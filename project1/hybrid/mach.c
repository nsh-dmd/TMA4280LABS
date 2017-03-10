#include "hybrid.h"

int main(int argc, char **argv) {

    int n = atoi(argv[1]);
    if ( argc < 2 || !power_of_2(n) ) {
      return 1;
    }

    int rank, nproc;

    Vector_Tuple vectors, local_vectors;

    double start_time;
    double partial_sum=0, total_sum=0;

    // Initializing MPI environment
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    int chunk_size = n/nproc;

    if (rank == 0) {
        start_time = MPI_Wtime();
        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
        // partial machin vectors sends to every process
        vectors = gen_machin_vector(n);
    }

    // each process will have its own partial vector
    local_vectors.v1 = (double*) malloc(chunk_size * sizeof(double));
    local_vectors.v2 = (double*) malloc(chunk_size * sizeof(double));

    // send partial vectors to each process
    MPI_Scatter( vectors.v1, chunk_size, MPI_DOUBLE, local_vectors.v1, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD );
    MPI_Scatter( vectors.v2, chunk_size, MPI_DOUBLE, local_vectors.v2, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD );

    partial_sum = machin_formula(chunk_size, local_vectors);
    MPI_Reduce(&partial_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        print_to_file("machin_hybrid", n, nproc, MPI_Wtime() - start_time, abs_error(total_sum));
        printf("Error = %e\n", abs_error(total_sum));
        printf ("Elapsed time =  %f \n", MPI_Wtime() - start_time);
        free(vectors.v1);
        free(vectors.v2);
    }
    free(local_vectors.v1);
    free(local_vectors.v2);

    MPI_Finalize();

    return 0;
}
