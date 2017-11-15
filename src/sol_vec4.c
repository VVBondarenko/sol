    //////////////////////////////////////////////////////////////////////
   // sol_vec4.c ////////////////////////////////////////////////////////
  // Description: Adds 4D quaternion/axis-angle functionality to Sol. //
 // Author: David Garland (https://github.com/davidgarland/sol) ///////
//////////////////////////////////////////////////////////////////////

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
 // Vec4 Initialization ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec4_init ///
// Description
//   Initializes a quaternion in XYZW order.
// Arguments
//   x: dimension (Float)
//   y: dimension (Float)
//   z: dimension (Float)
//   w: dimension (Float)
// Returns
//   quaternion (Vec4)

sol_inline
Vec4 vec4_init(Float x, Float y, Float z, Float w) {
  Vec4 out;
  #if defined(SOL_AVX_64)
        out.vec = _mm256_set_pd(x, y, z, w);
  #elif defined(SOL_AVX)
        out.vec = _mm_set_ps(x, y, z, w);
  #else
        out.x = x;
        out.y = y;
        out.z = z;
        out.w = w;
  #endif
  return out;
}

/// vec4_initf ///
// Description
//   Initializes a quaternion's XYZW values using a single float.
// Arguments
//   f: scalar (Float)
// Returns
//   quaternion (Vec4)

sol_inline
Vec4 vec4_initf(Float f) {
  Vec4 out;
  #if defined(SOL_AVX_64)
        out.vec = _mm256_set1_pd(f);
  #elif defined(SOL_AVX)
        out.vec = _mm_set1_ps(f);
  #elif defined(SOL_NEON_64)
        out.vec = vdupq_n_f64(f);
  #elif defined(SOL_NEON)
        out.vec = vdupq_n_f32(f);
  #else
        out = vec4_init(f, f, f, f);
  #endif
  return out;
}

/// vec4_zero ///
// Description
//   Initializes a quaternion's XYZW values as zero.
// Arguments
//   void
// Returns
//   quaternion (Vec4)

