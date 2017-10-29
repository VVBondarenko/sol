    /////////////////////////////////////////////////////////////////////
   // sol_vec2.c ///////////////////////////////////////////////////////
  // Description: Adds 2D vector/position functionality to Sol. ///////
 // Author: k1tt3hk4t (https://github.com/k1tt3hk4t/sol) /////////////
/////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
 // Local Headers /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#include "../sol.h"

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
//   x: dimension (Float)
//   y: dimension (Float)
// Returns
//   vector (Vec2)

sol_inline
Vec2 vec2_init(Float x, Float y) {
  Vec2 out;
  #if defined(SOL_AVX_64)
        out.vec = _mm_set_pd(x, y);
  #elif defined(SOL_AVX)
        out.vec = _mm_set_ps(x, y, 0, 0);
  #else
        out.x = x;
        out.y = y;
  #endif
  return out;
}

/// vec2_initf ///
// Description
//   Initializes a vector's XY values using a single float.
// Arguments
//   f: scalar (Float)
// Returns
//   vector (Vec2)

sol_inline
Vec2 vec2_initf(Float f) {
  Vec2 out;
  #if defined(SOL_AVX_64)
        out.vec = _mm_set1_pd(f);
  #elif defined(SOL_AVX)
        out.vec = _mm_set1_ps(f);
  #elif defined(SOL_NEON_64)
        out.vec = vdup_n_f64(f);
  #elif defined(SOL_NEON)
        out.vec = vdup_n_f32(f);
  #else
        out = vec2_init(f, f);
  #endif
  return out;
}

/// vec2_zero ///
// Description
//   Initizlies a vector's XYZ values as zero.
// Arguments
//   void
// Returns
//   vector (Vec2)

