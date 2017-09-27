    /////////////////////////////////////////////////////////////////////
   // sol_vec3.c ///////////////////////////////////////////////////////
  // Description: Adds 3D vector/position functionality to Sol. ///////
 // Author: k1tt3hk4t (https://github.com/k1tt3hk4t/sol) /////////////
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
 // Vec3 Initialization ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec3_init ///
// Description
//   Initializes a vector in XYZ order.
// Arguments
//   x: float (sol_f)
//   y: float (sol_f)
//   z: float (sol_f)
// Returns
//   out: vector (Vec3)

sol_inline
Vec3 vec3_init(sol_f x, sol_f y, sol_f z) {
  Vec3 out;
  #ifdef SOL_AVX
        #if SOL_F_SIZE >= 64
              out.vec = _mm256_set_pd(x, y, z, 0);
        #else
              out.vec = _mm_set_ps(x, y, z, 0);
        #endif
  #else // NEON has no special set intrinsic:
        out.x = x;
        out.y = y;
        out.z = z;
  #endif
  return out;
}

/// vec3_initf ///
// Description
//   Initializes a vector's XYZ values using a single float.
// Arguments
//   f: float (sol_f)
// Returns
//   out: vector (Vec3)

sol_inline
Vec3 vec3_initf(sol_f f) {
  Vec3 out;
  #ifdef SOL_AVX
        #if SOL_F_SIZE >= 64
              out.vec = _mm256_set1_pd(f);
        #else
              out.vec = _mm_set1_ps(f);
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
  #endif
  return out;
}

/// vec3_zero ///
// Description
//   Initializes a vector's XYZ values as zero.
// Arguments
//   void
// Returns
//   out: vector (Vec3)

