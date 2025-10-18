#!/bin/bash
echo "<==========================================================>"
echo ""
echo "Starting test: link debug library to binary."
echo ""
make debug > /dev/null 2>&1
rm *.gcno > /dev/null 2>&1
cat > user.c <<- "EOF"
#include "EINT.h"
#include <stdio.h>
#include <stdlib.h>
int main() {

  /*Integrate x from 0 to 1 = 1/2. With extrapolation.*/

  size_t N    = 11;
  int    base = 2;

  float *arr = (float *)malloc(N * sizeof(float));
  float  x;

  for (size_t i = 1; i <= N; i++) {
    x          = ((float)(i - 1)) / ((float)(N - 1));
    arr[i - 1] = x;
  }

  float result = extrapolation_float(arr, N, base);
  fprintf(stdout, "Sucessfull link!\n");
  free(arr);
  fprintf(stdout, "Result is %f.\n", result);
}

EOF
gcc -L./dbgbin -I./inc -Wl,-rpath=./dbgbin -g -Wall user.c -o user.o -leint
rm user.c
./user.o
rm user.o
echo ""
echo "<==========================================================>"
