    /////////////////////////////////////////////////////////////////////
   // sol_vec2.h ///////////////////////////////////////////////////////
  // Description: Adds 2D vector/position functionality to Sol. ///////
 // Author: Team Epoch (https://github.com/TeamEpoch/sol) ////////////
/////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
 // Local Headers /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#include "sol.h"

  //////////////////////////////////////////////////////////////////////////////
 // Standard Headers //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>

  //////////////////////////////////////////////////////////////////////////////
 // Vec2 Initialization ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec2_init ///
// Description
//   Initializes a vector in XY order.
// Arguments
//   x: float (sol_f)
//   y: float (sol_f)
// Returns
//   out: vector (Vec2)

sol_inline
Vec2 vec2_init(sol_f x, sol_f y) {
  Vec2 out = {x, y};
  return out;
}

/// vec2_initf ///
// Description
//   Initializes a vector's XY values using a single float.
// Arguments
//   x: float (sol_f)
//   y: float (sol_f)
// Returns
//   out: vector (Vec2)

sol_inline
Vec2 vec2_initf(sol_f f) {
  return vec2_init(f, f);
}

/// vec2_zero ///
// Description
//   Initizlies a vector's XYZ values as zero.
// Arguments
//   void
// Returns
//   out: vector (Vec2)

