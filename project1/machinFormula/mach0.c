#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static const double X1 = 1. / 5;
static const double X2 = 1. / 239; 

double* gen_machin_vector(double x, size_t n) {
    double *vector = malloc( n * sizeof(double) );
    for (size_t i = 1; i <= n; i++) {
        vector[i] = pow (-1., i-1) * pow(x, 2*i-1) / (2*i-1);
    }
    return vector;
}


double sum(double *vector, size_t n) {

    double s = 0;
    for (size_t i = 0; i < n; i++) {
        s += vector[i];
    }
    return s;
}

double machin_formula(int n) {
  double sum_x1 = sum( gen_machin_vector(X1, n), n );
  double sum_x2 = sum( gen_machin_vector(X2, n), n );
  return 16 * sum_x1 - 4 * sum_x2;
}

double machin_pi() {
    return 16 * atan(X1) - 4 * atan(X2);
}

double abs_error(double s) {
  return fabs(s - M_PI);
}

void unit_test(size_t n) {

  double approx = 0.;
  
  if ( n < 30 )  approx = machin_formula(n); 
  else approx = machin_pi();

  printf( "n = %zu \n", n );
  printf( "Machin pi = %f \n", machin_pi() );
  printf( "Machin sum = %f \n", approx );
  printf( "Error = %f \n", abs_error(approx) );

}

void verification_test(char *test_name, int n) {

  double i = 0;

  FILE *pFile = fopen("machin.txt", "w+");
  fprintf( pFile,"**************************\n %s:\n", test_name );
  fputs( "**************************\n", pFile );

  if ( n < 12 ) { 
    for ( size_t k=1; k <= n; k++ ) {
      i = pow(2., k);
      fprintf(pFile, "k = %zu \t Error = %f \n", k, abs_error(machin_formula(i)) );
    }
  }
  else fprintf(pFile, "n = %d \t Error = %f \n", n, abs_error(machin_pi()) );
  
  fclose(pFile);
}


int main(int argc, char **argv) {
    
    size_t n = atoi(argv[1]);

    unit_test( 3 );
    verification_test("Machin vtest ", n);
  
    return 0;
}