sol_inline
Vec4 vec4_zero(void) {
  return vec4_initf(0);
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec4 Core Operations //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec4_norm ///
// Description
//   Normalizes a quaternion such that the magnitude is 1.
// Arguments
//   q: quaternion (Vec4)
// Returns
//   out: quaternion (Vec4)

sol_inline
Vec4 vec4_norm(Vec4 v) {
  return vec4_divf(v, vec4_mag(v));
}

/// vec4_mag ///
// Description
//   Finds the magnitude of a quaternion.
// Arguments
//   q: quaternion (Vec4)
// Returns
//   out: scalar (Float)

sol_inline
Float vec4_mag(Vec4 v) {
  return flt_sqrt(vec4_sum(vec4_mul(v, v)));
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec4 Basic Functions //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec4_sum ///
// Description
//   Gets the sum of all the dimensions of a vector.
// Arguments
//   v: vector (Vec4)
// Returns
//   scalar (Float) {v.x + v.y + v.z + v.w} 

sol_inline
Float vec4_sum(Vec4 v) {
  return v.x + v.y + v.z + v.w;
}

/// vec4_add ///
// Description
//   Adds the elements of two vectors.
// Arguments
//   a: vector (Vec4)
//   b: vector (Vec4)
// Returns
//   vector (Vec4) {a.xyz + b.xyz} 

sol_inline
Vec4 vec4_add(Vec4 a, Vec4 b) {
  Vec4 out;
  #if defined(SOL_AVX_64)
        out.vec = _mm256_add_pd(a.vec, b.vec);
  #elif defined(SOL_AVX)
        out.vec = _mm_add_ps(a.vec, b.vec);
  #elif defined(SOL_NEON_64)
        out.vec = vaddq_f64(a.vec, b.vec);
  #elif defined(SOL_NEON)
        out.vec = vaddq_f32(a.vec, b.vec);
  #else
        out.x = a.x + b.x;
        out.y = a.y + b.y;
        out.z = a.z + b.z;
        out.w = a.w + b.w;
  #endif
  return out;
}

/// vec4_addf ///
// Description
//   Adds a scalar to each element of a vector.
// Arguments
//   v: vector (Vec4)
//   f: scalar (Float)
// Returns
//   vector (Vec4) {v.xyz + f}

sol_inline
Vec4 vec4_addf(Vec4 v, Float f) {
  return vec4_add(v, vec4_initf(f)); 
}

/// vec4_sub ///
// Description
//   Subtract the elements of one vector from another.
// Arguments
//   a: vector (Vec4)
//   b: vector (Vec4)
// Returns
//   vector (Vec4) {a.xyz - b.xyz}

sol_inline
Vec4 vec4_sub(Vec4 a, Vec4 b) {
  Vec4 out;
  #if defined(SOL_AVX_64)
        out.vec = _mm256_add_pd(a.vec, b.vec);
  #elif defined(SOL_AVX)
        out.vec = _mm_add_ps(a.vec, b.vec);
  #elif defined(SOL_NEON_64)
        out.vec = vsubq_f64(a.vec, b.vec);
  #elif defined(SOL_NEON)
        out.vec = vsubq_f32(a.vec, b.vec);
  #else
        out.x = a.x - b.x;
        out.y = a.y - b.y;
        out.z = a.z - b.z;
        out.w = a.w - b.w;
  #endif
  return out;
}

/// vec4_subf ///
// Description
//   Subtracts a scalar from each element of a vector.
// Arguments
//   v: vector (Vec4)
//   f: scalar (Float)
// Returns
//   vector (Vec4) {v.xyz - f}

sol_inline
Vec4 vec4_subf(Vec4 v, Float f) {
  return vec4_sub(v, vec4_initf(f));
}

/// vec4_fsub ///
// Description
//   Subtracts each of a vector'e elements from a scalar.
// Arguments
//   f: scalar (Float)
//   v: vector (Vec4)
// Returns
//   vector (Vec4) {f - v.xyz}

sol_inline
Vec4 vec4_fsub(Float f, Vec4 v) {
  return vec4_sub(vec4_initf(f), v);
}

/// vec4_mul ///
// Description
//   Multiplies the elements of one vector by another.
// Arguments
//   a: vector (Vec4)
//   b: vector (Vec4)
// Returns
//   vector (Vec4) {a.xyz * b.xyz}

sol_inline
Vec4 vec4_mul(Vec4 a, Vec4 b) {
  Vec4 out;
  #if defined(SOL_AVX_64)
        out.vec = _mm256_mul_pd(a.vec, b.vec);
  #elif defined(SOL_AVX)
        out.vec = _mm_mul_ps(a.vec, b.vec);
  #elif defined(SOL_NEON_64)
        out.vec = vmulq_f64(a.vec, b.vec);
  #elif defined(SOL_NEON)
        out.vec = vmulq_f32(a.vec, b.vec);
  #else
        out.x = a.x * b.x;
        out.y = a.y * b.y;
        out.z = a.z * b.z;
        out.w = a.w * b.w;
  #endif
  return out;
}

/// vec4_mulf ///
// Description
//   Multiplies the elements of a vector by a scalar.
// Arguments
//   v: vector (Vec4)
//   f: scalar (Float)
// Returns
//   vector (Vec4) {v.xyz * f}

sol_inline
Vec4 vec4_mulf(Vec4 v, Float f) {
  return vec4_mul(v, vec4_initf(f));
}

/// vec4_div ///
// Description
//   Divides the elements of one vector by another.
// Arguments
//   a: vector (Vec4)
//   b: vector (Vec4)
// Returns
//   vector (Vec4) {a.xyz / b.xyz}

sol_inline
Vec4 vec4_div(Vec4 a, Vec4 b) {
  Vec4 out;
  out.x = a.x / b.x;
  out.y = a.y / b.y;
  out.z = a.z / b.z;
  out.w = a.w / b.w;
  return out;
}

/// vec4_divf ///
// Description
//   Divides the elements of a vector by a scalar.
// Arguments
//   v: vector (Vec4)
//   f: scalar (Float)
// Returns
//   vector (Vec4) {v.xyz / f}

sol_inline
Vec4 vec4_divf(Vec4 v, Float f) {
  return vec4_div(v, vec4_initf(f));
}

/// vec4_fdiv ///
// Description
//   Divides a scalar by the elements of a vector.
// Arguments
//   f: scalar (Float)
//   v: vector (Vec4)
// Returns
//   vector (Vec4) {f / v.xyz}

sol_inline
Vec4 vec4_fdiv(Float f, Vec4 v) {
  return vec4_div(vec4_initf(f), v);
}

/// vec4_avg ///
// Description
//   Averages the elements of one vector with another.
// Arguments
//   a: vector (Vec4)
//   b: vector (Vec4)
// Returns
//   vector (Vec4) {(a.xyz + b.xyz) / 2}

sol_inline
Vec4 vec4_avg(Vec4 a, Vec4 b) {
  return vec4_divf(vec4_mul(a, b), 2);
}

/// vec4_avgf ///
// Description
//   Averages the elements of a vector with a scalar.
// Arguments
//   v: vector (Vec4)
//   f: scalar (Float)
// Returns
//   vector (Vec4) {(v.xyz + f) / 2}

sol_inline
Vec4 vec4_avgf(Vec4 v, Float f) {
  return vec4_avg(v, vec4_initf(f));
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec4 Terminal IO //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec4_print ///
// Description
//   Show a quaternion's elements in stdout with a newline appended.
// Arguments
//   q: quaternion (Vec4)
// Returns
//   void

sol_inline
void vec4_print(Vec4 q) {
  #if SOL_F_SIZE > 64
        printf("(%Le, %Le, %Le, %Le)\n", q.x, q.y, q.z, q.w);
  #elif SOL_F_SIZE > 32
        printf("(%e, %e, %e, %e)\n", q.x, q.y, q.z, q.w);
  #else
        printf("(%f, %f, %f, %f)\n", q.x, q.y, q.z, q.w);
  #endif
}
