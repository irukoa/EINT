#ifndef EINT_lib
#define EINT_lib

#include <stdlib.h>

float extrapolation_float(float *array,
                          size_t sz,
                          int    base);

double extrapolation_double(double *array,
                            size_t  sz,
                            int     base);

#endif
