#include "../util.h"
#include <omp.h>


double abs_error(double s) {
  return fabs(s - PI);
}
double calculate_sum(double *vector, int n) {
    double s = 0;
    #pragma omp parallel for reduction(+:s)
    for (size_t i = 0; i < n; i++) {
        s += vector[i];
    }
    return s;
}

double* gen_reimann_vector (int n, double *vector) {
   #pragma omp parallel for schedule(static)
   for (size_t i = 1; i <= n; i++) {
        vector[i] = 1. / (i*i);
  }
  return vector;
}
double reimann_pi (int n, double *v) {
    return sqrt(6.0 * calculate_sum(v , n));
}
void print_to_file(char* test_name, int n, double walltime, double error) {
    FILE *pFile = fopen("parallel_test.txt", "a+");
    fprintf( pFile,"*************%s*************\n", test_name );
    // fputs( "**************************\n", pFile );
    fprintf(pFile,"n = %d\nwalltime = %f\nerr = %e\n\n", n, walltime, error);
    // fputs( "**************************\n", pFile );
}

int main(int argc, char **argv) {

    int n = atoi(argv[1]);
    if ( argc < 2 || (n & (n - 1)) ) {
      printf("Usage:\n");
      printf("  make n\n\n");
      printf("Arguments:\n");
      printf("  n: the problem size (must be a power of 2)\n");
      return 1;
    }
    double start_time = omp_get_wtime();
    double *vec = (double*) malloc(n*sizeof(double));
    double error = abs_error(reimann_pi(n, vec));
    print_to_file("Zeta OpenMP", n, omp_get_wtime()-start_time, error);

    return 0;
}