sol_inline
Vec3 vec3_zero(void) {
  return vec3_initf(0);
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec3 Core Operations //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec3_norm ///
// Description
//   Normalizes a vector such that the magnitude is 1.
// Arguments
//   v: vector (Vec3)
// Returns
//   out: vector (Vec3)

sol_inline
Vec3 vec3_norm(Vec3 v) {
  return vec3_divf(v, vec3_mag(v));
}

/// vec3_mag ///
// Description
//   Finds the magnitude of a vector.
// Arguments
//   v: vector (Vec3)
// Returns
//   out: vector (Vec3)

sol_inline
sol_f vec3_mag(Vec3 v) {
  return sqrt(vec3_dot(v, v));
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec3 Advanced Operations //////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec3_rot ///
// Description
//   Rotates a vector by a unit quaternion.
// Arguments
//   v: vector (Vec3)
//   q: quaternion (Vec4)
// Returns
//   out: vector (Vec3)

sol_inline
Vec3 vec3_rot(Vec3 v, Vec4 q) {
  Vec3 qv = vec3_init(q.x, q.y, q.z);
  Vec3 t = vec3_multf(vec3_cross(qv, v), 2);
  return vec3_add(v, vec3_add(vec3_multf(t, q.w), vec3_cross(qv, t)));
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec3 Advanced Math ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec3_cross ///
// Description
//   Gets the cross product of two vectors.
// Arguments
//   a: vector (Vec3)
//   b: vector (Vec3)
// Returns
//   out: vector (Vec3)

sol_inline
Vec3 vec3_cross(Vec3 a, Vec3 b) {
  return vec3_init((a.y * b.z) - (a.z * b.y),
                   (a.z * b.x) - (a.x * b.z),
                   (a.x * b.y) - (a.y * b.x));
}

/// vec3_dot ///
// Description
//   Gets the dot product of two vectors.
// Arguments
//   a: vector (Vec3)
//   b: vector (Vec3)
// Returns
//   out: vector (Vec3)

sol_inline
sol_f vec3_dot(Vec3 a, Vec3 b) {
  return (a.x * b.x)
       + (a.y * b.y)
       + (a.z * b.z);
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec3 Basic Math ///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec3_add ///
// Description
//   Adds the elements of two vectors.
// Arguments
//   a: vector (Vec3)
//   b: vector (Vec3)
// Returns
//   out: vector (Vec3) {a.xyz + b.xyz}

sol_inline
Vec3 vec3_add(Vec3 a, Vec3 b) {
  Vec3 out;
  #ifdef SOL_AVX
        #if SOL_F_SIZE >= 64
              out.vec = _mm256_add_pd(a.vec, b.vec);
        #else
              out.vec = _mm_add_ps(a.vec, b.vec);
        #endif
  #elif defined(SOL_NEON)
        #if SOL_F_SIZE >= 64
              out.vec = vaddq_f64(a.vec, b.vec);
        #else
              out.vec = vaddq_f32(a.vec, b.vec);
        #endif
  #elif defined(SOL_OMP)
        #pragma sol_omp
        for (char i = 0; i < 3; i++) {
          out.arr[i] = a.arr[i] + b.arr[i];
        }
  #else
        out.x = a.x + b.x;
        out.y = a.y + b.y;
        out.z = a.z + b.z;
  #endif
  return out;
}

/// vec3_addf ///
// Description
//   Adds a float to each element of a vector.
// Arguments
//   v: vector (Vec3)
//   f: float (sol_f)
// Returns
//   out: vector (Vec3) {v.xyz + f}

sol_inline
Vec3 vec3_addf(Vec3 v, sol_f f) {
  return vec3_add(v, vec3_initf(f));
}

/// vec3_sub ///
// Description
//   Subtracts the elements of one vector from another.
// Arguments
//   a: vector (Vec3)
//   b: vector (Vec3)
// Returns
//   out: vector (Vec3) {a.xyz - b.xyz}

sol_inline
Vec3 vec3_sub(Vec3 a, Vec3 b) {
  Vec3 out;
  #ifdef SOL_AVX
        #if SOL_F_SIZE >= 64
              out.vec = _mm256_sub_pd(a.vec, b.vec);
        #else
              out.vec = _mm_sub_ps(a.vec, b.vec);
        #endif
  #elif defined(SOL_NEON)
        #if SOL_F_SIZE >= 64
              out.vec = vsubq_f64(a.vec, b.vec);
        #else
              out.vec = vsubq_f32(a.vec, b.vec);
        #endif
  #elif defined(SOL_OMP)
        #pragma sol_omp
        for (char i = 0; i < 3; i++) {
          out.arr[i] = a.arr[i] - b.arr[i];
        }
  #else
        out.x = a.x - b.x;
        out.y = a.y - b.y;
        out.z = a.z - b.z;
  #endif
  return out;
}

/// vec3_subf ///
// Description
//   Subtracts a float from each element of a vector.
// Arguments
//   v: vector (Vec3)
//   f: float (sol_f)
// Returns
//   out: vector (Vec3) {v.xyz - f}

sol_inline
Vec3 vec3_subf(Vec3 v, sol_f f) {
  return vec3_sub(v, vec3_initf(f));
}

/// vec3_fsub ///
// Description
//   Subtracts each element of a vector from a float.
// Arguments
//   f: float (sol-f)
//   v: vector (Vec3)
// Returns
//   out: vector (Vec3) {f - v.xyz}

sol_inline
Vec3 vec3_fsub(sol_f f, Vec3 v) {
  return vec3_sub(vec3_initf(f), v);
}

/// vec3_mult ///
// Description
//   Multiplies the elements of two vectors.
// Arguments
//   a: vector (Vec3)
//   b: vector (Vec3)
// Returns
//   out: vector (Vec3) {a.xyz * b.xyz}

sol_inline
Vec3 vec3_mult(Vec3 a, Vec3 b) {
  Vec3 out;
  #ifdef SOL_AVX
        #if SOL_F_SIZE >= 64
              out.vec = _mm256_mul_pd(a.vec, b.vec);
        #else
              out.vec = _mm_mul_ps(a.vec, b.vec);
        #endif
  #elif defined(SOL_NEON)
        #if SOL_F_SIZE >= 64
              out.vec = vmulq_f64(a.vec, b.vec);
        #else
              out.vec = vmulq_f32(a.vec, b.vec);
        #endif
  #elif defined(SOL_OMP)
        #pragma sol_omp
        for (char i = 0; i < 3; i++) {
          out.arr[i] = a.arr[i] * b.arr[i];
        }
  #else
        out.x = a.x * b.x;
        out.y = a.y * b.y;
        out.z = a.z * b.z;
  #endif
  return out;
}

/// vec3_multf ///
// Description
//   Multiplies each element of a vector by a float.
// Arguments
//   v: vector (Vec3)
//   f: float (sol_f)
// Returns
//   out: vector (Vec3) {v.xyz * f}

sol_inline
Vec3 vec3_multf(Vec3 v, sol_f f) {
  return vec3_mult(v, vec3_initf(f));
}

/// vec3_div ///
// Description
//   Divides each element of one vector by another.
// Arguments
//   a: vector (Vec3)
//   b: vector (Vec3)
// Returns
//   out: vector (Vec3) {a.xyz / b.xyz}

sol_inline
Vec3 vec3_div(Vec3 a, Vec3 b) {
  Vec3 out;
  #ifdef SOL_OMP
        #pragma sol_omp
        for (char i = 0; i < 3; i++) {
          out.arr[i] = a.arr[i] / b.arr[i];
        }
  #else
        out.x = a.x / b.x;
        out.y = a.y / b.y;
        out.z = a.z / b.z;
  #endif
  return out;
}

/// vec3_divf ///
// Description
//   Divide each element of a vector by a float.
// Arguments
//   v: vector (Vec3)
//   f: float (sol_f)
// Returns
//   out: vector (Vec3) {v.xyz / f}

sol_inline
Vec3 vec3_divf(Vec3 v, sol_f f) {
  return vec3_div(v, vec3_initf(f));
}

/// vec3_fdiv ///
// Description
//   Divide a float by each element of a vector.
// Arguments
//   f: float (sol_f)
//   v: vector (Vec3)
// Returns
//   out: vector (Vec3) {f / v.xyz}

sol_inline
Vec3 vec3_fdiv(sol_f f, Vec3 v) {
  return vec3_div(vec3_initf(f), v);
}

/// vec3_avg ///
// Description
//   Average each element of two vectors.
// Arguments
//   a: vector (Vec3)
//   b: vector (Vec3)
// Returns
//   out: vector (Vec3) {(a.xyz + b.xyz) / 2}

sol_inline
Vec3 vec3_avg(Vec3 a, Vec3 b) {
  return vec3_divf(vec3_add(a, b), 2);
}

/// vec3_avgf ///
// Description
//   Average each element of a vector with a float.
// Arguments
//   v: vector (Vec3)
//   f: float (sol_f)
// Returns
//   out: vector (Vec3) {(v.xyz + f) / 2}

sol_inline
Vec3 vec3_avgf(Vec3 v, sol_f f) {
  return vec3_avg(v, vec3_initf(f));
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec3 Terminal IO //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec3_print ///
// Description
//   Shows a vector's elements in stdout with a newline appended.
// Arguments
//   v: vector (Vec3)
// Returns
//   void

sol_inline
void vec3_print(Vec3 v) {
  printf("(%Le, %Le, %Le)\n", (long double) v.x,
                              (long double) v.y,
                              (long double) v.z);
}
