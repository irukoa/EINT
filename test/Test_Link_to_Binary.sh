#!/bin/bash
echo "<==========================================================>"
echo ""
echo "Starting test: link debug library to binary (C user)."
echo ""
make debug > /dev/null 2>&1
rm *.gcno > /dev/null 2>&1
cat > user.c <<- "EOF"
#include "EINT_C.h"
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

echo ""
echo "Starting test: link debug library to binary (Fortran user)."
echo ""
cat > user.F90 <<- "EOF"
program user_F

  use, intrinsic :: ISO_C_BINDING, only: C_SIZE_T, C_INT, C_FLOAT
  use, intrinsic :: ISO_FORTRAN_ENV, only: stdout => output_unit

  integer(C_SIZE_T) :: N = 11
  integer(C_INT) :: base = 2

  real(C_FLOAT), allocatable :: arr(:)

  integer(C_SIZE_T) :: i
  real(C_FLOAT) :: x

  real(C_FLOAT) :: result

  character(len=256) :: aux

#include "EINT_F.h"

  allocate (arr(N))

  do i = 1, N
    x = real(i - 1, C_FLOAT)/real(N - 1, C_FLOAT)
    arr(i) = x
  end do

  result = extrapolation_float(arr, N, base)
  write (aux, "(F12.6)") result
  write (stdout, "(A)") "Sucessfull link!"
  deallocate (arr)
  write (stdout, "(A)") "Result is "//trim(adjustl(aux))//"."

end program user_F

EOF
gfortran -L./dbgbin -I./inc -Wl,-rpath=./dbgbin -g -Wall user.F90 -o user.o -leint
rm user.F90
./user.o
rm user.o
echo ""
echo "<==========================================================>"
