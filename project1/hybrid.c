#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "mpi.h"

#define PI 3.14159265358979323846
#define X1 1. / 5
#define X2 1. / 239

typedef struct {
    double* v1;
    double* v2;
} Vector_Tuple;

double calculate_sum(double *vector, size_t n) {
    double s = 0;
    #pragma omp parallel for reduction(+:s)
    for (size_t i = 0; i < n; i++) {
        s += vector[i];
    }
    return s;
}

double machin_formula(int n, Vector_Tuple t) {
    return 16 * calculate_sum(t.v1, n) - 4 * calculate_sum( t.v2, n );
}

double machin_pi() {
    return 16 * atan(X1) - 4 * atan(X2);
}

double abs_error(double s) {
  return fabs(s - PI);
}

Vector_Tuple gen_machin_vector ( uint16_t n ) {
    // int rest = (double)n % nproc;
    Vector_Tuple vectors;
    vectors.v1 = (double*) malloc( n * sizeof(double) );
    vectors.v2 = (double*) malloc( n * sizeof(double) );

    #pragma omp parallel for schedule(static)
    for (size_t i = 1; i <= n; i++) {
        vectors.v1[i] = pow (-1., i-1) * pow(X1, 2*i-1) / (2*i-1);
        vectors.v2[i] = pow (-1., i-1) * pow(X2, 2*i-1) / (2*i-1);
    }
    return vectors;
}
void print_to_file(char* test_name, int n, int nproc, double walltime, double error) {
    FILE *pFile = fopen("parallel_test.txt", "a+");
    fprintf( pFile,"*************%s*************\n", test_name );
    // fputs( "**************************\n", pFile );
    fprintf(pFile,"n = %d\n nproc = %d\n walltime = %f\n err = %e\n\n", n, nproc, walltime, error);
    // fputs( "**************************\n", pFile );

}

int main(int argc, char **argv) {

    uint16_t n = atoi(argv[1]);
    if ( argc < 2 || (n & (n - 1)) ) {
      printf("Usage:\n");
      printf("  make n\n\n");
      printf("Arguments:\n");
      printf("  n: the problem size (must be a power of 2)\n");
      MPI_Finalize();
      return 1;
    }

    int rank, nproc;

    // double *vector_z, *scattered_z;
    Vector_Tuple vectors_m, scattered_m;

    double start_time;
    // double mach_time = 0, zeta_time = 0;


    // Initializing MPI environment
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    uint16_t chunk_size = (double)n/nproc;
    double partial_sum, total_sum;

    if (rank == 0) {
        start_time = MPI_Wtime();
        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
        // partial machin vectors sends to every process
        vectors_m = gen_machin_vector(n);
    }

    // each process will have its own partial vector
    scattered_m.v1 = (double*) malloc(chunk_size * sizeof(double));
    scattered_m.v2 = (double*) malloc(chunk_size * sizeof(double));

    // send partial vectors to each process
    MPI_Scatter( vectors_m.v1, chunk_size, MPI_DOUBLE, scattered_m.v1, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD );
    MPI_Scatter( vectors_m.v2, chunk_size, MPI_DOUBLE, scattered_m.v2, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD );

    partial_sum = machin_formula(chunk_size, scattered_m);
    MPI_Reduce(&partial_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        print_to_file("Machin hybrid", n, nproc, MPI_Wtime() - start_time, abs_error(total_sum));
        printf("Error = %e\n", abs_error(total_sum));
        printf ("Elapsed time =  %f \n", MPI_Wtime() - start_time);
    }

    free(scattered_m.v1);
    free(scattered_m.v2);
    free(vectors_m.v1);
    free(vectors_m.v2);

    MPI_Finalize();

    return 0;
}
