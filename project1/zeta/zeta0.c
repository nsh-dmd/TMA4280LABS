#include "zeta0.h"
double* gen_reimann_vector (size_t n) {
  double *vector = (double*) malloc( n * sizeof(double) );
   for (size_t i = 1; i <= n; i++) {
        vector[i] = 1. / (i*i);
  }
  return vector;
}

double reimann_pi (int n, double *v) {
    return sqrt(6.0 * calculate_sum(v , n));
}
