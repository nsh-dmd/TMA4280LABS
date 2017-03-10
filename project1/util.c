#include "util.h"

double calculate_sum (double *vector, int n) {
  double s = 0;
  for (size_t i = 0; i < n; i++)
    s += vector[i];
  return s;
}

double abs_error(double s) {
  return fabs(s - PI);
}

int power_of_2(int n) {

    if ((n & (n - 1)) ) {
        printf("Usage:\n");
        printf("  make n\n\n");
        printf("Arguments:\n");
        printf("  n: the problem size (must be a power of 2)\n");
        return 0;
    }
    return 1;
}

void print_to_file(char* test_name, int n, int nproc, double walltime, double error) {
    char name[15];
    strcpy(name, test_name);
    FILE *pFile = fopen(strcat(name, ".txt"), "a+");
    fprintf( pFile,"*************%s*************\n", test_name );
    fputs( "**************************\n", pFile );
    fprintf(pFile,"n = %d\nnproc = %d\nwalltime = %f\nerr = %e\n\n", n, nproc, walltime, error);
}
