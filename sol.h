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

  //////////////////////////////////////////////////////////////////////////////
 // Config Processing /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

// SOL_F_SIZE

#if !defined(SOL_F_SIZE)
      #if SOL_F_SIZE_DEFAULT > 64
            #define SOL_F_SIZE 80
      #elif SOL_F_SIZE_DEFAULT > 32
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
            #if defined(__AVX__) || defined(__AVX2__) || defined(__ARM_NEON__)
                  #define SOL_SIMD
            #endif
      #endif
#else
      #ifdef SOL_NO_SIMD
            #undef SOL_SIMD
      #endif
#endif

  //////////////////////////////////////////////////////////////////////////////
 // Environment Checks & Configuration ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#if !defined(__GNUC__) && !defined(__clang__)
      #pragma message ("[sol] Unrecognized compiler. Some features may not work.")
#endif

#ifdef SOL_SIMD
      #if SOL_F_SIZE > 64
           #undef SOL_F_SIZE
           #define SOL_F_SIZE 64
      #endif
      #if !defined(__ARM__) && !defined(__AVX__)
            #pragma message ("[sol] SOL_SIMD cannot be enabled on x86 without AVX.")
            #undef SOL_SIMD
      #endif
#endif

#ifdef SOL_SIMD
      #if defined(__AVX__)
            #if defined(__AVX2__)
                  #define SOL_AVX2
            #endif
            #if SOL_F_SIZE > 32
                  #define SOL_AVX_64
            #endif
            #define SOL_AVX
      #elif defined(__ARM_NEON__)
            #if SOL_F_SIZE > 32
                  #define SOL_NEON_64
            #endif
            #define SOL_NEON
      #endif
#endif

  //////////////////////////////////////////////////////////////////////////////
 // Nonstandard Headers ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#if defined(SOL_AVX)
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

  //////////////////////////////////////////////////////////////////////////////
 // Core Type Definitions /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#if SOL_F_SIZE > 64
      typedef long double Float;
#elif SOL_F_SIZE > 32
      typedef double Float;
#else
      typedef float Float;
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
//   x: dimension (Float)
//   y: dimension (Float)
//   dim: dimensions (Float[2])

