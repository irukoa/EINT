program placeholder

  use, intrinsic :: ISO_C_BINDING, only: size_t => C_SIZE_T, &
                                                                int4 => C_INT, &
                                                                  dp => C_DOUBLE

#include <EINT_F.h>

  print *, extrapolation_double([0.0_dp, 1.0_dp], 2_size_t, 2)

end program placeholder
