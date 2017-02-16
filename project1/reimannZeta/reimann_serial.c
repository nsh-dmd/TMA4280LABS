#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double* gen_vector(size_t n) {
    double *vector = malloc( n * sizeof(double) );
    for (size_t i = 0; i < n; i++) {
        vector[i] = 0;
        vector[i] = 1. / pow(i, 2);
    }
    return vector;
}

double reimann_sum(double *vector, size_t n) {
    double s;
    for (size_t i = 0; i < n; i++) {
        s += vector[i];
    }
    return s;
}

double lare_sum() {
    return pow(M_PI, 2) / 6. ;
}

int main(int argc, char **argv) {
    double s;
    size_t k = atoi(argv[1]);
    if ( k > 14) larg_sum();
    else {
        double *vector = gen_vector( k*k );
        s = reimann_sum(vector);
    }

    printf("reimann_sum = %f \n", s);
    printf("error = %f \n", s - sum_larg());
    
    return 0;
}
