#include "../util.h"
#include "../zeta/zeta0.h"
#include "mpi.h"

double recursive_doubling( int nproc, int rank, double global_sum, double partial_sum );
//double reimann_pi (int n, double *v);
//double* gen_reimann_vector (int n);

int main(int argc, char **argv) {

    int n = atoi(argv[1]);

    if ( argc < 2 || !power_of_2(n) ) {
        MPI_Finalize();
        return 1;
    }

    double start_time;
    int rank, nproc;

    double *vector, *local_vector;
    // Initializing MPI environment
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    int chunk_size = n/nproc;
    double partial_sum=0, global_sum=0;

    MPI_Barrier(MPI_COMM_WORLD);

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

    global_sum = recursive_doubling(nproc, rank, global_sum, partial_sum);

    if (rank==0) {
        print_to_file("Reimann MPI", n, nproc, MPI_Wtime() - start_time, abs_error(global_sum));
        printf("Error = %e\n", abs_error(global_sum));
        printf ("Elapsed time =  %f \n", MPI_Wtime() - start_time);
        free(local_vector);
        free(vector);
        }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

    return 0;
}

// double* gen_reimann_vector (int n) {
//     double *vector = (double*) malloc( n * sizeof(double) );
//     for (size_t i = 1; i <= n; i++) {
//         vector[i] = 1. / (i*i);
//     }
//     return vector;
// }
//
// double reimann_pi (int n, double *v) {
//     return sqrt(6.0 * calculate_sum(v , n));
// }

double recursive_doubling( int nproc, int rank, double global_sum, double partial_sum ) {

    int q;

    for (size_t d = 0; d < log2(nproc-1); d++) {
        double sum = 0.;
        q = rank ^ (1 << d);

        // send global_sum to processor q
        MPI_Send(&global_sum, 1, MPI_DOUBLE, q, 0, MPI_COMM_WORLD);

        //Receive partial_sum from processor q
        MPI_Recv(&partial_sum, 1, MPI_DOUBLE, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        global_sum += sum;
    }

    return global_sum;
}
