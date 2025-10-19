#include "EINT.h"

void Integrate_Stiff() {

  /*Integrate exp(0.5*x*sin[pi*x]) from 1 to 5 = 8.55626*/
  /*Employ 1025 datapoints.*/

  static double tol = 1000.0 * DBL_EPSILON;
  const double  pi  = acos((double)-1.0);

  const double reference = 8.556256383674835;

  size_t N = 1015;

  double a = (double)1;
  double b = (double)5;

  double *arr = (double *)malloc(N * sizeof(double));
  double  x;

  for (size_t i = 1; i <= N; i++) {
    x          = a + (b - a) * ((double)(i - 1)) / ((double)(N - 1));
    arr[i - 1] = exp((double)0.5 * x * sin(pi * x));
  }

  double result = extrapolation_double(arr, N, 2);
  result        = (double)(b - a) * result;
  fprintf(stderr, "\\int_{1}^{5} dx e^{x\\sin(\\pi x)/2} \\approx %.18e.\n",
          result);
  assert(fabs(result - reference) <= tol);
  free(arr);
  fprintf(stderr, ">>Test OK\n");
}

void Integrate_Random_Poly() {

  /*Integrate a random polynomial from 0 to 1.*/

  unsigned int seed = time(0);
  float        rnd;

  const unsigned int min_datasize_log = 10;
  const unsigned int max_datasize_log = 20;
  unsigned int       datasize_log;
  size_t             datasize;

  rnd = (float)rand_r(&seed) / ((float)RAND_MAX);
  datasize_log =
      min_datasize_log +
      (unsigned int)lroundf((float)(max_datasize_log - min_datasize_log) * rnd);
  datasize = 1;
  for (size_t i = 0; i < datasize_log; i++) {
    datasize = datasize * 2;
  }
  datasize = datasize + 1;

  fprintf(stderr, ">>>> SAMPLES = %li.\n", datasize);

  const unsigned int min_order = 2;
  const unsigned int max_order = 20;
  unsigned int       order;

  rnd = (float)rand_r(&seed) / ((float)RAND_MAX);
  order =
      min_order + (unsigned int)lroundf((float)(max_order - min_order) * rnd);

  fprintf(stderr, ">>>> POLYNIOMIAL ORDER = %i.\n", order);

  const double min_coef = (double)0.0;
  const double max_coef = (double)10.0;
  double      *coefs    = (double *)malloc(order * sizeof(double));
  for (unsigned int i = 0; i < order; i++) {
    rnd      = (float)rand_r(&seed) / ((float)RAND_MAX);
    coefs[i] = min_coef + (max_coef - min_coef) * (double)(rnd);
  }

  double *arr = (double *)malloc(datasize * sizeof(double));
  double  x;

  // Computes f(x) = coefs[0]*x + coefs[1]*x^2 + ...
  for (size_t i = 1; i <= datasize; i++) {
    x          = ((double)(i - 1)) / ((double)(datasize - 1));
    arr[i - 1] = (double)0.0;
    for (unsigned int j = 0; j < order; j++) {
      arr[i - 1] += coefs[j] * pow(x, (double)(j + 1));
    }
  }

  double result = extrapolation_double(arr, datasize, 2);
  // Computes I = coefs[0]/2 + coefs[1]/3 + ...
  double exact_result = (double)0.0;
  for (unsigned int i = 0; i < order; i++) {
    exact_result += coefs[i] / ((double)(i + 2));
  }

  fprintf(stderr, ">>>> RESULT = %.18e.\n", result);
  fprintf(stderr, ">>>> EXACT RESULT = %.18e.\n", exact_result);
  fprintf(stderr, ">>>> ABSOLUTE ERROR = %.18e.\n",
          fabs(result - exact_result));
  fprintf(stderr, ">>>> RELATIVE ERROR = %.8e %%.\n",
          100 * fabs(result - exact_result) / fabs(exact_result));

  free(coefs);
  free(arr);
}
