#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define PI 3.14159265358979323846
#define X1 1. / 5
#define X2 1. / 239

typedef struct {
    double* v1;
    double* v2;
} Vector_Tuple;
double calculate_sum(double *vector, size_t n) {
    double s = 0.;

    #pragma omp parallel for reduction(+:s)
    for (size_t i = 0; i < n; i++) {
        s += vector[i];
    }
    return s;
}

double machin_formula(size_t n, Vector_Tuple t) {
    return 16 * calculate_sum(t.v1, n) - 4 * calculate_sum( t.v2, n );
}
double abs_error(double s) {
  return fabs(s - PI);
}
Vector_Tuple gen_machin_vector ( size_t n ) {
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
void print_to_file(char* test_name, int n, double walltime, double error) {
    FILE *pFile = fopen("parallel_test.txt", "a+");
    fprintf( pFile,"*************%s*************\n", test_name );
    // fputs( "**************************\n", pFile );
    fprintf(pFile,"n = %d\nwalltime = %f\nerr = %e\n\n", n, walltime, error);
    // fputs( "**************************\n", pFile );
}

int main(int argc, char **argv) {

    size_t n = atoi(argv[1]);
    if ( argc < 2 || (n & (n - 1)) ) {
      printf("Usage:\n");
      printf("  make n\n\n");
      printf("Arguments:\n");
      printf("  n: the problem size (must be a power of 2)\n");
      return 1;
    }
    double start_time = omp_get_wtime();
    Vector_Tuple tuple = gen_machin_vector(n);
    double error = abs_error(machin_formula(n, tuple));
    print_to_file("Machin OpenMP", n, omp_get_wtime()-start_time, error);
    return 0;
}
