#include "hybrid.h"

double calculate_sum(double *vector, int n) {
    double s = 0;
    #pragma omp parallel for reduction(+:s) num_threads(4) schedule(guided)
    for (int i = 0; i < n; i++) {
        s += vector[i];
    }
    return s;
}

double abs_error(double s) {
  return fabs(s - PI);
}

void print_to_file(char* test_name, int n, int nproc, double walltime, double error) {
    char name[15];
    strcpy(name, test_name);
    FILE *pFile = fopen(strcat(name, ".txt"), "a+");
    fprintf( pFile,"*************%s*************\n", test_name );
    fprintf(pFile,"n = %d\n nproc/nthreads = %d\n walltime = %f\n err = %e\n\n", n, nproc, walltime, error);
}
int power_of_2(int n) {

    if ((n & (n - 1)) ) {
        printf("Usage:\n");
        printf("  make n\n\n");
        printf("Arguments:\n");
        printf("  n: the problem size (must be a power of 2)\n");
        return 0;
    }
    return 1;
}
double machin_formula(int n, Vector_Tuple t) {
    return 16 * calculate_sum(t.v1, n) - 4 * calculate_sum( t.v2, n );
}
Vector_Tuple gen_machin_vector ( int n ) {
    // int rest = (double)n % nproc;
    Vector_Tuple vectors;
    vectors.v1 = (double*) malloc( n * sizeof(double) );
    vectors.v2 = (double*) malloc( n * sizeof(double) );

    #pragma omp parallel for num_threads(4) schedule(guided)
    for (int i = 1; i <= n; i++) {
        vectors.v1[i] = pow (-1., i-1) * pow(X1, 2*i-1) / (2*i-1);
        vectors.v2[i] = pow (-1., i-1) * pow(X2, 2*i-1) / (2*i-1);
    }
    return vectors;
}
double* gen_reimann_vector (int n) {
    double *vector = (double*) malloc( n * sizeof(double) );
   #pragma omp parallel for num_threads(4) schedule(guided)
   for (size_t i = 1; i <= n; i++) {
        vector[i] = 1. / (i*i);
  }
  return vector;
}

double reimann_pi (int n, double *v) {
    return sqrt(6.0 * calculate_sum(v , n));
}
