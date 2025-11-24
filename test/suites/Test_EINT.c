#include "EINT_C.h"

void EINT_Test_check_float_trivial_case() {

  /*Integrate a single point.*/

  static float tol = 10.0 * FLT_EPSILON;

  size_t N    = 1;
  int    base = 2;

  float *arr = (float *)malloc(N * sizeof(float));
  float  x;

  for (size_t i = 1; i <= N; i++) {
    x          = (float)0;
    arr[i - 1] = x;
  }

  float result = extrapolation_float(arr, N, base);
  assert(fabs(result - (float)0) <= tol);
  free(arr);
  fprintf(stderr, ">>Test OK\n");
}

void EINT_Test_check_double_trivial_case() {

  /*Integrate a single point.*/

  static double tol = 10.0 * DBL_EPSILON;

  size_t N    = 1;
  int    base = 2;

  double *arr = (double *)malloc(N * sizeof(double));
  double  x;

  for (size_t i = 1; i <= N; i++) {
    x          = (double)0;
    arr[i - 1] = x;
  }

  double result = extrapolation_double(arr, N, base);
  assert(fabs(result - (double)0) <= tol);
  free(arr);
  fprintf(stderr, ">>Test OK\n");
}

void EINT_Test_check_float_1stOrdPoly_nE() {

  /*Integrate x from 0 to 1 = 1/2. No extrapolation.*/

  static float tol = 10.0 * FLT_EPSILON;

  size_t N    = 10;
  int    base = 2;

  float *arr = (float *)malloc(N * sizeof(float));
  float  x;

  for (size_t i = 1; i <= N; i++) {
    x          = ((float)(i - 1)) / ((float)(N - 1));
    arr[i - 1] = x;
  }

  float result = extrapolation_float(arr, N, base);
  assert(fabs(result - (float)0.5) <= tol);
  free(arr);
  fprintf(stderr, ">>Test OK\n");
}

void EINT_Test_check_double_1stOrdPoly_nE() {

  /*Integrate x from 0 to 1 = 1/2. No extrapolation.*/

  static double tol = 10.0 * DBL_EPSILON;

  size_t N    = 10;
  int    base = 2;

  double *arr = (double *)malloc(N * sizeof(double));
  double  x;

  for (size_t i = 1; i <= N; i++) {
    x          = ((double)(i - 1)) / ((double)(N - 1));
    arr[i - 1] = x;
  }

  double result = extrapolation_double(arr, N, base);
  assert(fabs(result - (double)0.5) <= tol);
  free(arr);
  fprintf(stderr, ">>Test OK\n");
}

void EINT_Test_check_float_1stOrdPoly_E() {

  /*Integrate x from 0 to 1 = 1/2. With extrapolation.*/

  static float tol = 10.0 * FLT_EPSILON;

  size_t N    = 11;
  int    base = 2;

  float *arr = (float *)malloc(N * sizeof(float));
  float  x;

  for (size_t i = 1; i <= N; i++) {
    x          = ((float)(i - 1)) / ((float)(N - 1));
    arr[i - 1] = x;
  }

  float result = extrapolation_float(arr, N, base);
  assert(fabs(result - (float)0.5) <= tol);
  free(arr);
  fprintf(stderr, ">>Test OK\n");
}

void EINT_Test_check_double_1stOrdPoly_E() {

  /*Integrate x from 0 to 1 = 1/2. With extrapolation.*/

  static double tol = 10.0 * DBL_EPSILON;

  size_t N    = 11;
  int    base = 2;

  double *arr = (double *)malloc(N * sizeof(double));
  double  x;

  for (size_t i = 1; i <= N; i++) {
    x          = ((double)(i - 1)) / ((double)(N - 1));
    arr[i - 1] = x;
  }

  double result = extrapolation_double(arr, N, base);
  assert(fabs(result - (double)0.5) <= tol);
  free(arr);
  fprintf(stderr, ">>Test OK\n");
}

void EINT_Test_check_float_4thOrdPoly_nE() {

  /*Integrate x^4 from 0 to 1 = 1/5. No extrapolation.*/

  static float tol = 10.0 * FLT_EPSILON;

  size_t N    = 10;
  int    base = 2;

  float *arr = (float *)malloc(N * sizeof(float));
  float  x;

  for (size_t i = 1; i <= N; i++) {
    x          = ((float)(i - 1)) / ((float)(N - 1));
    arr[i - 1] = x * x * x * x;
  }

  float result = extrapolation_float(arr, N, base);
  // Should fail by approx 0.004.
  assert(fabs(result - (float)0.2) >= tol);
  free(arr);
  fprintf(stderr, ">>Test OK\n");
}

void EINT_Test_check_double_4thOrdPoly_nE() {

  /*Integrate x^4 from 0 to 1 = 1/5. No extrapolation.*/

  static double tol = 10.0 * DBL_EPSILON;

  size_t N    = 10;
  int    base = 2;

  double *arr = (double *)malloc(N * sizeof(double));
  double  x;

  for (size_t i = 1; i <= N; i++) {
    x          = ((double)(i - 1)) / ((double)(N - 1));
    arr[i - 1] = x * x * x * x;
  }

  double result = extrapolation_double(arr, N, base);
  // Should fail by approx 0.004.
  assert(fabs(result - (double)0.2) >= tol);
  free(arr);
  fprintf(stderr, ">>Test OK\n");
}

void EINT_Test_check_float_4thOrdPoly_E() {

  /*Integrate x from 0 to 1 = 1/5. With extrapolation.*/

  static float tol = 10.0 * FLT_EPSILON;

  size_t N    = 11;
  int    base = 2;

  float *arr = (float *)malloc(N * sizeof(float));
  float  x;

  for (size_t i = 1; i <= N; i++) {
    x          = ((float)(i - 1)) / ((float)(N - 1));
    arr[i - 1] = x * x * x * x;
  }

  float result = extrapolation_float(arr, N, base);
  // Should fail by approx 0.00001.
  assert(fabs(result - (float)0.2) >= tol);
  free(arr);
  fprintf(stderr, ">>Test OK\n");
}

void EINT_Test_check_double_4thOrdPoly_E() {

  /*Integrate x from 0 to 1 = 1/5. With extrapolation.*/

  static double tol = 10.0 * DBL_EPSILON;

  size_t N    = 11;
  int    base = 2;

  double *arr = (double *)malloc(N * sizeof(double));
  double  x;

  for (size_t i = 1; i <= N; i++) {
    x          = ((double)(i - 1)) / ((double)(N - 1));
    arr[i - 1] = x * x * x * x;
  }

  double result = extrapolation_double(arr, N, base);
  // Should fail by approx 0.00001.
  assert(fabs(result - (double)0.2) >= tol);
  free(arr);
  fprintf(stderr, ">>Test OK\n");
}
