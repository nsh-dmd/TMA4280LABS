/**
 * C program to solve the two-dimensional Poisson equation on
 * a unit square using one-dimensional eigenvalue decompositions
 * and fast sine transforms.
 *
 * Einar M. Rønquist
 * NTNU, October 2000
 * Revised, October 2001
 * Revised by Eivind Fonn, February 2015
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include "mpi.h"


#define PI 3.14159265358979323846
#define true 1
#define false 0

typedef double real;
typedef int bool;

// Function prototypes
real *mk_1D_array(size_t n, bool zero);
real **mk_2D_array(size_t n1, size_t n2, bool zero);
void transpose(real **bt, real **b, size_t m);
real rhs(real x, real y);
void fst_(real *v, int *n, real *w, int *nn);
void fstinv_(real *v, int *n, real *w, int *nn);
real exact_solution(real x, real y);
void parallel_transpose(int rank, int nproc, int m, double *bt, double *b, \
                        double *sendbuf, double *recvbuf, int *counts, \
                        int *displs, int *local_columns, int *col_displacements) ;

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage:\n");
        printf("  poisson n\n\n");
        printf("Arguments:\n");
        printf("  n: the problem size (must be a power of 2)\n");
    }

    // The number of grid points in each direction is n+1
    // The number of degrees of freedom in each direction is n-1
    int n = atoi(argv[1]);
    int m = n - 1;
    int nn = 4 * n;
    real h = 1.0 / n;

    double start_time;

    // Initialize MPI environment
    int rank, nproc;
    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &nproc );

    MPI_Barrier( MPI_COMM_WORLD );

    int max_threads = omp_get_max_threads();
    int chunk_size = 0;
    int displacement = 0;

    if ( rank == 0 ) {
        start_time = omp_get_wtime();
    }

    int columns = m / nproc;
    int rest_columns = m % nproc;
    int last_process_index_start = nproc - rest_columns;

    int *local_columns = (int *) malloc( nproc * sizeof(int) );
    int *col_displacements = (int *) malloc( nproc * sizeof(int) );

    int *counts = (int *) malloc( nproc * sizeof(int) );
    int *displs = (int *) malloc( nproc * sizeof(int) );

    // printf("Line:83, load balancing, partition the matrix in vectors\n");
    for (int i = 0; i < nproc; i++) {
        local_columns[i] = columns;
        // Distribute the remaining columns to last processes
        if ( rest_columns && i >= last_process_index_start ) {
            local_columns[i] = local_columns[i] + 1;
            rest_columns-- ;
        }
        col_displacements[i] = displacement;
        displacement += local_columns[i];
    }

    for (int i = 0; i < nproc; i++) {
        counts[i] = local_columns[i] * local_columns[rank];
        displs[i] = chunk_size;
        chunk_size += counts[i];
    }

    if ( rank >= last_process_index_start && m % nproc ) {
        columns++ ;
    }

    double *sendbuf = mk_1D_array ( chunk_size, false );
    double *recvbuf = mk_1D_array ( chunk_size, false );

/*
    // Grid points
    real *grid = mk_1D_array(n+1, false);
    for (size_t i = 0; i < n+1; i++) {
        grid[i] = i * h;
    }
*/
    // printf("Line:115, The diagonal of the eigenvalue matrix of T\n");
    real *diag = mk_1D_array(m, false);
    #pragma omp parallel for schedule ( static )
    for (size_t i = 0; i < m; i++) {
        diag[i] = 2.0 * (1.0 - cos((i+1) * PI / n));
    }

    // Initialize the right hand side data
    real *b = mk_1D_array(m * local_columns[rank], false);
    real *bt = mk_1D_array(m * local_columns[rank], false);
    real **z = mk_2D_array(max_threads, nn, false);

    #pragma omp parallel for schedule(static)
    for (size_t i = 0; i < local_columns[rank]; i++) {
        for (size_t j = 0; j < m; j++) {
            b[ i*m+j ] = h * h * rhs( h*col_displacements[rank]+i*h , h*j );
        }
    }

    // printf("Line:134, Calculate Btilde^T = S^-1 * (S * B)^T\n");
    // Transform
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < local_columns[rank]; i++) {
        int thread_num = omp_get_thread_num();
        fst_( b + (i * m), &n, z[thread_num], &nn );
    }

    /*
    transpose(bt, b, m);
    for (size_t i = 0; i < m; i++) {
        fstinv_(bt[i], &n, z, &nn);
    }
    */

    // printf("Line:149, transpose\n");
    parallel_transpose(rank, nproc, m, bt, b, sendbuf, recvbuf, counts, displs, local_columns, col_displacements);

    // printf("Line:152, Invers transform\n");
    #pragma omp parallel for schedule(static)
    for (size_t i = 0; i < local_columns[rank]; i++) {
        int thread_num = omp_get_thread_num();
        fstinv_(bt + (i * m), &n, z[thread_num], &nn);
    }

    // printf(" Solve Lambda * Xtilde = Btilde\n");
    #pragma omp parallel for schedule(static)
    for (size_t i = 0; i < local_columns[rank]; i++) {
        for (size_t j = 0; j < m; j++) {
            size_t index = i * m + j;
            bt[ index ] /=  diag[j] + diag[ col_displacements[rank]+i ];
        }
    }

    // printf(" Calculate X = S^-1 * (S * Xtilde^T)\n");
    // Transform
    #pragma omp parallel for schedule ( static )
    for ( size_t i = 0; i < local_columns[rank]; i++ ) {
        int thread_num = omp_get_thread_num();
        fst_( bt + (i * m), &n, z[thread_num], &nn );
    }

    /* transpose(b, bt, m);
    for (size_t i = 0; i < m; i++) {
        fstinv_(b[i], &n, z, &nn);
    } */

    // transpose
    parallel_transpose(rank, nproc, m, b, bt, sendbuf, recvbuf, counts, displs, local_columns, col_displacements);

    // Invers
    #pragma omp parallel for schedule(static)
    for (size_t i = 0; i < local_columns[rank]; i++) {
        int thread_num = omp_get_thread_num();
        fstinv_(b + (i * m), &n, z[thread_num], &nn);
    }

    double u_max = 0.0;
    double error_max = 0.0;

    // Calculate maximal value of solution
    #pragma omp parallel for schedule(static)
    for (size_t i = 0; i < local_columns[rank]; i++) {
        for (size_t j = 0; j < m; j++) {

            int index = i * m + j;
            real x = h * i + h * col_displacements[rank];
            real y = j * h;

            // To verify and calculate the error
            double u = exact_solution( x, y );
            double err = fabs( b[index] - u );

            u_max = u_max > b[index] ? u_max : b[index];
            error_max = error_max > err ? error_max : err;
        }
    }

    double umax, error;

    MPI_Reduce( &u_max, &umax, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD );
    MPI_Reduce( &error_max, &error, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD );

    if (rank == 0) {
        printf ("{max_u:%e,", umax);
        printf ("max_err:%e,", error);
    }

    if (rank == 0) {
        printf("n:%d,", n);
        printf ("time:%f}\n", MPI_Wtime() - start_time);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    // free(grid);
    free(recvbuf);
    free(sendbuf);
    free(local_columns);
    free(col_displacements);
    free(counts);
    free(diag);
    free(z);
    free(b);
    free(bt);


    MPI_Finalize();

    return 0;
}

