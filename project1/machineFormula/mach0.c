#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double* gen_vector(double x, size_t n) {
    double *vector = malloc( n * sizeof(double) );
    for (size_t i = 1; i <= n; i++) {
        vector[i] = pow (-1., i-1) * pow(x, 2*i-1) / (2*i-1);
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

double sum_larg(double x) {
    return arctan(x)
}

double pi_quarter() {
    return 4 * arctan(1./5) - arctan(1./239);
}

void unit_test(size_t n, ) {
}

int main(int argc, char **argv) {
    double s;
    size_t k = atoi(argv[1]);
    double x = -1 + 2. * (doubel)rand() / RAND_MAX;
    
    if ( k > 14) sum_larg(x);
    else {
        double x = -1 + 2. * (doubel)rand() / RAND_MAX;        
        double*vector = gen_vector( x, k*k );
        s = machine_formula(vector, k);
    }

    printf("reimann_sum = %f \n", s);
    printf("error = %f \n", fabs(s - _larg(x));
    
    return 0;
}

