#include "mach0.h"

Vector_Tuple gen_machin_vector ( int n ) {
  // int rest = (double)n % nproc;
  Vector_Tuple vectors;
  vectors.v1 = (double*) malloc( n * sizeof(double) );
  vectors.v2 = (double*) malloc( n * sizeof(double) );

  for (size_t i = 1; i <= n; i++) {
    vectors.v1[i] = pow (-1., i-1) * pow(X1, 2*i-1) / (2*i-1);
    vectors.v2[i] = pow (-1., i-1) * pow(X2, 2*i-1) / (2*i-1);
  }
  return vectors;
}

double machin_formula(int n, Vector_Tuple t) {
  return 16 * calculate_sum(t.v1, n) - 4 * calculate_sum( t.v2, n );
}

double machin_pi() {
    return 16 * atan(X1) - 4 * atan(X2);
}
