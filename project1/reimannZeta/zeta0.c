#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

double abs_error(double x) {
  return fabs(x-reimann_pi());
}

void unit_test(size_t n, double *vector) {
  
  double sum = 0;
  double pi = reimann_pi();
 
  if ( n > 30 ) sum = pi;
  else sum = reimann_sum(vector, n);
   
  printf("n = %zu \n", n );
  printf("reimann pi = %f \n", pi);
  printf("reimann sum = %f \n", sum);
  printf("error = %f \n", abs_error(sum));
 }

void verification_test(char *test_name, int n) {

  double i = 0;
  double error;

  FILE *file = fopen("vtest.txt", "a+");
  fprintf(file,"************************************\n %s:\n ************************************\n", test_name);
  for (size_t k=1; k <= 24; k++) {
    i = pow(2., k);
    double *vector = gen_reimann_vector(i) ;
    fprintf(file, "k = %zu \t Error = %f \n", k, abs_error(reimann_sum(vector, i)) );
  }
  fclose(file);
}
int main(int argc, char **argv) {

  int n = atoi(argv[1]);

  //  double *reimann_vector = gen_reimann_vector( n );
  unit_test( 3, gen_reimann_vector(3) );
  verification_test("vtest n=2^k", n);

  return 0;
}
