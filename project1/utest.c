#include "util.h"
#include "zeta0.c"
#include "mach0.c"

 void unit_test(size_t n, char* test_name) {

   double approx = 0.;

   if ( strcmp(test_name, "machin") == 0 )  approx = machin_formula(n);
   else if( strcmp(test_name, "reimann") == 0 ) approx = reimann_pi(n);
   else {
       printf("\"%s\" is not defined. Select reimann/machin\n", test_name);
       return;
   }

   printf( "Unit test name = %s \n", test_name );
   printf( "n = %zu \n", n );
   printf( "Calculated pi = %f \n", approx );
   printf( "Error = %f \n", abs_error(approx) );
 }

 int main(int argc, char const **argv) {
     unit_test( 3, "machin" );
     unit_test( 3, "reimann" );
     return 0;
 }
