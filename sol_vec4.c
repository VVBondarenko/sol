    //////////////////////////////////////////////////////////////////////
   // sol_vec4.c ////////////////////////////////////////////////////////
  // Description: Adds 4D quaternion/axis-angle functionality to Sol. //
 // Author: k1tt3hk4t (https://github.com/k1tt3hk4t/sol) //////////////
//////////////////////////////////////////////////////////////////////

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
 // Vec4 Initialization ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec4_init ///
// Description
//   Initializes a quaternion in XYZW order.
// Arguments
//   x: float (sol_f)
//   y: float (sol_f)
//   z: float (sol_f)
//   w: float (sol_f)
// Returns
//   out: quaternion (Vec4)

sol_inline
Vec4 vec4_init(sol_f x, sol_f y, sol_f z, sol_f w) {
  Vec4 out;
  #ifdef SOL_AVX
        #if SOL_F_SIZE >= 64
              out.vec = _mm256_set_pd(x, y, z, w);
        #else
              out.vec = _mm_set_ps(x, y, z, w);
        #endif
  #else // NEON has no special set intrinsic:
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
//   f: float (sol_f)
// Returns
//   out: quaternion (Vec4)

sol_inline
Vec4 vec4_initf(sol_f f) {
  Vec4 out;
  #ifdef SOL_AVX
        #if SOL_F_SIZE >= 64
              out.vec = _mm256_set1_pd(f);
        #else
              out.vec = _mm_set_ps(f);
        #endif
  #elif defined(SOL_NEON)
        #if SOL_F_SIZE >= 64
              out.vec = vdupq_n_f64(f);
        #else
              out.vec = vdupq_n_f32(f);
        #endif
  #else
        out.x = f;
        out.y = f;
        out.z = f;
        out.w = f;
  #endif
  return out;
}

/// vec4_zero ///
// Description
//   Initializes a quaternion's XYZW values as zero.
// Arguments
//   void
// Returns
//   out: quaternion (Vec4)

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
  sol_f m = vec4_mag(q);
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
//   out: float (sol_f)

sol_inline
sol_f vec4_mag(Vec4 q) {
  return sqrt((q.x * q.x)
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
  printf("(%Le, %Le, %Le, %Le)\n", (long double) q.x,
                                   (long double) q.y,
                                   (long double) q.z,
                                   (long double) q.w);
}
