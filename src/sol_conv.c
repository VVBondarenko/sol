  ////////////////
 // sol_conv.c //
////////////////

  ///////////////////
 // Local Headers //
///////////////////

#include "../sol.h"

  //////////////////////
 // Standard Headers //
//////////////////////

#include <math.h>

  ///////////////////////
 // Vector Conversion //
///////////////////////

/// cv_axis_quat ///
// Description
//   Converts an axis-angle representation
//   into a quaternion. The "w" element of
//   Vec4 is used for the angle, which is
//   in radians.
// Arguments
//   axis: Axis-Angle (Vec4)
// Returns
//   Quaternion (Vec4)

sol_inline
Vec4 cv_axis_quat(Vec4 axis) {
  const Float w = axis.w / 2;
  const Float s = flt_sin(w);
  return vec4_init(axis.x * s,
                   axis.y * s,
                   axis.z * s,
                   flt_cos(w));
}

/// cv_quat_axis ///
// Description
//   Converts a quaternion into its axis-angle
//   representation. The "w" element of Vec4 is
//   used for the angle, which is in radians.
// Arguments
//   quat: Quaternion (Vec4)
// Returns
//   Axis-Angle (Vec4)

sol_inline
Vec4 cv_quat_axis(Vec4 quat) {
  const Float s = flt_sqrt(1 - (quat.w * 2));
  return vec4_init(quat.x * s,
                   quat.y * s,
                   quat.z * s,
                   2 * flt_acos(quat.w));
}

  ////////////////////
 // Vector Casting //
////////////////////

sol_inline
Vec2 cv_vec3_vec2(Vec3 v) {
  return vec2_init(v.x, v.y);
}

sol_inline
Vec2 cv_vec4_vec2(Vec4 v) {
  return vec2_init(v.x, v.y);
}

sol_inline
Vec3 cv_vec2_vec3(Vec2 v, Float z) {
  return vec3_init(v.x, v.y, z);
}

sol_inline
Vec3 cv_vec4_vec3(Vec4 v) {
  return vec3_init(v.x, v.y, v.z);
}

sol_inline
Vec4 cv_vec2_vec4(Vec2 v, Float z, Float w) {
  return vec4_init(v.x, v.y, z, w);
}

sol_inline
Vec4 cv_vec3_vec4(Vec3 v, Float w) {
  return vec4_init(v.x, v.y, v.z, w);
}

  ///////////////////////
 // Scalar Conversion //
///////////////////////

sol_inline
Float cv_deg_rad(Float deg) {
  return deg * (M_PI / 180);
}

sol_inline
Float cv_rad_deg(Float rad) {
  return rad * (180 / M_PI);
}