sol_inline
Vec2 vec2_zero(void) {
  return vec2_initf(0);
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
//   vector (Vec2)

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
//   scalar (Float)

sol_inline
Float vec2_mag(Vec2 v) {
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
//   rad: radians (Float)
// Returns
//   out: vector (Vec2)

sol_inline
Vec2 vec2_rot(Vec2 v, Float rad) {
  Float cs = cos(rad);
  Float sn = sin(rad);
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
//   scalar (Float)

sol_inline
Float vec2_cross(Vec2 a, Vec2 b) {
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
//   scalar (Float)

sol_inline
Float vec2_dot(Vec2 a, Vec2 b) {
  const Vec2 out = vec2_mul(a, b);
  return out.x + out.y;
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec2 Basic Math ///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec2_sum ///
// Description
//   Gets the sum of all of the dimensions of a vector.
// Arguments
//   v: vector (Vec2)
// Returns
//   scalar (Float) {sum a.xy}

sol_inline
Float vec2_sum(Vec2 v) {
  return v.x + v.y;
}

/// vec2_add ///
// Description
//   Adds the elements of two vectors.
// Arguments
//   a: vector (Vec2)
//   b: vector (Vec2)
// Returns
//   vector (Vec2) {a.xy + b.xy}

sol_inline
Vec2 vec2_add(Vec2 a, Vec2 b) {
  Vec2 out;
  #if defined(SOL_AVX_64)
        out.vec = _mm_add_pd(a.vec, b.vec);
  #elif defined(SOL_AVX)
        out.vec = _mm_add_ps(a.vec, b.vec);
  #elif defined(SOL_NEON_64)
        out.vec = vadd_f64(a.vec, b.vec);
  #elif defined(SOL_NEON)
        out.vec = vadd_f32(a.vec, b.vec);
  #else
        out.x = a.x + b.x;
        out.y = a.y + b.y;
  #endif
  return out;
}

/// vec2_addf ///
// Description
//   Adds a float to each element of a vector.
// Arguments
//   v: vector (Vec2)
//   f: scalar (Float)
// Returns
//   vector (Vec2) {v.xyz + f}

sol_inline
Vec2 vec2_addf(Vec2 v, Float f) {
  return vec2_add(v, vec2_initf(f));
}

/// vec2_sub ///
// Description
//   Subtract the elements of one vector from another.
// Arguments
//   a: vector (Vec2)
//   b: vector (Vec2)
// Returns
//   vector (Vec2) {a.xyz - b.xyz}

sol_inline
Vec2 vec2_sub(Vec2 a, Vec2 b) {
  Vec2 out;
  #if defined(SOL_AVX_64)
        out.vec = _mm_sub_pd(a.vec, b.vec);
  #elif defined(SOL_AVX)
        out.vec = _mm_sub_ps(a.vec, b.vec);
  #elif defined(SOL_NEON_64)
        out.vec = vsub_f64(a.vec, b.vec);
  #elif defined(SOL_NEON)
        out.vec = vsub_f32(a.vec, b.vec);
  #else
        out.x = a.x - b.x;
        out.y = a.y - b.y;      
  #endif
  return out;
}

/// vec2_subf ///
// Description
//   Subtracts a scalar from each element of a vector.
// Arguments
//   v: vector (Vec2)
//   f: scalar (Float)
// Returns
//   vector (Vec2) {v.xyz - f}

sol_inline
Vec2 vec2_subf(Vec2 v, Float f) {
  return vec2_sub(v, vec2_initf(f));
}

/// vec2_fsub ///
// Description
//   Subtracts each element of a vector from a float.
// Arguments
//   f: float (sol_f)
//   v: vector (Vec2)
// Returns
//   vector (Vec2) {f - v.xyz}

sol_inline
Vec2 vec2_fsub(Float f, Vec2 v) {
  return vec2_sub(vec2_initf(f), v);
}

/// vec2_mul ///
// Description
//   Multiplies the elements of two vectors.
// Arguments
//   a: vector (Vec2)
//   b: vector (Vec2)
// Returns
//   vector (Vec2) {a.xyz * b.xyz}

sol_inline
Vec2 vec2_mul(Vec2 a, Vec2 b) {
  Vec2 out;
  #if defined(SOL_AVX_64)
        out.vec = _mm_mul_pd(a.vec, b.vec);
  #elif defined(SOL_AVX)
        out.vec = _mm_mul_ps(a.vec, b.vec);
  #elif defined(SOL_NEON_64)
        out.vec = vmul_f64(a.vec, b.vec);
  #elif defined(SOL_NEON)
        out.vec = vmul_f32(a.vec, b.vec);
  #else
        out.x = a.x * b.x;
        out.y = a.y * b.y;
  #endif
  return out;
}

/// vec2_multf ///
// Description
//   Multiplies each element of a vector by a float.
// Arguments
//   v: vector (Vec2)
//   f: scalar (Float)
// Returns
//   vector (Vec2) {v.xyz * f}

sol_inline
Vec2 vec2_mulf(Vec2 v, Float f) {
  return vec2_mul(v, vec2_initf(f));
}

/// vec2_div ///
// Description
//   Divide the elements of one vector by another.
// Arguments
//   a: vector (Vec2)
//   b: vector (Vec2)
// Returns
//   vector (Vec2) {a.xyz / b.xyz}

sol_inline
Vec2 vec2_div(Vec2 a, Vec2 b) {
  Vec2 out;
  out.x = a.x / b.x;
  out.y = a.y / b.y;
  return out;
}

/// vec2_divf ///
// Description
//   Divide the elements of a vector by a float.
// Arguments
//   v: vector (Vec2)
//   f: scalar (Float)
// Returns
//   vector (Vec2) {v.xyz / f}

sol_inline
Vec2 vec2_divf(Vec2 v, Float f) {
  return vec2_div(v, vec2_initf(f));
}

/// vec2_fdiv ///
// Description
//   Divide a float by each element of a vector.
// Arguments
//   f: scalar (Float)
//   v: vector (Vec2)
// Returns
//   vector (Vec2) {f / v.xyz}

sol_inline
Vec2 vec2_fdiv(Float f, Vec2 v) {
  return vec2_div(vec2_initf(f), v);
}

/// vec2_avg ///
// Description
//   Average each element of two vectors.
// Arguments
//   a: vector (Vec2)
//   b: vector (Vec2)
// Returns
//   vector (Vec2) {(a.xyz + b.xyz) / 2}

sol_inline
Vec2 vec2_avg(Vec2 a, Vec2 b) {
  return vec2_divf(vec2_add(a, b), 2);
}

/// vec2_avgf ///
// Description
//   Average each element of a vector with a float.
// Arguments
//   v: vector (Vec2)
//   f: scalar (Float)
// Returns
//   vector (Vec2) {(v.xyz + f) / 2}

sol_inline
Vec2 vec2_avgf(Vec2 v, Float f) {
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
  #if SOL_F_SIZE > 64
        printf("(%Le, %Le)\n", v.x, v.y);
  #elif SOL_F_SIZE > 32
        printf("(%e, %e)\n", v.x, v.y);
  #else
        printf("(%f, %f)\n", v.x, v.y);
  #endif
}
