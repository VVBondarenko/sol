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
Vec4 vec4_norm(Vec4 q) {
  const Float m = vec4_mag(q);
  return vec4_init(q.x / m,
                   q.y / m,
                   q.z / m,
                   q.w / m);
}

/// vec4_mag ///
// Description
//   Finds the magnitude of a quaternion.
// Arguments
//   q: quaternion (Vec4)
// Returns
//   out: scalar (Float)

sol_inline
Float vec4_mag(Vec4 q) {
  return sqrtf((q.x * q.x)
             + (q.y * q.y)
             + (q.z * q.z)
             + (q.w * q.w));
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
