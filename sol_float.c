  //////////////////
 // sol_float.c //
/////////////////

#include "sol.h"

sol_inline
sol_f sol_f_clamp(sol_f f, sol_f min, sol_f max) {
  return (f > max) ? max : (f < min) ? min : f;
}
