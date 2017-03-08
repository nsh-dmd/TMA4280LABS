// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>
#include "../util.h"

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
double* gen_reimann_vector (int n) {
    double *vector = (double*) malloc( n * sizeof(double) );
    for (size_t i = 1; i <= n; i++) {
        vector[i] = 1. / (i*i);
    }
    return vector;
}

double reimann_pi (int n, double *v) {
    return sqrt(6.0 * calculate_sum(v , n));
}

int main(int argc, char **argv) {

    int n = atoi(argv[1]);
    if ( argc < 2 || power_of_2(n) ) {
      MPI_Finalize();
      return 1;
    }

    int rank, nproc;
    double *vector, *local_vector;
    // Vector_Tuple vectors_m, scattered_m;

    double start_time;

    // Initializing MPI environment
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    int chunk_size = n/nproc;
    double partial_sum, global_sum;

    if (rank == 0) {
        start_time = MPI_Wtime();
        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
        // partial machin vectors sends to every process
        vector = gen_reimann_vector(n);
    }

    // each process will have its own partial vector
    local_vector = (double*) malloc(chunk_size * sizeof(double));

    // send partial vectors to each process
    MPI_Scatter( vector, chunk_size, MPI_DOUBLE, local_vector, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD );

    partial_sum = reimann_pi(chunk_size, local_vector);
    MPI_Allreduce(&partial_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    if (rank == 0) {
        print_to_file("Reimann MPI", n, nproc, MPI_Wtime() - start_time, abs_error(global_sum));
        printf("Error = %e\n", abs_error(global_sum));
        printf ("Elapsed time =  %f \n", MPI_Wtime() - start_time);
        free(local_vector);
        free(vector);
    }

    MPI_Finalize();

  return 0;
}
