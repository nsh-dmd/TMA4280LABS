#include "util.h"
#include "zeta0.c"
#include "mach0.c"

void verification_test(char *test_name, int n) {

  double i, error = 0;

  FILE *pFile = fopen("vtest.txt", "w+");
  fprintf( pFile,"**************************\n %s:\n", test_name );
  fputs( "**************************\n", pFile );

  if ( n < 25 ) {
    for ( size_t k=1; k <= n; k++ ) {
      i = pow(2., k);
      switch (test_name) {
          case 'machin': error = abs_error(machin_formula(i)); break;
          case 'reimann': error = abs_error(reimann_pi(i)); break;
      }
      fprintf(pFile, "k = %zu \t Error = %f \n", k,  error);
    }
  }
  else fprintf(pFile, "n = %d \t Error = %f \n", n, abs_error(machin_pi()) );

  fclose(pFile);
}

int main(int argc, char const **argv) {
    int n = atoi(argv[1]);
    verification_test(n);
    return 0;
}
