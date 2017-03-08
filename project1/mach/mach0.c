#include "mach0.h"

double* gen_machin_vector(double x, size_t n) {
    double *vector = (double*) malloc( n * sizeof(double) );
    for (size_t i = 1; i <= n; i++) {
        vector[i] = pow (-1., i-1) * pow(x, 2*i-1) / (2*i-1);
    }
    return vector;
}

double machin_formula(int n) {
    double *v1 = gen_machin_vector(X1, n);
    double *v2 = gen_machin_vector(X2, n);
    double pi = 16 * calculate_sum(v1, n) - 4 * calculate_sum( v2, n );
    free(v1);
    free(v2);
    return pi;
}

double machin_pi() {
    return 16 * atan(X1) - 4 * atan(X2);
}
