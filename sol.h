    ///////////////////////////////////////////////////////////
   // sol.h //////////////////////////////////////////////////
  // Description: A vector library written only in C. ///////
 // Author: k1tt3hk4t (https://github.com/k1tt3hk4t/sol) ///
///////////////////////////////////////////////////////////

#ifndef SOL_H
#define SOL_H

#ifdef __cplusplus
      extern "C" {
#endif

  //////////////////////////////////////////////////////////////////////////////
 // Standard Headers //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

  //////////////////////////////////////////////////////////////////////////////
 // Default Config ////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#define SOL_F_SIZE_DEFAULT 64 // Set the size of the sol_f float value.
#define SOL_INLINE_DEFAULT true // Enables function inlining.
#define SOL_FAM_DEFAULT true // Enables C99 "Flexible Array Members" (FAM).
#define SOL_SIMD_DEFAULT true // Enables automatic selection of OMP/AVX/NEON.
#define SOL_OMP_DEFAULT false // Enables explicit OpenMP SIMD.
#define SOL_AVX_DEFAULT false // Enables explicit AVX SIMD.
#define SOL_NEON_DEFAULT false // Enables explicit NEON SIMD.

  //////////////////////////////////////////////////////////////////////////////
 // Config Processing /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

// SOL_F_SIZE

#if !defined(SOL_F_SIZE)
      #if SOL_F_SIZE_DEFAULT > 32
            #define SOL_F_SIZE 64
      #else
            #define SOL_F_SIZE 32
      #endif
#endif

// SOL_INLINE

#if !defined(SOL_INLINE) && !defined(SOL_NO_INLINE)
      #if SOL_INLINE_DEFAULT == true
            #define SOL_INLINE
      #endif
#else
      #ifdef SOL_NO_INLINE
            #ifdef SOL_INLINE
                  #undef SOL_INLINE
            #endif
      #endif
#endif

// SOL_FAM

#if !defined(SOL_FAM) && !defined(SOL_NO_FAM)
      #if SOL_FAM_DEFAULT == true
            #define SOL_FAM
      #endif
#else
      #ifdef SOL_NO_FAM
            #ifdef SOL_FAM
                  #undef SOL_FAM
            #endif
      #endif
#endif

// SOL_SIMD

#if !defined(SOL_SIMD) && !defined(SOL_NO_SIMD)
      #if SOL_SIMD_DEFAULT == true
            #define SOL_SIMD
      #endif
#else
      #ifdef SOL_NO_SIMD
            #undef SOL_SIMD
      #endif
#endif

// SOL_AVX

#if !defined(SOL_AVX) && !defined(SOL_NO_AVX)
      #if SOL_AVX_DEFAULT == true
            #define SOL_AVX
      #endif
#else
      #ifdef SOL_NO_AVX
            #undef SOL_AVX
      #endif
#endif

// SOL_NEON

#if !defined(SOL_NEON) && !defined(SOL_NO_NEON)
      #if SOL_NEON_DEFAULT == true
            #define SOL_NEON
      #endif
#else
      #ifdef SOL_NO_NEON
            #undef SOL_NEON
      #endif
#endif

// SOL_OMP

#if !defined(SOL_OMP) && !defined(SOL_NO_OMP)
      #if SOL_OMP_DEFAULT == true
            #define SOL_OMP
      #endif
#else

      #ifdef SOL_NO_OMP
            #undef SOL_OMP
      #endif
#endif

  //////////////////////////////////////////////////////////////////////////////
 // Environment Checks ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#if !defined(__GNUC__) && !defined(__clang__)
      #pragma message ("[sol] Unrecognized compiler. Some features may not work.")
#endif

#if !defined(SOL_AVX) && !defined(SOL_NEON) && !defined(SOL_OMP)
      #ifdef SOL_SIMD
            #ifdef __AVX2__
                  #define SOL_AVX
            #elif defined(__AVX__)
                  #define SOL_AVX
                  #pragma message ("[sol] No AVX2 support found; Forcing 32-bit.")
                  #if SOL_F_SIZE >= 64
                        #undef SOL_F_SIZE
                        #define SOL_F_SIZE 32
                  #endif
            #elif defined(__ARM_NEON__)
                  #define SOL_NEON
            #else
                  #define SOL_OMP
            #endif
      #endif
#endif

  //////////////////////////////////////////////////////////////////////////////
 // Nonstandard Headers ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#ifdef SOL_AVX
      #include <x86intrin.h>
#elif defined(SOL_NEON)
      #include <arm_neon.h>
#endif

  //////////////////////////////////////////////////////////////////////////////
 // Core Macros ///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#ifdef SOL_INLINE
      #define sol_inline inline
#else
      #define sol_inline
#endif

#ifdef SOL_OMP
      #define sol_omp omp for simd
#else
      #define sol_omp
#endif

  //////////////////////////////////////////////////////////////////////////////
 // Core Type Definitions /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#if SOL_F_SIZE >= 64
      typedef double sol_f;
#else
      typedef float sol_f;
#endif

  //////////////////////////////////////////////////////////////////////////////
 // Math Macros ///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////



  //////////////////////////////////////////////////////////////////////////////
 // Struct Type Definitions ///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// Vec2 ///
// Description
//   A type comprised of two floats to represent a 2D vector or position.
// Fields
//   x: dimension (sol_f)
//   y: dimension (sol_f)
// Declarations
//   Vec2
//   struct type_vec2

typedef struct type_vec2 {
  union {
    struct {
      sol_f x, y;
    };
    sol_f arr[2];
    #ifdef SOL_AVX
          #if SOL_F_SIZE >= 64
                __m128d vec;
          #else
                __m128 vec;
          #endif
    #elif defined(SOL_NEON)
          #if SOL_F_SIZE >= 64
                float64x2_t vec;
          #else
                float32x2_t vec;
          #endif
    #endif
  };
} Vec2;

/// Vec3 ///
// Description
//   A type comprised of three floats to represent a 3D vector or position.
// Fields
//   x: dimension (sol_f)
//   y: dimension (sol_f)
//   z: dimension (sol_F)
// Declarations
//   Vec3
//   struct type_vec3

typedef struct type_vec3 {
  union { 
    struct {
      sol_f x, y, z;
    };
    sol_f arr[3];
    #ifdef SOL_AVX
          #if SOL_F_SIZE >= 64
                __m256d vec;
          #else
                __m128 vec;
          #endif
    #elif defined(SOL_NEON)
          #if SOL_F_SIZE >= 64
                float64x4_t vec;
          #else
                float32x4_t vec;
          #endif
    #endif
  };
} Vec3;

/// Vec4 ///
// Description
//   A type comprised of four floats to represent a quaternion or axis/angle
//   rotation.
// Fields
//   x: dimension (sol_f)
//   y: dimension (sol_f)
//   z: dimension (sol_f)
//   w: dimension (sol_f)
// Declarations
//   Vec4
//   struct type_vec4

typedef struct type_vec4 {
  union {
    struct {
      sol_f x, y, z, w;
    };
    sol_f arr[4];
    #ifdef SOL_AVX
          #if SOL_F_SIZE >= 64
                __m256d vec;
          #else
                __m128 vec;
          #endif
    #elif defined(SOL_NEON)
          #if SOL_F_SIZE >= 64
                float64x4_t vec;
          #else
                float32x4_t vec;
          #endif
    #endif
  };
} Vec4;

/// Seg2 ///
// Description
//   A type comprised of two 2D positions that represent a line segment.
// Fields
//   orig: position (Vec2)
//   dest: position (Vec2)
// Declarations
//   Seg2
//   struct type_seg2

typedef struct type_seg2 {
  Vec2 orig, dest;
} Seg2;

/// Seg3 ///
// Description
//   A type comprised of two 3D positions that represent a line segment.
// Fields
//   orig: position (Vec3)
//   dest: position (Vec3)
// Declarations
//   Seg3
//   struct type_seg3

typedef struct type_seg3 {
  Vec3 orig, dest;
} Seg3;

/// Box2 ///
// Description
//   A type comprised of two 2D positions that represent a bounding box.
// Fields
//   min: position (Vec2)
//   max: position (Vec2)
// Declarations
//   Box2
//   struct type_box2

typedef struct type_box2 {
  Vec2 min, max;
} Box2;

/// Box3 ///
// Description
//   A type comprised of two 3D positions that represent a bounding box.
// Fields
//   min: position (Vec3)
//   max: position (Vec3)
// Declarations
//   Box3
//   struct type_box3

typedef struct type_box3 {
  Vec3 min, max;
} Box3;

/// Sph2 ///
// Description
//   A type comprised of a 2D position and a radius that represent a bounding
//   sphere. Spheres have many advantages over boxes as bounding volumes,
//   as they don't change when rotated and are easy to check for intersection.
// Fields
//   pos: position (Vec2)
//   radius: radius (sol_f)
// Declarations
//   Sph2
//   struct type_sph2

typedef struct type_sph2 {
  Vec2 pos;
  sol_f radius;
} Sph2;

/// Sph3 ///
// Description
//   A type comprised of a 3D position and a radius that represent a bounding
//   sphere. Spheres have many advantages over boxes as bounding volumes,
//   as they don't change when rotated and are easy to check for intersection.
// Fields
//   pos: position (Vec3)
//   radius: radius (sol_f)
// Declarations
//   Sph3
//   struct type_sph3

typedef struct type_sph3 {
  Vec3 pos;
  sol_f radius;
} Sph3;

/// Lnk2 ///
// Description
//   A type comprised of a 2D position and an address to the next position to
//   represent a "link" for a model.
// Fields
//   pos: position (Vec2)
//   next: address (size_t)
// Declarations
//   Lnk2
//   struct type_lnk2

typedef struct type_lnk2 {
  Vec2 pos;
  size_t next;
} Lnk2;

/// Lnk3 ///
// Description
//   A type comprised of a 3D position and an address to the next position to
//   represent a "link" for a model.
// Fields
//   pos: position (Vec3)
//   next: address (size_t)
// Declarations
//   Lnk3
//   struct type_lnk3

typedef struct type_lnk3 {
  Vec3 pos;
  size_t next;
} Lnk3;

/// Mod2 ///
// Description
//   A type comprised of a bounding sphere, an array of links, and an integer
//   representing the size of the link array.
// Fields
//   sph: bounding sphere (Sph2)
//   size: integer (size_t)
//   link[]: link array (Lnk2[])
// Declarations
//   Mod2
//   struct type_mod2

typedef struct type_mod2 {
  Sph2 sph;
  size_t size;
  #ifdef SOL_FAM
        Lnk2 link[];
  #else
        Lnk2 *link;
  #endif
} *Mod2;

/// Mod3 ///
// Description
//   A type comprised of a bounding sphere, an array of links, and an integer
//   representing the size of the link array.
// Fields
//   sph: bounding sphere (Sph3)
//   size: integer (size_t)
//   link[]: link array (Lnk3[])
// Declarations
//   Mod2
//   struct type_mod2

typedef struct type_mod3 {
  Sph3 sph;
  size_t size;
  #ifdef SOL_FAM
        Lnk3 link[];
  #else
        Lnk3 *link;
  #endif
} *Mod3;

  //////////////////////////////////////////////////////////////////////////////
 // Vec2 Function Declarations ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Vec2 vec2_init(sol_f x, sol_f y);
Vec2 vec2_initf(sol_f f);
Vec2 vec2_zero(void);

Vec2 vec2_norm(Vec2 v);
sol_f vec2_mag(Vec2 v);

Vec2 vec2_rot(Vec2 v, sol_f rad);

sol_f vec2_cross(Vec2 a, Vec2 b);
sol_f vec2_dot(Vec2 a, Vec2 b);

sol_f vec2_sum(Vec2 a, Vec2 b);
Vec2 vec2_add(Vec2 a, Vec2 b);
Vec2 vec2_addf(Vec2 v, sol_f f);
Vec2 vec2_sub(Vec2 a, Vec2 b);
Vec2 vec2_subf(Vec2 v, sol_f f);
Vec2 vec2_fsub(sol_f f, Vec2 v);
Vec2 vec2_mult(Vec2 a, Vec2 b);
Vec2 vec2_multf(Vec2 v, sol_f f);
Vec2 vec2_div(Vec2 a, Vec2 b);
Vec2 vec2_divf(Vec2 v, sol_f f);
Vec2 vec2_fdiv(sol_f f, Vec2 v);
Vec2 vec2_avg(Vec2 a, Vec2 b);
Vec2 vec2_avgf(Vec2 v, sol_f f);

void vec2_print(Vec2 v);

  //////////////////////////////////////////////////////////////////////////////
 // Vec3 Function Declarations ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Vec3 vec3_init(sol_f x, sol_f y, sol_f z);
Vec3 vec3_initf(sol_f f);
Vec3 vec3_zero(void);

Vec3 vec3_norm(Vec3 v);
sol_f vec3_mag(Vec3 v);

Vec3 vec3_rot(Vec3 v, Vec4 q);

Vec3 vec3_cross(Vec3 a, Vec3 b);
sol_f vec3_dot(Vec3 a, Vec3 b);

sol_f vec3_sum(Vec3 a, Vec3 b);
Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_addf(Vec3 v, sol_f f);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_subf(Vec3 v, sol_f f);
Vec3 vec3_fsub(sol_f f, Vec3 v);
Vec3 vec3_mult(Vec3 a, Vec3 b);
Vec3 vec3_multf(Vec3 v, sol_f f);
Vec3 vec3_div(Vec3 a, Vec3 b);
Vec3 vec3_divf(Vec3 v, sol_f f);
Vec3 vec3_fdiv(sol_f f, Vec3 v);
Vec3 vec3_avg(Vec3 a, Vec3 b);
Vec3 vec3_avgf(Vec3 v, sol_f f);

void vec3_print(Vec3 v);

  //////////////////////////////////////////////////////////////////////////////
 // Vec4 Function Declarations ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Vec4 vec4_init(sol_f x, sol_f y, sol_f z, sol_f w);
Vec4 vec4_initf(sol_f f);
Vec4 vec4_zero(void);

Vec4 vec4_norm(Vec4 q);
sol_f vec4_mag(Vec4 q);

void vec4_print(Vec4 q);

#ifdef __cplusplus
      }
#endif

#endif
