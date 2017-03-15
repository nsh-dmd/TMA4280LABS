#include "utest.c"
#include "vtest.c"

int main(int argc, char **argv) {
    int n = atoi(argv[1]);
    if ( argc < 2 || !power_of_2(n) ) {
      return 1;
    }
    // unit test for n=3
    unit_test(3, "machin");
    unit_test(3, "reimann");

    // verification test
    // verification_test(n);

    // hybrid mach
    // hybrid_mach(argc, argv);


    return 0;
}
