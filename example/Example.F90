program Improper_Integral_Example

  !In this example we compute an improper integral
  !while demonstrating the Fortran API.

  !IMPROPER INTEGRALS FROM 1 TO INFINITY.
  !==================================================================!
  !We consider improper integrals of the form:
  !  I = \int_{1}^{\infty} f(x) dx.
  !For the integral to exist, the Cauchy principal value (P. V.)
  !needs to exist,
  !(P. V.) I = \lim_{z\to\infty}\int_{1}^{z} f(x) dx =
  !            K \in \mathbb{C}.
  !We consider first the change of variables [x = 1/u]:
  !  x = 1/u => u = 1/x; x = 1 => u = 1, x \to \infty => u \to 0^+;
  !  dx = -du/u^2.
  !So,
  !(P. V.) I = \lim_{\eta\to 0^+}\int_{\eta}^{1} f(1/u)/u^2 du.
  !Now we discretize the variable u in N points:
  !  u -> u_i = (i-1)/(N-1) = \Delta u (i-1) | i\in[1, N].
  !We observe that to apply the extrapolation method
  !we need the evaluation of
  !  g(u) = f(1/u)/u^2 for all the u_i\in[0, 1]. Which will be stored
  !in a data array which we will feed to EINT.
  !In this aspect, we notice that the direct numerical evaluation
  !of g(0) is undefined, and only exists as the limit
  !  g(0) = \lim_{u\to 0^+} f(1/u)/u^2 = \lim_{x\to\infty} x^2 f(x),
  !which needs to be finite for the integral to converge.
  !This quantity cannot be computed numerically.
  !==================================================================!

  !In this example we will consider the integral of
  !  f(x) = 3x^4/(x^6 + 5) from 0 to infinity. The exact result is
  !  I = \pi/5^{1/6}.
  !We will separate the integral in 2, one
  !from 0 to 1 and the other from 1 to infinity.

  !Load the C types.
  use, intrinsic :: ISO_C_BINDING, only: size_t => C_SIZE_T, &
                                                                int4 => C_INT, &
                                                                  dp => C_DOUBLE

  !Fortran I/O.
  use, intrinsic :: ISO_FORTRAN_ENV, only: stdout => output_unit

  !Local definitions
  integer(size_t) :: N
  integer(size_t) :: i

  integer(int4) :: base

  real(dp), allocatable :: arr(:)
  real(dp) :: u

  real(dp) :: result

  !The exact result
  real(dp) :: exact_result = acos(-1.0_dp)/(5.0_dp)**(1.0_dp/6.0_dp)

  !Rectangle approximation
  real(dp) :: sum1, sum2, sum

  character(len=256) :: aux

  !Load EINT interfaces.
#include <EINT_F.h>

  !We choose N such that N - 1 is a power of base,
  base = 2
  N = int(base, size_t)**6 + 1

  allocate (arr(N))
  sum1 = 0.0_dp

  !Regular integral from 0 to 1.
  !Evaluate the function f(x) in the [0, 1] range.
  do i = 2, N
    u = real(i - 1, dp)/real(N - 1, dp)
    arr(i) = f(u)
    sum1 = sum1 + arr(i)
  end do
  result = extrapolation_double(arr, N, base)
  sum1 = sum1/real(N - 1, dp)

  sum2 = 0.0_dp
  !Improper integral from 1 to infinity.
  !Evaluate the function g(u) in the (0, 1] range.
  do i = 2, N
    u = real(i - 1, dp)/real(N - 1, dp)
    arr(i) = f(1.0_dp/u)/u**2
    sum2 = sum2 + arr(i)
  end do
  !Evaluate g(0) separately, the limit of x^2 f(x) at infinity.
  arr(1) = 3.0_dp
  sum2 = sum2 + arr(1)
  sum2 = sum2/real(N - 1, dp)

  result = result + extrapolation_double(arr, N, base)
  sum = sum1 + sum2

  write (stdout, "(A)") ""
  write (stdout, "(A)") "Extrapolation:"
  write (stdout, "(A)") ""
  write (aux, "(F25.18)") result
  write (stdout, "(A)") "RESULT = "//trim(adjustl(aux))//"."
  write (aux, "(F25.18)") exact_result
  write (stdout, "(A)") "EXACT RESULT = "//trim(adjustl(aux))//"."
  write (aux, "(F25.18)") abs(result - exact_result)
  write (stdout, "(A)") "ABSOLUTE ERROR = "//trim(adjustl(aux))//"."
  write (aux, "(F15.8)") 100.0_dp*abs(result - exact_result)/abs(exact_result)
  write (stdout, "(A)") "RELATIVE ERROR = "//trim(adjustl(aux))//"%."
  write (stdout, "(A)") ""

  write (stdout, "(A)") "Rectangle:"
  write (stdout, "(A)") ""
  write (aux, "(F25.18)") sum
  write (stdout, "(A)") "RESULT = "//trim(adjustl(aux))//"."
  write (aux, "(F25.18)") exact_result
  write (stdout, "(A)") "EXACT RESULT = "//trim(adjustl(aux))//"."
  write (aux, "(F25.18)") abs(sum - exact_result)
  write (stdout, "(A)") "ABSOLUTE ERROR = "//trim(adjustl(aux))//"."
  write (aux, "(F15.8)") 100.0_dp*abs(sum - exact_result)/abs(exact_result)
  write (stdout, "(A)") "RELATIVE ERROR = "//trim(adjustl(aux))//"%."
  write (stdout, "(A)") ""

  deallocate (arr)

contains

  function f(x)
    real(dp), intent(in) :: x
    real(dp) :: f
    f = 3*x**4/(x**6 + 5)
  end function f

end program Improper_Integral_Example
