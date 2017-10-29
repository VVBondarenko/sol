  //////////////////
 // sol_float.c //
/////////////////

#include "../sol.h"

/// float_clamp ///
// Description
//   Clamps a Float to a specific lower/upper bounds.
// Arguments
//   f: Number (Float)
//   lower: Lower Bounds (Float)
//   upper: Upper Bounds (Float)
// Returns
//   out: Clamped Number (Float)

sol_inline
Float float_clamp(Float f, Float lower, Float upper) {
  return (f > upper) ? upper : (f < lower) ? lower : f;
}
