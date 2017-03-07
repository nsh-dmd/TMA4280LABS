#include "util.h"

double sum (double *vector, size_t n) {
  double s = 0;
  for (size_t i = 0; i < n; i++)
    s += vector[i];
  return s;
}

double abs_error(double s) {
  return fabs(s - PI);
}