void parallel_transpose(int rank, int nproc, int m, double *bt, double *b, \
                        double *sendbuf, double *recvbuf, int *counts, \
                        int *displs, int *local_columns, int *col_displacements)
{
    // printf("Line:250, pack\n");
    #pragma omp parallel for schedule(static)
    for (size_t p = 0; p < nproc; p++) {
        for (size_t col = 0; col < local_columns[rank]; col++) {
            size_t r_index = col * m + col_displacements[p];
            size_t s_index = displs[p] + col * local_columns[p];
            // printf("read: %zu \t", r_index);
            // printf("write: %zu \n", s_index);

        // copy blocks of matrix into the send buffer
        memcpy( sendbuf + s_index, b + r_index, local_columns[p] * sizeof(double) );
        }
    }
    // printf("Line:264, alltoallv\n");
    MPI_Alltoallv( sendbuf, counts, displs, MPI_DOUBLE, recvbuf, counts, displs, MPI_DOUBLE, MPI_COMM_WORLD );

    // printf("Line:266, unpack\n");
    #pragma omp parallel for schedule(static)
    for (size_t p = 0; p < nproc; p++)
    {
        for (size_t col = 0; col < local_columns[rank]; col++)
        {
            for (size_t c = 0; c < local_columns[p]; c++)
            {
                size_t r_index = (c * local_columns[rank]) + displs[p] + col;
                size_t s_index = m * col + col_displacements[p] + c;
                bt[s_index] = recvbuf[r_index];
            }
        }
    }

}


// Test function
real test_function(real x, real y) {
    return exp(x) * sin(2 * PI * x) * sin(2 * PI * y);
}

// Verification functions
real exact_solution(real x, real y) {
    return sin(PI * x) * sin(2 * PI * y);
  // double res= sin(PI * x) * sin(2 * PI * y);
  // printf("solution=%f\n", res);
  // return res;
}

real rhs(real x, real y) {
    return 2 * (y - y*y + x - x*x);
}

void transpose(real **bt, real **b, size_t m)
{
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < m; j++) {
            bt[i][j] = b[j][i];
        }
    }
}

real *mk_1D_array(size_t n, bool zero)
{
    if (zero) {
        return (real *)calloc(n, sizeof(real));
    }
    return (real *)malloc(n * sizeof(real));
}

real **mk_2D_array(size_t n1, size_t n2, bool zero)
{
    real **ret = (real **)malloc(n1 * sizeof(real *));

    if (zero) {
        ret[0] = (real *)calloc(n1 * n2, sizeof(real));
    }
    else {
        ret[0] = (real *)malloc(n1 * n2 * sizeof(real));
    }

    for (size_t i = 1; i < n1; i++) {
        ret[i] = ret[i-1] + n2;
    }
    return ret;
}
