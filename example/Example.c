#include <EINT_C.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int main() {

  /*This example demonstrates the extrapolation method.*/

  /*Integrate sin(x)/x from 0 to pi = Si(pi).
  We employ the extrapolation method with N = 65 = 2^6 + 1 points.
  The expected accuracy is O(h^{2*6}), with h = pi/(64).*/

  const double pi = acos((double)-1.0);

  size_t N    = 65;
  int    base = 2;

  // The exact result is:
  const double exact_result = (double)1.851937051982466170;

  // We also compute the rectangle approximation.
  double sum = (double)0.0;

  double *arr = (double *)malloc(N * sizeof(double));
  double  x;

  arr[0] = (double)1.0;
  sum += arr[0];
  for (size_t i = 2; i <= N; i++) {
    x          = pi * ((double)(i - 1)) / ((double)(N - 1));
    arr[i - 1] = sin(x) / x;
    sum += arr[i - 1];
  }
  sum = pi * sum / ((double)(N - 1));

  double result = extrapolation_double(arr, N, base);
  result        = pi * result;
  free(arr);

  fprintf(stdout, "\n");
  fprintf(stdout, "Extrapolation:\n");
  fprintf(stdout, "\n");
  fprintf(stdout, "RESULT = %.18e.\n", result);
  fprintf(stdout, "EXACT RESULT = %.18e.\n", exact_result);
  fprintf(stdout, "ABSOLUTE ERROR = %.18e.\n", fabs(result - exact_result));
  fprintf(stdout, "RELATIVE ERROR = %.8e %%.\n",
          100 * fabs(result - exact_result) / fabs(exact_result));
  fprintf(stdout, "\n");

  fprintf(stdout, "Rectangle:\n");
  fprintf(stdout, "\n");
  fprintf(stdout, "RESULT = %.18e.\n", sum);
  fprintf(stdout, "ABSOLUTE ERROR = %.18e.\n", fabs(sum - exact_result));
  fprintf(stdout, "RELATIVE ERROR = %.8e %%.\n",
          100 * fabs(sum - exact_result) / fabs(exact_result));
  fprintf(stdout, "\n");
}
