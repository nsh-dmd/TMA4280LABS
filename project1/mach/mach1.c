#include "mach0.h"
#include "mpi.h"

int main(int argc, char **argv) {

    int n = atoi(argv[1]);
    if ( argc < 2 || !power_of_2(n) ) {
      return 1;
    }

    int rank, nproc;

    Vector_Tuple vectors_m, scattered_m;

    double start_time = 0.;

    // Initializing MPI environment
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    int chunk_size = n/nproc;
    double partial_sum=0., total_sum=0.;

    if (rank == 0) {
        start_time = MPI_Wtime();
        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
        // partial machin vectors sends to every process
        vectors_m = gen_machin_vector(n);
    }

    // each process will have its own partial vector
    scattered_m.v1 = (double*) calloc(chunk_size , sizeof(double));
    scattered_m.v2 = (double*) calloc(chunk_size , sizeof(double));

    // send partial vectors to each process
    MPI_Scatter( vectors_m.v1, chunk_size, MPI_DOUBLE, scattered_m.v1, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD );
    MPI_Scatter( vectors_m.v2, chunk_size, MPI_DOUBLE, scattered_m.v2, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD );

    partial_sum = machin_formula(chunk_size, scattered_m);
    MPI_Reduce(&partial_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Error = %e\n", abs_error(total_sum));
        printf ("Elapsed time =  %f \n", MPI_Wtime() - start_time);
        print_to_file("machin_mpi", n, nproc, MPI_Wtime() - start_time, abs_error(total_sum));
        free(vectors_m.v1);
        free(vectors_m.v2);
    }
    free(scattered_m.v1);
    free(scattered_m.v2);

    MPI_Finalize();

    return 0;
}
