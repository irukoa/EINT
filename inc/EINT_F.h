#ifndef EINT_F_lib
#define EINT_F_lib
// clang-format off
  interface
    function extrapolation_float(arr, sz, base) result(u) bind(c, name="extrapolation_float")
      use, intrinsic :: ISO_C_BINDING, only: C_SIZE_T, C_FLOAT, C_INT
      integer(C_SIZE_T), intent(in), value :: sz
      real(C_FLOAT), intent(in) :: arr(sz)
      integer(C_INT), intent(in), value :: base

      real(C_FLOAT) :: u
    end function extrapolation_float
  end interface

  interface
    function extrapolation_double(arr, sz, base) result(u) bind(c, name="extrapolation_double")
      use, intrinsic :: ISO_C_BINDING, only: C_SIZE_T, C_DOUBLE, C_INT
      integer(C_SIZE_T), intent(in), value :: sz
      real(C_DOUBLE), intent(in) :: arr(sz)
      integer(C_INT), intent(in), value :: base

      real(C_DOUBLE) :: u
    end function extrapolation_double
  end interface
// clang-format on
#endif
