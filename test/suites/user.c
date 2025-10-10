#include "EINT.h"

void usertest() {

  size_t N    = 11;
  int    base = 2;

  float *arr = (float *)malloc(N * sizeof(float));

  float sum = 0.0;
  for (size_t i = 0; i < N; i++) {
    arr[i] = (float)i;
    sum += (float)i;
  }
  sum = sum / ((float)N - 1);

  fprintf(stderr, "%f, %f\n", extrapolation_float(arr, N, base), sum);

  free(arr);
}
