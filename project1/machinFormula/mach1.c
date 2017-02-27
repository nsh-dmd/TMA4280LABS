#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

static const double X1 = 1. / 5;
static const double X2 = 1. / 239;

double* gen_machin_vector(double x, size_t n) {
    double *vector = malloc( n * sizeof(double) );
    for (size_t i = 1; i <= n; i++) {
        vector[i] = pow (-1., i-1) * pow(x, 2*i-1) / (2*i-1);
    }
    return vector;
}

double calculate_sum(double *vector, size_t n) {

    double s = 0;
    for (size_t i = 0; i < n; i++) {
        s += vector[i];
    }
    return s;
}

double machin_formula(int n) {
  double sum_x1 = calculate_sum( gen_machin_vector(X1, n), n );
  double sum_x2 = calculate_sum( gen_machin_vector(X2, n), n );
  return 16 * sum_x1 - 4 * sum_x2;
}

double machin_pi() {
    return 16 * atan(X1) - 4 * atan(X2);
}

double abs_error(double s) {
  return fabs(s - M_PI);
}
/**
void unit_test(size_t n) {

  double approx = 0.;

  if ( n < 30 )  approx = machin_formula(n);
  else approx = machin_pi();

  printf( "n = %zu \n", n );
  printf( "Machin pi = %f \n", machin_pi() );
  printf( "Machin sum = %f \n", approx );
  printf( "Error = %e \n", abs_error(approx) );

}

void verification_test(char *test_name, int n) {

  double i = 0;

  FILE *pFile = fopen("machin.txt", "w+");
  fprintf( pFile,"**************************\n %s:\n", test_name );
  fputs( "**************************\n", pFile );

  if ( n < 25 ) {
    for ( size_t k=1; k <= n; k++ ) {
      i = pow(2., k);
      fprintf(pFile, "k = %zu \t Error = %e \n", k, abs_error(machin_formula(i)) );
    }
  }
  else fprintf(pFile, "n = %d \t Error = %e \n", n, abs_error(machin_pi()) );

  fclose(pFile);
}
*/
void initialize_MPI_env(int rank, int nproc) {
  // Initializing MPI environment
  MPI_Init(rank, nproc);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);
}
double* distribute_vector ( int n, doubel *vector, int nproc ) {
    int rest = (double)n % nproc;
    int k = n/nproc;
    double *scattered_v = (double *) malloc( k * sizeof(double) );
    MPI_Scatter( vector, k, MPI_DOUBLE, scattered_v, k, MPI_DOUBLE, 0, MPI_COMM_WORLD );
    return scattered_v;
}

int main(int argc, char **argv) {

    size_t n = atoi(argv[1]);
    if ( argc < 2 || (x & (x - 1)) ) {
      printf("Usage:\n");
      printf("  make n\n\n");
      printf("Arguments:\n");
      printf("  n: the problem size (must be a power of 2)\n");
      MPI_Finalize();
      return 1;
    }

    double partial_sum, total_sum;
    int rank, nproc;

    double start_time = MPI_Wtime();
    // Initializing MPI environment
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    double *vector;
    double *scattered_v;

    if (rank == 0) {
        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
        scattered_v = distribute_vector(int n, double* vector, int nproc);
        MPI_Reduce( &partial_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        printf("Error = %e\n", );
        free(vector);
        printf ("Elapsed time =  %f \n", MPI_Wtime() - start_time);

    }

    partial_sum = compute_sum(calculate_sum, n);
    free(scattered_v);
    MPI_Finalize();

    return 0;
}
