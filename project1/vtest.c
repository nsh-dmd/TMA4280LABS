#include "util.h"

double* gen_reimann_vector (int n) {
  double *vector = (double*) malloc( n * sizeof(double) );
   for (size_t i = 1; i <= n; i++) {
        vector[i] = 1. / (i*i);
  }
  return vector;
}

double reimann_pi (int n) {
    double *v = gen_reimann_vector(n);
    double pi = sqrt(6.0 * calculate_sum(v , n));
    free(v);
    return pi;
}
double* gen_machin_vector(double x, int n) {
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

void verification_test(int n) {
  int i=0;
  double error_m = 0., error_z = 0.;

  FILE *pFile = fopen("vtest.txt", "w+");
  fprintf( pFile,"**************************\n Verification test:\n" );
  fputs( "**************************\n", pFile );

  if ( n < 25 ) {
    for ( int k=1; k <= n; k++ ) {
<<<<<<< HEAD
      i = pow(2., k);
      error_m = abs_error(machin_formula(i));
=======
      //i = pow(2, k);
      //Vector_Tuple t = gen_machin_vector(n);
      //double m = machin_formula(i);
      //printf("mach_sum=%.20f\n", m);
      error_m = abs_error(machin_formula(1<<k));
    //   free(t.v1);
    //   free(t.v2);
>>>>>>> 8af8626735cf3799bc0c2cb73b90d63314dec7bf
      error_z = abs_error(reimann_pi(i));
      fprintf(pFile, "k = %d \t Mach error = %e \n", k,  error_m);
      fprintf(pFile, "k = %d \t Zeta error = %e \n", k,  error_z);
      fputs( "**************************\n", pFile );
    }
  }
  else printf("ERROR! n must be less than 25!\n");

  fclose(pFile);
}

 int main(int argc, char const **argv) {
     int n = atoi(argv[1]);
     verification_test(n);
     return 0;
 }
