#include "../hybrid/hybrid.h"

int main(int argc, char **argv) {

    int n = atoi(argv[1]);
    if ( argc < 2 || !power_of_2(n) ) {
      return 1;
    }

    int nthreads;
    double start_time = omp_get_wtime();
    Vector_Tuple tuple = gen_machin_vector(n);
    double error = abs_error(machin_formula(n, tuple));

    #pragma omp parallel private(nthreads)
    if ( omp_get_thread_num() == 0) {
        nthreads = omp_get_num_threads();
        print_to_file("machin_openmp", n, nthreads, omp_get_wtime()-start_time, error);
        printf("Error = %e\n", error);
    }
    free(tuple.v1);
    free(tuple.v2);

    return 0;
}
