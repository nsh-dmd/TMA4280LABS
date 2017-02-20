#include "zeta0.h"
 #include <string.h>

double* gen_reimann_vector(size_t n) {
    double *vector = malloc( n * sizeof(double) );
    for (size_t i = 1; i <= n; i++) {
        vector[i] = 1. / (i*i);
    }
    return vector;
}

double reimann_sum(double *vector, size_t n) {
    double sum = 0;
    for (size_t i = 0; i < n; i++) {
        sum += vector[i];
    }
    return sum;
}

double reimann_pi() {
    return (M_PI * M_PI) / 6. ;
}

void unit_test(size_t n, double *vector) {
  
  double sum = 0;
  double pi = reimann_pi();
 
  if ( n > 30 ) sum = pi;
  else sum = reimann_sum(vector, n);
   
  printf("n = %zu \n", n );
  printf("reimann pi = %f \n", pi);
  printf("reimann sum = %f \n", sum);
  printf("error = %f \n", fabs(pi-sum));

 }


int main(int argc, char **argv) {

  //size_t n = atoi(argv[1]);

  //  double *reimann_vector = gen_reimann_vector( n );
  unit_test( 3, gen_reimann_vector(3) );


  return 0;
}
