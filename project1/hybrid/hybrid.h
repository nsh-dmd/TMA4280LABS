#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <omp.h>
#include "mpi.h"

#define PI 3.14159265358979323846
#define X1 1. / 5
#define X2 1. / 239

typedef struct {
    double* v1;
    double* v2;
} Vector_Tuple;

double calculate_sum (double *vector, int n);
double abs_error(double s);
void print_to_file(char* test_name, int n, int nproc, double walltime, double error);
int power_of_2(int n);
double machin_formula(int n, Vector_Tuple t);
Vector_Tuple gen_machin_vector ( int n );
double* gen_reimann_vector (int n);
double reimann_pi (int n, double *v);
