#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mpi.h>

#define PI 3.14159265358979323846
#define X1 1. / 5
#define X2 1. / 239

typedef struct {
    double* v1;
    double* v2;
} Vector_Tuple;

// static const double X1 = 1. / 5;
// static const double X2 = 1. / 239;
// static const double PI = 3.14159265358979323846;

double calculate_sum (double *vector, int n);
double abs_error(double s);
int power_of_2(int n);
void print_to_file(char* test_name, int n, int nproc, double walltime, double error);
