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
#include <math.h>

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
        start_time = MPI_Wtime();
    }

    size_t columns = m / nproc;
    size_t rest_columns = m % nproc;
    size_t last_process_index_start = nproc - rest_columns;

    size_t *local_columns = (size_t *) malloc( nproc * sizeof(size_t) );
    size_t *col_displacements = (size_t *) malloc( sizeof(size_t) );

    size_t *counts = (size_t *) malloc( nproc * sizeof(size_t) );
    size_t *displs = (size_t *) malloc( nproc * sizeof(size_t) );

    // load balancing, partition the matrix in vectors
    for (size_t i = 0; i < nproc; i++) {
        local_columns[i] = columns;
        // Distribute the remaining columns to last processes
        if ( rest_columns && i >= last_process_index_start ) {
            local_columns[i] = local_columns[i] + 1;
            rest_columns-- ;
        }
        col_displacements[i] = displacement;
        displacement += local_columns[i];
    }

    for (size_t i = 0; i < nproc; i++) {
        counts[i] = local_columns[i] * local_columns[rank];
        displs[i] = chunk_size;
        chunk_size += counts[i];
    }

    if ( rank >= last_process_index_start && m % nproc ) {
        columns++ ;
    }

    double *sendbuff = mk_1D_array ( chunk_size, false );
    double *recvbuff = mk_1D_array ( chunk_size, false );

/*
    // Grid points
    real *grid = mk_1D_array(n+1, false);
    for (size_t i = 0; i < n+1; i++) {
        grid[i] = i * h;
    }
*/
    // The diagonal of the eigenvalue matrix of T
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
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < m; j++) {
            b[i][j] = h * h * rhs(grid[i], grid[j]);
        }
    }

    // Calculate Btilde^T = S^-1 * (S * B)^T
    // Transform
    #pragma omp parallel for schedule(static)
    for (size_t i = 0; i < local_columns[rank]; i++) {
        int thread_num = omp_get_thread_num();
        fst_( b + (i * m), &n, z[thread_num], &nn );
    }
    /*
    transpose(bt, b, m);
    for (size_t i = 0; i < m; i++) {
        fstinv_(bt[i], &n, z, &nn);
    }
    */

    //TODO: Implement/Add parallel transpose function

    // Invers transform
    #pragma omp parallel for schedule(static)
    for (size_t i = 0; i < local_columns[rank]; i++) {
        int thread_num = omp_get_thread_num();
        fstinv_(bt + (i * m), &n, z[thread_num], &nn);
    }

    // Solve Lambda * Xtilde = Btilde
    #pragma omp parallel for schedule(static)
    for (size_t i = 0; i < local_columns[rank]; i++) {
        for (size_t j = 0; j < m; j++) {
            size_t index = i * m + j;
            bt[i][j] = bt[index] / (diag[j] + diag[ col_displacements[rank]+i ] );
        }
    }

    // Calculate X = S^-1 * (S * Xtilde^T)
    // Transform
    #pragma omp parallel for schedule ( static )
    for ( size_t i = 0; i < local_columns[rank]; i++ ) {
        fst_( bt + (i * m), &n, z[thread_num], &nn );
    }

    //TODO: Implement/Add parallel transpose function
    /* transpose(b, bt, m);
    for (size_t i = 0; i < m; i++) {
        fstinv_(b[i], &n, z, &nn);
    } */

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

            size_t index = i * m + j;
            real x = h * i + h * coldispls[rank];
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
        printf ("u_max =  %e\n", umax);
        printf ("Max error =  %e\n", error);
    }

    if (rank == 0) {
        printf("n=%d\n", n);
        printf ("Time =  %f \n", MPI_Wtime() - start_time);
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

void parallel_transpose( void ) {

    // TODO: Implement transpose function using MPI_ALltoallv
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