sol_inline
Vec2 vec2_zero(void) {
  return vec2_initf((sol_f) 0);
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec2 Core Operations //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec2_norm ///
// Description
//   Normalizes a vector such that the magnitude is 1.
// Arguments
//   v: vector (Vec2)
// Returns
//   out: vector (Vec2)

sol_inline
Vec2 vec2_norm(Vec2 v) {
  return vec2_divf(v, vec2_mag(v));
}

/// vec2_mag ///
// Description
//   Finds the magnitude of a vector.
// Arguments
//   v: vector (Vec2)
// Returns
//   out: float (sol_f)

sol_inline
sol_f vec2_mag(Vec2 v) {
  return sqrt(vec2_dot(v, v));
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec2 Advanced Operations //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/// vec2_rot ///
// Description
//   Rotate a 2D vector counterclockwise in radians.
// Arguments
//   v: vector (Vec2)
//   rad: float (sol_f)
// Returns
//   out: vector (Vec2)

sol_inline
Vec2 vec2_rot(Vec2 v, sol_f rad) {
  sol_f cs = cos(rad);
  sol_f sn = sin(rad);
  return vec2_init((v.x * cs) - (v.y * sn),
                   (v.x * sn) + (v.y * cs));
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec2 Advanced Math ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec2_cross ///
// Description
//   Gets the cross product of two vectors.
// Arguments
//   a: vector (Vec2)
//   b: vector (Vec2)
// Returns
//   out: float (sol_f)

sol_inline
sol_f vec2_cross(Vec2 a, Vec2 b) {
  return (a.x * b.y)
       - (b.x * a.y);
}

/// vec2_dot ///
// Description
//   Gets the dot product of two vectors.
// Arguments
//   a: vector (Vec2)
//   b: vector (Vec2)
// Returns
//   out: vector (Vec2)

sol_inline
sol_f vec2_dot(Vec2 a, Vec2 b) {
  return (a.x * b.x)
       + (a.y * b.y);
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec2 Basic Math ///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec2_add ///
// Description
//   Adds the elements of two vectors.
// Arguments
//   a: vector (Vec2)
//   b: vector (Vec2)
// Returns
//   out: vector (Vec2) {a.xy + b.xy}

sol_inline
Vec2 vec2_add(Vec2 a, Vec2 b) {
  return vec2_init(a.x + b.x,
                   a.y + b.y);
}

/// vec2_addf ///
// Description
//   Adds a float to each element of a vector.
// Arguments
//   v: vector (Vec2)
//   f: float (sol_f)
// Returns
//   out: vector (Vec2) {v.xyz + f}

sol_inline
Vec2 vec2_addf(Vec2 v, sol_f f) {
  return vec2_add(v, vec2_initf(f));
}

/// vec2_sub ///
// Description
//   Subtract the elements of one vector from another.
// Arguments
//   a: vector (Vec2)
//   b: vector (Vec2)
// Returns
//   out: vector (Vec2) {a.xyz - b.xyz}

sol_inline
Vec2 vec2_sub(Vec2 a, Vec2 b) {
  return vec2_init(a.x - b.x,
                   a.y - b.y);
}

/// vec2_subf ///
// Description
//   Subtracts a float from each element of a vector.
// Arguments
//   v: vector (Vec2)
//   f: float (sol_f)
// Returns
//   out: vector (Vec2) {v.xyz - f}

sol_inline
Vec2 vec2_subf(Vec2 v, sol_f f) {
  return vec2_sub(v, vec2_initf(f));
}

/// vec2_fsub ///
// Description
//   Subtracts each element of a vector from a float.
// Arguments
//   f: float (sol_f)
//   v: vector (Vec2)
// Returns
//   out: vector (Vec2) {f - v.xyz}

sol_inline
Vec2 vec2_fsub(sol_f f, Vec2 v) {
  return vec2_sub(vec2_initf(f), v);
}

/// vec2_mult ///
// Description
//   Multiplies the elements of two vectors.
// Arguments
//   a: vector (Vec2)
//   b: vector (Vec2)
// Returns
//   out: vector (Vec2) {a.xyz * b.xyz}

sol_inline
Vec2 vec2_mult(Vec2 a, Vec2 b) {
  return vec2_init(a.x * b.x,
                   a.y * b.y);
}

/// vec2_multf ///
// Description
//   Multiplies each element of a vector by a float.
// Arguments
//   v: vector (Vec2)
//   f: float (sol_f)
// Returns
//   out: vector (Vec2) {v.xyz * f}

sol_inline
Vec2 vec2_multf(Vec2 v, sol_f f) {
  return vec2_mult(v, vec2_initf(f));
}

/// vec2_div ///
// Description
//   Divide the elements of one vector by another.
// Arguments
//   a: vector (Vec2)
//   b: vector (Vec2)
// Returns
//   out: vector (Vec2) {a.xyz / b.xyz}

sol_inline
Vec2 vec2_div(Vec2 a, Vec2 b) {
  return vec2_init(a.x / b.x,
                   a.y / b.y);
}

/// vec2_divf ///
// Description
//   Divide the elements of a vector by a float.
// Arguments
//   v: vector (Vec2)
//   f: float (sol_f)
// Returns
//   out: vector (Vec2) {v.xyz / f}

sol_inline
Vec2 vec2_divf(Vec2 v, sol_f f) {
  return vec2_div(v, vec2_initf(f));
}

/// vec2_fdiv ///
// Description
//   Divide a float by each element of a vector.
// Arguments
//   f: float (sol_f)
//   v: vector (Vec2)
// Returns
//   out: vector (Vec2) {f / v.xyz}

sol_inline
Vec2 vec2_fdiv(sol_f f, Vec2 v) {
  return vec2_div(vec2_initf(f), v);
}

/// vec2_avg ///
// Description
//   Average each element of two vectors.
// Arguments
//   a: vector (Vec2)
//   b: vector (Vec2)
// Returns
//   out: vector (Vec2) {(a.xyz + b.xyz) / 2}

sol_inline
Vec2 vec2_avg(Vec2 a, Vec2 b) {
  return vec2_divf(vec2_add(a, b), 2);
}

/// vec2_avgf ///
// Description
//   Average each element of a vector with a float.
// Arguments
//   v: vector (Vec2)
//   f: float (sol_f)
// Returns
//   out: vector (Vec2) {(v.xyz + f) / 2}

sol_inline
Vec2 vec2_avgf(Vec2 v, sol_f f) {
  return vec2_avg(v, vec2_initf(f));
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec2 Terminal IO //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec2_print ///
// Description
//   Show a vector's elements in stdout.
// Arguments
//   v: vector (Vec2)
// Returns
//   void

sol_inline
void vec2_print(Vec2 v) {
  printf("(%Le, %Le)\n", (long double) v.x,
                         (long double) v.y);
}
