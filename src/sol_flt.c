  ///////////////
 // sol_flt.c //
///////////////

#include "../sol.h"

/// flt_clamp ///
// Description
//   Clamps a Float to a specific lower/upper bounds.
// Arguments
//   f: Number (Float)
//   lower: Lower Bounds (Float)
//   upper: Upper Bounds (Float)
// Returns
//   out: Clamped Number (Float)

sol_inline
Float flt_clamp(Float f, Float lower, Float upper) {
  return (f > upper) ? upper : (f < lower) ? lower : f;
}

/// flt_pow ///
// Description
//   A wrapper for powf/pow/powl which respects
//   the accuracy of Sol's Float type.

sol_inline
Float flt_pow(Float a, Float b) {
  #if SOL_F_SIZE > 64
        return powl(a, b);
  #elif SOL_F_SIZE > 32
        return pow(a, b);
  #else
        return powf(a, b);
  #endif
}

/// flt_sqrt ///
// Description
//   A wrapper for sqrtf/sqrt/sqrtl which respects
//   the accuracy of Sol's Float type.

sol_inline
Float flt_sqrt(Float f) {
  #if SOL_F_SIZE > 64
        return sqrtl(f);
  #elif SOL_F_SIZE > 32
        return sqrt(f);
  #else
        return sqrtf(f);
  #endif
}

/// flt_sin ///
// Description
//   A wrapper for sinf/sin/sinl which respects
//   the accuracy of Sol's Float type.

sol_inline
Float flt_sin(Float f) {
  #if SOL_F_SIZE > 64
        return sinl(f);
  #elif SOL_F_SIZE > 32
        return sin(f);
  #else
        return sinf(f);
  #endif
}

/// flt_cos ///
// Description
//   A wrapper for cosf/cos/cosl which respects
//   the accuracy of Sol's Float type.

sol_inline
Float flt_cos(Float f) {
  #if SOL_F_SIZE > 64
        return cosl(f);
  #elif SOL_F_SIZE > 32
        return cos(f);
  #else
        return cosf(f);
  #endif
}
