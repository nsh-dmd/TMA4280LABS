#include "utest.c"
#include "vtest.c"

int main(int argc, char const *argv[]) {
  unit_test( 3, "machin" );
  unit_test( 3, "reimann" );
  int n = atoi(argv[1]);
  verification_test(n);
  return 0;
}
