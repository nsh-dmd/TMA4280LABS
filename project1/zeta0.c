#include "util.h"

double* gen_reimann_vector (size_t n) {
  double *vector = (double*) malloc( n * sizeof(double) );
   for (size_t i = 1; i <= n; i++) {
        vector[i] = 1. / (i*i);
  }
  return vector;
}

double reimann_pi (size_t n) {
    double *v = gen_reimann_vector(n);
    double pi = sqrt(6.0 * sum(v , n));
    free(v);
    return pi;
}
