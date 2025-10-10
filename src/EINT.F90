module EINT

  use FC_Kinds, only: &
    C_INT, C_SIZE_T, &
    C_FLOAT, C_DOUBLE

  use, intrinsic :: ISO_C_Binding

  use EINT_Core, only: &
    extrapolation_driverC_FLOAT, &
    extrapolation_driverC_DOUBLE

  implicit none

  private

  public :: extrapolation_float
  public :: extrapolation_double

contains

  function extrapolation_float(array, sz, base) result(u) &
    BIND(C, NAME="extrapolation_float")

    integer(C_SIZE_T), intent(in), value :: sz
    real(C_FLOAT), intent(in)        :: array(sz)
    integer(C_INT), intent(in), value :: base

    real(C_FLOAT) :: u

    u = extrapolation_driverC_FLOAT(array, base)

  end function extrapolation_float

  function extrapolation_double(array, sz, base) result(u) &
    BIND(C, NAME="extrapolation_double")

    integer(C_SIZE_T), intent(in), value :: sz
    real(C_DOUBLE), intent(in)        :: array(sz)
    integer(C_INT), intent(in), value :: base

    real(C_DOUBLE) :: u

    u = extrapolation_driverC_DOUBLE(array, base)

  end function extrapolation_double

end module EINT
