#include "util.h"
#include "zeta/zeta0.h"
#include "mach/mach0.h"

 void unit_test(size_t n, char* test_name) {

   double approx = 0.;

   if ( strcmp(test_name, "machin") == 0 ) {
     Vector_Tuple t = gen_machin_vector(n);
     approx = machin_formula(n, t);
   }
   else if( strcmp(test_name, "reimann") == 0 ) {
       double *v = gen_reimann_vector(n);
       approx = reimann_pi(n, v);
       free(v);
   }
   else {
       printf("\"%s\" is not defined. Select reimann/machin\n", test_name);
       return;
   }

   printf( "Unit test name = %s \n", test_name );
   printf( "n = %zu \n", n );
   printf( "Calculated pi = %f \n", approx );
   printf( "Error = %f \n", abs_error(approx) );
 }
