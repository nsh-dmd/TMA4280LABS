#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265358979323846
#define X1 1. / 5
#define X2 1. / 239

// static const double X1 = 1. / 5;
// static const double X2 = 1. / 239;
// static const double PI = 3.14159265358979323846;

double sum (double *vector, size_t n);
double abs_error(double s);
