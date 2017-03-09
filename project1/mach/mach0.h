#include "../util.h"

typedef struct {
  double* v1;
  double* v2;
} Vector_Tuple;

Vector_Tuple gen_machin_vector(int n);
double machin_formula(int n, Vector_Tuple t);
double machin_pi();