typedef struct {
  union {
    struct {
      Float x, y;
    };
    Float dim[2];
    #if defined(SOL_AVX_64)
          __m128d vec;
    #elif defined(SOL_AVX)
          __m128 vec;
    #elif defined(SOL_NEON_64)
          f64x2_t vec;
    #elif defined(SOL_NEON)
          f32x2_t vec;
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
//   dim: dimensions (Float[3])

typedef struct {
  union { 
    struct {
      Float x, y, z;
    };
    Float dim[3];
    #if defined(SOL_AVX_64)
          __m256d vec;
    #elif defined(SOL_AVX)
          __m128 vec;
    #elif defined(SOL_NEON_64)
          f64x4_t vec;
    #elif defined(SOL_NEON)
          f32x4_t vec;
    #endif
  };
} Vec3;

/// Vec4 ///
// Description
//   A type comprised of four floats to represent a quaternion or axis/angle
//   rotation.
// Fields
//   x: dimension (Float)
//   y: dimension (Float)
//   z: dimension (Float)
//   w: dimension (Float)
//   dim: dimensions (Float[4])
// Declarations
//   Vec4
//   struct type_vec4

typedef struct {
  union {
    struct {
      Float x, y, z, w;
    };
    Float dim[4];
    #if defined(SOL_AVX_64)
          __m256d vec;
    #elif defined(SOL_AVX)
          __m128 vec;
    #elif defined(SOL_NEON_64)
          f64x4_t vec;
    #elif defined(SOL_NEON)
          f32x4_t vec;
    #endif
  };
} Vec4;

/// Seg2 ///
// Description
//   A type comprised of two 2D positions that represent a line segment.
// Fields
//   orig: position (Vec2)
//   dest: position (Vec2)

typedef struct {
  Vec2 orig, dest;
} Seg2;

/// Seg3 ///
// Description
//   A type comprised of two 3D positions that represent a line segment.
// Fields
//   orig: position (Vec3)
//   dest: position (Vec3)

typedef struct {
  Vec3 orig, dest;
} Seg3;

/// Box2 ///
// Description
//   A type comprised of two 2D positions that represent a bounding box.
// Fields
//   lower: position (Vec2)
//   upper: position (Vec2)

typedef struct type_box2 {
  Vec2 lower, upper;
} Box2;

/// Box3 ///
// Description
//   A type comprised of two 3D positions that represent a bounding box.
// Fields
//   upper: position (Vec3)
//   lower: position (Vec3)

typedef struct type_box3 {
  Vec3 lower, upper;
} Box3;

/// Sph2 ///
// Description
//   A type comprised of a 2D position and a radius that represent a bounding
//   sphere.
// Fields
//   pos: position (Vec2)
//   rad: radius (Float)

typedef struct type_sph2 {
  Vec2 pos;
  Float rad;
} Sph2;

/// Sph3 ///
// Description
//   A type comprised of a 3D position and a radius that represent a bounding
//   sphere.
// Fields
//   pos: position (Vec3)
//   rad: radius (Float)

typedef struct type_sph3 {
  Vec3 pos;
  Float rad;
} Sph3;

  //////////////////////////////////////////////////////////////////////////////
 // Vec2 Function Declarations ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Vec2 vec2_init(Float x, Float y);
Vec2 vec2_initf(Float f);
Vec2 vec2_zero(void);

Vec2 vec2_norm(Vec2 v);
Float vec2_mag(Vec2 v);

Vec2 vec2_rot(Vec2 v, Float rad);

Float vec2_cross(Vec2 a, Vec2 b);
Float vec2_dot(Vec2 a, Vec2 b);

Float vec2_sum(Vec2 v);
Vec2 vec2_add(Vec2 a, Vec2 b);
Vec2 vec2_addf(Vec2 v, Float f);
Vec2 vec2_sub(Vec2 a, Vec2 b);
Vec2 vec2_subf(Vec2 v, Float f);
Vec2 vec2_fsub(Float f, Vec2 v);
Vec2 vec2_mul(Vec2 a, Vec2 b);
Vec2 vec2_mulf(Vec2 v, Float f);
Vec2 vec2_div(Vec2 a, Vec2 b);
Vec2 vec2_divf(Vec2 v, Float f);
Vec2 vec2_fdiv(Float f, Vec2 v);
Vec2 vec2_avg(Vec2 a, Vec2 b);
Vec2 vec2_avgf(Vec2 v, Float f);

void vec2_print(Vec2 v);

  //////////////////////////////////////////////////////////////////////////////
 // Vec3 Function Declarations ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Vec3 vec3_init(Float x, Float y, Float z);
Vec3 vec3_initf(Float f);
Vec3 vec3_zero(void);

Vec3 vec3_norm(Vec3 v);
Float vec3_mag(Vec3 v);

Vec3 vec3_rot(Vec3 v, Vec4 q);

Vec3 vec3_cross(Vec3 a, Vec3 b);
Float vec3_dot(Vec3 a, Vec3 b);

Float vec3_sum(Vec3 v);
Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_addf(Vec3 v, Float f);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_subf(Vec3 v, Float f);
Vec3 vec3_fsub(Float f, Vec3 v);
Vec3 vec3_mul(Vec3 a, Vec3 b);
Vec3 vec3_mulf(Vec3 v, Float f);
Vec3 vec3_div(Vec3 a, Vec3 b);
Vec3 vec3_divf(Vec3 v, Float f);
Vec3 vec3_fdiv(Float f, Vec3 v);
Vec3 vec3_avg(Vec3 a, Vec3 b);
Vec3 vec3_avgf(Vec3 v, Float f);

void vec3_print(Vec3 v);

  //////////////////////////////////////////////////////////////////////////////
 // Vec4 Function Declarations ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Vec4 vec4_init(Float x, Float y, Float z, Float w);
Vec4 vec4_initf(Float f);
Vec4 vec4_zero(void);

Vec4 vec4_norm(Vec4 q);
Float vec4_mag(Vec4 q);

void vec4_print(Vec4 q);

#ifdef __cplusplus
      }
#endif

#endif
