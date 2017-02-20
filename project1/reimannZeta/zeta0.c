#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double* gen_reimann_vector(size_t n) {

  double *vector = malloc( n * sizeof(double) );

   for (size_t i = 1; i <= n; i++) {
        vector[i] = 1. / (i*i);
  }
  return vector;
}

double sum(double *vector, size_t n) {

  double s = 0;
  for (size_t i = 0; i < n; i++)
    s += vector[i];

  return s;
}

double reimann_pi() {
  return (M_PI * M_PI) / 6. ;
}

double abs_error(double x) {
  return fabs( x - reimann_pi() );
}

void unit_test(size_t n, double *vector) {
  
  printf("unit testing \n");
  
  double reimann_approx = 0;
  double pi = reimann_pi();
 
  if ( n > 12 ) reimann_approx = pi;
  else reimann_approx = sum(vector, n);
   
  printf("n = %zu \n", n );
  printf("reimann pi = %f \n", pi);
  printf("reimann sum = %f \n", reimann_approx);
  printf("error = %f \n", abs_error(reimann_approx));

  free(vector);
 }

void verification_test(char *test_name, int n) {

  double i = 0;
 
  FILE *pFile = fopen( "reimann.txt", "w+" );
  fprintf( pFile,"**************************\n %s n = %d\n", test_name, n );
  fputs("**************************\\n", pFile );
  
  if ( n < 12 ) { 
    for ( size_t k=1; k <= n; k++ ) {
      i = pow(2., k);
      double *vector = gen_reimann_vector(i) ;
      fprintf(pFile, "k = %zu \t Error = %f \n", k, abs_error(sum(vector, i)) );
      //free(vector);
     }
  }    
  else fprintf( pFile, "k = %d \t Error = %f \n", n, abs_error(reimann_pi()) );
  
  fclose(pFile);
}

int main(int argc, char **argv) {

  int n = atoi(argv[1]);

  unit_test( 3, gen_reimann_vector(3) );
  verification_test("reimann vtest", n);

  return 0;
}
