#include "../hybrid/hybrid.h"

int main(int argc, char **argv) {

    int n = atoi(argv[1]);
    if ( argc < 2 || !power_of_2(n) ) {
      return 1;
    }

    int nthreads;
    double start_time = omp_get_wtime();
    double *vec = gen_reimann_vector(n);
    double error = abs_error(reimann_pi(n, vec));

    #pragma omp parallel private(nthreads)
    if ( omp_get_thread_num() == 0) {
        nthreads = omp_get_num_threads();
        print_to_file("zeta_openmp", n, nthreads, omp_get_wtime()-start_time, error);
        printf("Error = %e\n", error);
    }

    free(vec);
    return 0;
}
