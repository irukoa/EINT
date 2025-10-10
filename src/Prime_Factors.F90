module Prime_Factors

  use FC_Kinds
  use, intrinsic :: ISO_C_Binding

  implicit none

  private

  public :: is_prime
  public :: get_factor_power

contains

  function is_prime(number) result(u) BIND(C, NAME="is_prime")

    integer(C_INT), intent(in), value :: number

    logical(C_BOOL) :: u

    integer(C_INT) :: div_count
    integer(C_INT) :: i

    u = .false._C_BOOL
    div_count = 0_C_INT

    if (number < 1_C_INT) return

    do i = 1_C_INT, number
      if (modulo(number, i) == 0_C_INT) div_count = div_count + 1_C_INT
    end do

    if (div_count <= 2_C_INT) u = .true._C_BOOL

  end function is_prime

  function get_factor_power(number, prime_factor) result(u) &
    BIND(C, NAME="get_factor_power")

    integer(C_INT), intent(in), value :: number
    integer(C_INT), intent(in), value :: prime_factor

    integer(C_INT) :: u

    integer(C_INT) :: aux

    u = 0_C_INT
    aux = number

    do while (modulo(aux, prime_factor) == 0_C_INT)
      aux = aux/prime_factor
      u = u + 1_C_INT
    end do

  end function get_factor_power

end module Prime_Factors
