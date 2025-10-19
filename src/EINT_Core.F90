module EINT_Core

  use FC_Kinds
  use Prime_Factors

  implicit none

  private

  public :: extrapolation_driverC_FLOAT
  public :: extrapolation_driverC_DOUBLE

contains

  function extrapolation_driverC_FLOAT(array, base) result(u)

    real(C_FLOAT), intent(in)           :: array(:)
    integer(C_INT), intent(in), optional :: base

    real(C_FLOAT) :: u

    integer(C_INT) :: lbase
    integer(C_INT) :: power
    integer(C_INT) :: N

    lbase = 2_C_INT
    power = 0_C_INT
    N = size(array, kind=C_INT)

    if (N < 2_C_INT) then
      u = array(1_C_INT)
      return
    end if

    if (present(base)) then
      if (is_prime(base)) lbase = base
    end if

    power = get_factor_power(N - 1_C_INT, lbase)

    u = apply_extrapolation_schemeC_FLOAT(array, lbase, power)

  end function extrapolation_driverC_FLOAT

  function apply_extrapolation_schemeC_FLOAT(array, base, power) result(u)

    real(C_FLOAT), intent(in) :: array(:)
    integer(C_INT), intent(in) :: base
    integer(C_INT), intent(in) :: power

    real(C_FLOAT) :: u

    real(C_FLOAT)    :: work(power + 1_C_INT)
    integer(C_INT) :: i, j

    do i = 1_C_INT, power + 1_C_INT
      work(power + 2_C_INT - i) = &
        trapezoidal_ruleC_FLOAT(array, base, i - 1_C_INT)
    end do

    do i = 2_C_INT, (power + 1_C_INT)
      do j = 1_C_INT, (power + 1_C_INT) - i + 1_C_INT
        work(j) = &
          ((real(base, C_FLOAT)**2_C_INT)**(i - 1_C_INT))*work(j + 1_C_INT) &
          - work(j)
        work(j) = &
          work(j)/(-1.0_C_FLOAT + &
                   (real(base, C_FLOAT)**2_C_INT)**(i - 1_C_INT))
      end do
    end do

    u = work(1)

  end function apply_extrapolation_schemeC_FLOAT

  function trapezoidal_ruleC_FLOAT(array, base, power) result(u)

    real(C_FLOAT), intent(in) :: array(:)
    integer(C_INT), intent(in) :: base
    integer(C_INT), intent(in) :: power

    real(C_FLOAT) :: u

    integer(C_INT) :: N, Np
    integer(C_INT) :: i
    integer(C_INT) :: idx

    N = size(array, kind=C_INT)
    Np = ((N - 1_C_INT)/base**power) + 1_C_INT

    u = 0.5_C_FLOAT*(array(1_C_INT) + array(N))

    !$OMP PARALLEL DO PRIVATE(i, idx) SHARED(Np, base, power, array) REDUCTION(+: u)
    do i = 2_C_INT, Np - 1_C_INT
      idx = (base**power)*(i - 1_C_INT) + 1_C_INT
      u = u + array(idx)
    end do
    !$OMP END PARALLEL DO

    u = u/real(Np - 1_C_INT, C_FLOAT)

  end function trapezoidal_ruleC_FLOAT

  function extrapolation_driverC_DOUBLE(array, base) result(u)

    real(C_DOUBLE), intent(in)           :: array(:)
    integer(C_INT), intent(in), optional :: base

    real(C_DOUBLE) :: u

    integer(C_INT) :: lbase
    integer(C_INT) :: power
    integer(C_INT) :: N

    lbase = 2_C_INT
    power = 0_C_INT
    N = size(array, kind=C_INT)

    if (N < 2_C_INT) then
      u = array(1_C_INT)
      return
    end if

    if (present(base)) then
      if (is_prime(base)) lbase = base
    end if

    power = get_factor_power(N - 1_C_INT, lbase)

    u = apply_extrapolation_schemeC_DOUBLE(array, lbase, power)

  end function extrapolation_driverC_DOUBLE

  function apply_extrapolation_schemeC_DOUBLE(array, base, power) result(u)

    real(C_DOUBLE), intent(in) :: array(:)
    integer(C_INT), intent(in) :: base
    integer(C_INT), intent(in) :: power

    real(C_DOUBLE) :: u

    real(C_DOUBLE)    :: work(power + 1_C_INT)
    integer(C_INT) :: i, j

    do i = 1_C_INT, power + 1_C_INT
      work(power + 2_C_INT - i) = &
        trapezoidal_ruleC_DOUBLE(array, base, i - 1_C_INT)
    end do

    do i = 2_C_INT, (power + 1_C_INT)
      do j = 1_C_INT, (power + 1_C_INT) - i + 1_C_INT
        work(j) = &
          ((real(base, C_DOUBLE)**2_C_INT)**(i - 1_C_INT))*work(j + 1_C_INT) &
          - work(j)
        work(j) = &
          work(j)/(-1.0_C_DOUBLE + &
                   (real(base, C_DOUBLE)**2_C_INT)**(i - 1_C_INT))
      end do
    end do

    u = work(1)

  end function apply_extrapolation_schemeC_DOUBLE

  function trapezoidal_ruleC_DOUBLE(array, base, power) result(u)

    real(C_DOUBLE), intent(in) :: array(:)
    integer(C_INT), intent(in) :: base
    integer(C_INT), intent(in) :: power

    real(C_DOUBLE) :: u

    integer(C_INT) :: N, Np
    integer(C_INT) :: i
    integer(C_INT) :: idx

    N = size(array, kind=C_INT)
    Np = ((N - 1_C_INT)/base**power) + 1_C_INT

    u = 0.5_C_DOUBLE*(array(1_C_INT) + array(N))

    !$OMP PARALLEL DO PRIVATE(i, idx) SHARED(Np, base, power, array) REDUCTION(+: u)
    do i = 2_C_INT, Np - 1_C_INT
      idx = (base**power)*(i - 1_C_INT) + 1_C_INT
      u = u + array(idx)
    end do
    !$OMP END PARALLEL DO

    u = u/real(Np - 1_C_INT, C_DOUBLE)

  end function trapezoidal_ruleC_DOUBLE

end module EINT_Core
