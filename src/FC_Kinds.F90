module FC_Kinds

  use, intrinsic :: ISO_Fortran_ENV, only: &
    INT32, INT64

  use, intrinsic :: ISO_C_Binding, only: &
    C_BOOL, &
    C_INT, C_SIZE_T, &
    C_FLOAT, C_DOUBLE

  implicit none

  private

  !Fortran kinds.

  integer, parameter, public :: F_BOOL = kind(.true.)

  public :: INT32
  public :: INT64

  integer, parameter, public :: sp = kind(1.0e0)
  integer, parameter, public :: dp = kind(1.0d0)

  !C kinds.

  public :: C_BOOL

  public :: C_INT
  public :: C_SIZE_T

  public :: C_FLOAT
  public :: C_DOUBLE

end module FC_Kinds
