// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>
#include "zeta0.h"
#include "mpi.h"

// #define PI 3.14159265358979323846
//
// double calculate_sum(double *vector, int n) {
//     double s = 0;
//     for (size_t i = 0; i < n; i++) {
//         s += vector[i];
//     }
//     return s;
// }
//
// double* gen_reimann_vector (int n, double *vector) {
//    for (size_t i = 1; i <= n; i++) {
//         vector[i] = 1. / (i*i);
//   }
//   return vector;
// }
//
// double reimann_pi (int n, double *v) {
//     return sqrt(6.0 * calculate_sum(v , n));
// }

// double abs_error(double s) {
//   return fabs(s - PI);
// }
// void print_to_file(char* test_name, int n, int nproc, double walltime, double error) {
//     FILE *pFile = fopen("parallel_test.txt", "a+");
//     fprintf( pFile,"*************%s*************\n", test_name );
//     fputs( "**************************\n", pFile );
//     fprintf(pFile,"n = %d\nnproc = %d\nwalltime = %f\nerr = %e\n\n", n, nproc, walltime, error);
//     // fputs( "**************************\n", pFile );
// }
int main(int argc, char **argv) {

    int n = atoi(argv[1]);
    if ( argc < 2 || !power_of_2(n) ) {
      return 1;
    }

    int rank, nproc;

    double *vector_z= (double*) malloc( n * sizeof(double) );
    // Vector_Tuple vectors_m, scattered_m;

    double start_time = 0.0;
    // double mach_time = 0, zeta_time = 0;


    // Initializing MPI environment
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    int chunk_size = n/nproc;
    double partial_sum, total_sum;

    if (rank == 0) {
        start_time = MPI_Wtime();
        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
        // partial machin vectors sends to every process
        vector_z = gen_reimann_vector(n);
    }

    // each process will have its own partial vector
    double *scattered_z = (double*) malloc(chunk_size * sizeof(double));

    // send partial vectors to each process
    MPI_Scatter( vector_z, chunk_size, MPI_DOUBLE, scattered_z, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD );

    partial_sum = reimann_pi(chunk_size, scattered_z);
    MPI_Reduce(&partial_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        print_to_file("Reimann MPI", n, nproc, MPI_Wtime() - start_time, abs_error(total_sum));
        printf("Error = %e\n", abs_error(total_sum));
        printf ("Elapsed time =  %f \n", MPI_Wtime() - start_time);
        free(scattered_z);
        free(vector_z);
    }
    MPI_Finalize();

  return 0;
}
