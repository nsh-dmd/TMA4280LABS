#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double* gen_vector(size_t n) {
    double *vector = malloc( n * sizeof(double) );
    for (size_t i = 1; i <= n; i++) {
        vector[i] = 1. / (i*i);
    }
    return vector;
}

double reimann_sum(double *vector, size_t n) {
    double s = 0;
    for (size_t i = 0; i < n; i++) {
        s += vector[i];
    }
    return s;
}

double sum_larg() {
    return (M_PI * M_PI) / 6. ;
}

int main(int argc, char **argv) {
    double s;
    size_t k = atoi(argv[1]);
    if ( k > 14) sum_larg();
    else {
        double *vector = gen_vector( k*k );
        s = reimann_sum(vector, k);
    }

    printf("reimann_sum = %f \n", s);
    printf("error = %f \n", s - sum_larg());
    
    return 0;
}
