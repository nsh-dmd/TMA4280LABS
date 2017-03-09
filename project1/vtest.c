#include "util.h"
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265358979323846
#define X1 1. / 5
#define X2 1. / 239
typedef struct {
    double* v1;
    double* v2;
} Vector_Tuple;
/*
double calculate_sum (double *vector, size_t n) {
  double s = 0;
  for (size_t i = 0; i < n; i++)
    s += vector[i];
  return s;
}

double abs_error(double s) {
  return fabs(s - PI);
}
*/
double* gen_reimann_vector (size_t n) {
  double *vector = (double*) malloc( n * sizeof(double) );
   for (size_t i = 1; i <= n; i++) {
        vector[i] = 1. / (i*i);
  }
  return vector;
}

double reimann_pi (size_t n) {
    double *v = gen_reimann_vector(n);
    double pi = sqrt(6.0 * calculate_sum(v , n));
    free(v);
    return pi;
}
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

// Vector_Tuple gen_machin_vector ( int n ) {
//     // int rest = (double)n % nproc;
//     Vector_Tuple vectors;
//     vectors.v1 = (double*) malloc( n * sizeof(double) );
//     vectors.v2 = (double*) malloc( n * sizeof(double) );
//
//     for (size_t i = 1; i <= n; i++) {
//         vectors.v1[i] = pow (-1., i-1) * pow(X1, 2*i-1) / (2*i-1);
//         vectors.v2[i] = pow (-1., i-1) * pow(X2, 2*i-1) / (2*i-1);
//     }
//     return vectors;
// }
// double machin_formula(int n, Vector_Tuple t) {
//     return 16 * calculate_sum(t.v1, n) - 4 * calculate_sum( t.v2, n );
// }

void verification_test(int n) {

  double i, error_m = 0, error_z = 0;

  FILE *pFile = fopen("vtest.txt", "w+");
  fprintf( pFile,"**************************\n Verification test:\n" );
  fputs( "**************************\n", pFile );

  if ( n < 25 ) {
    for ( size_t k=1; k <= n; k++ ) {
      i = pow(2., k);
    //   Vector_Tuple t = gen_machin_vector(n);
      error_m = abs_error(machin_formula(i));
    //   free(t.v1);
    //   free(t.v2);
      error_z = abs_error(reimann_pi(i));
      fprintf(pFile, "k = %zu \t Mach error = %e \n", k,  error_m);
      fprintf(pFile, "k = %zu \t Zeta error = %e \n", k,  error_z);
      fputs( "**************************\n", pFile );
    }
  }
  // else fprintf(pFile, "n = %d \t Error = %f \n", n, abs_error(machin_pi()) );
  else printf("ERROR! n must be less than 25!\n");

  fclose(pFile);
}

// int main(int argc, char const **argv) {
//     int n = atoi(argv[1]);
//     verification_test(n);
//     return 0;
// }
