##################################################################
## sol.nim #######################################################
## Description: Nim bindings for the Sol vector library. #########
## Author: David Garland (https://github.com/davidgarland/sol) ###
##################################################################

################################################################################
# Compiler Configuration #######################################################
################################################################################

{.emit:
"""
   #define SOL_F_SIZE 32
   #define SOL_NO_FAM
   #define SOL_INLINE
   #define SOL_SIMD
"""
.}

{.compile: "./src/sol_flt.c".}
{.compile: "./src/sol_conv.c".}
{.compile: "./src/sol_vec2.c".}
{.compile: "./src/sol_vec3.c".}
{.compile: "./src/sol_vec4.c".}

{.passc:"-I.".}
{.passl:"-lm".}

################################################################################
# Type Definitions #############################################################
################################################################################

type Float* {.importc: "Float", header: "sol.h".} = cfloat

type Vec2* {.importc: "Vec2", header: "sol.h".} = object
    x*, y*: Float

type Vec3* {.importc: "Vec3", header: "sol.h".} = object
    x*, y*, z*: Float

type Vec4* {.importc: "Vec4", header: "sol.h".} = object
    x*, y*, z*, w*: Float

type Seg2* {.importc: "Seg2", header: "sol.h".} = object
    orig*, dest*: Vec2

type Seg3* {.importc: "Seg3", header: "sol.h".} = object
    orig*, dest*: Vec3

type Box2* {.importc: "Box2", header: "sol.h".} = object
    lower*, upper*: Vec2

type Box3* {.importc: "Box3", header: "sol.h".} = object
    lower*, upper*: Vec3

type Sph2* {.importc: "Sph2", header: "sol.h".} = object
    pos*: Vec2
    rad*: Float

type Sph3* {.importc: "Sph3", header: "sol.h".} = object
    pos*: Vec3
    rad*: Float

################################################################################
# Float Functions ##############################################################
################################################################################

proc flt_clamp*(f, lower, upper: Float): Float {.importc: "flt_clamp", header: "sol.h".}
proc flt_pow*(a, b: Float): Float {.importc: "flt_pow", header: "sol.h".}
proc flt_sqrt*(f: Float): Float {.importc: "flt_sqrt", header: "sol.h".}
proc flt_sin*(f: Float): Float {.importc: "flt_sin", header: "sol.h".}
proc flt_cos*(f: Float): Float {.importc: "flt_cos", header: "sol.h".}
proc flt_acos*(f: Float): Float {.importc: "flt_acos", header: "sol.h".}

################################################################################
# Conversion Functions #########################################################
################################################################################

proc cv_axis_quat*(axis: Vec4): Vec4 {.importc: "cv_axis_quat", header: "sol.h".}
proc cv_quat_axis*(quat: Vec4): Vec4 {.importc: "cv_quat_axis", header: "sol.h".}

proc cv_vec3_vec2*(v: Vec3): Vec2 {.importc: "cv_vec3_vec2", header: "sol.h".}
proc cv_vec4_vec2*(v: Vec4): Vec2 {.importc: "cv_vec4_vec2", header: "sol.h".}
proc cv_vec2_vec3*(v: Vec2; z: Float): Vec3 {.importc: "cv_vec2_vec3", header: "sol.h".}
proc cv_vec4_vec3*(v: Vec4): Vec3 {.importc: "cv_vec4_vec3", header: "sol.h".}
proc cv_vec2_vec4*(v: Vec2; z, w: Float): Vec4 {.importc: "cv_vec2_vec4", header: "sol.h".}
proc cv_vec3_vec4*(v: Vec3; w: Float): Vec4 {.importc: "cv_vec3_vec4", header: "sol.h".}

proc cv_deg_rad*(deg: Float): Float {.importc: "cv_deg_rad", header: "sol.h".}
proc cv_rad_deg*(rad: Float): Float {.importc: "cv_rad_deg", header: "sol.h".}

################################################################################
# Vec2 Functions ###############################################################
################################################################################

proc vec2_init*(x, y: Float): Vec2 {.importc: "vec2_init", header: "sol.h".}
proc vec2_initf*(f: Float): Vec2 {.importc: "vec2_initf", header: "sol.h".}
proc vec2_zero*(): Vec2 {.importc: "vec2_zero", header: "sol.h".}

proc vec2_norm*(v: Vec2): Vec2 {.importc: "vec2_norm", header: "sol.h".}
proc vec2_mag*(v: Vec2): Float {.importc: "vec2_mag", header: "sol.h".}

proc vec2_rot*(v: Vec2, rad: Float): Vec2 {.importc: "vec2_rot", header: "sol.h".}

proc vec2_cross*(a, b: Vec2): Float {.importc: "vec2_cross", header: "sol.h".}
proc vec2_dot*(a, b: Vec2): Float {.importc: "vec2_dot", header: "sol.h".}

proc vec2_sum*(v: Vec2): Float {.importc: "vec2_sum", header: "sol.h".}
proc vec2_add*(a, b: Vec2): Vec2 {.importc: "vec2_add", header: "sol.h".}
proc vec2_addf*(v: Vec2, f: Float): Vec2 {.importc: "vec2_addf", header: "sol.h".}
proc vec2_sub*(a, b: Vec2): Vec2 {.importc: "vec2_sub", header: "sol.h".}
proc vec2_subf*(v: Vec2, f: Float): Vec2 {.importc: "vec2_subf", header: "sol.h".}
proc vec2_fsub*(f: Float, v: Vec2): Vec2 {.importc: "vec2_fsub", header: "sol.h".}
proc vec2_mul*(a, b: Vec2): Vec2 {.importc: "vec2_mul", header: "sol.h".}
proc vec2_mulf*(v: Vec2, f: Float): Vec2 {.importc: "vec2_mulf", header: "sol.h".}
proc vec2_div*(a, b: Vec2): Vec2 {.importc: "vec2_div", header: "sol.h".}
proc vec2_divf*(v: Vec2, f: Float): Vec2 {.importc: "vec2_divf", header: "sol.h".}
proc vec2_fdiv*(f: Float, v: Vec2): Vec2 {.importc: "vec2_fdiv", header: "sol.h".}
proc vec2_avg*(a, b: Vec2): Vec2 {.importc: "vec2_avg", header: "sol.h".}
proc vec2_avgf*(v: Vec2, f: Float): Vec2 {.importc: "vec2_avgf", header: "sol.h".}

proc vec2_print*(v: Vec2): void {.importc: "vec2_print", header: "sol.h".}

################################################################################
# Vec3 Functions ###############################################################
################################################################################

proc vec3_init*(x, y, z: Float): Vec3 {.importc: "vec3_init", header: "sol.h".}
proc vec3_initf*(f: Float): Vec3 {.importc: "vec3_initf", header: "sol.h".}
proc vec3_zero*(): Vec3 {.importc: "vec3_zero", header: "sol.h".}

proc vec3_norm*(v: Vec3): Vec3 {.importc: "vec3_norm", header: "sol.h".}
proc vec3_mag*(v: Vec3): Float {.importc: "vec3_mag", header: "sol.h".}

proc vec3_rot*(v: Vec3, q: Vec4): Vec3 {.importc: "vec3_rot", header: "sol.h".}

proc vec3_cross*(a, b: Vec3): Vec3 {.importc: "vec3_cross", header: "sol.h".}
proc vec3_dot*(a, b: Vec3): Float {.importc: "vec3_dot", header: "sol.h".}

proc vec3_sum*(v: Vec3): Float {.importc: "vec3_sum", header: "sol.h".}
proc vec3_add*(a, b: Vec3): Vec3 {.importc: "vec3_add", header: "sol.h".}
proc vec3_addf*(v: Vec3, f: Float): Vec3 {.importc: "vec3_addf", header: "sol.h".}
proc vec3_sub*(a, b: Vec3): Vec3 {.importc: "vec3_sub", header: "sol.h".}
proc vec3_subf*(v: Vec3, f: Float): Vec3 {.importc: "vec3_subf", header: "sol.h".}
proc vec3_fsub*(f: Float, v: Vec3): Vec3 {.importc: "vec3_fsub", header: "sol.h".}
proc vec3_mul*(a, b: Vec3): Vec3 {.importc: "vec3_mul", header: "sol.h".}
proc vec3_mulf*(v: Vec3, f: Float): Vec3 {.importc: "vec3_mulf", header: "sol.h".}
proc vec3_div*(a, b: Vec3): Vec3 {.importc: "vec3_div", header: "sol.h".}
proc vec3_divf*(v: Vec3, f: Float): Vec3 {.importc: "vec3_divf", header: "sol.h".}
proc vec3_fdiv*(f: Float, v: Vec3): Vec3 {.importc: "vec3_fdiv", header: "sol.h".}
proc vec3_avg*(a, b: Vec3): Vec3 {.importc: "vec3_avg", header: "sol.h".}
proc vec3_avgf*(v: Vec3, f: Float): Vec3 {.importc: "vec3_avgf", header: "sol.h".}

proc vec3_print*(v: Vec3): void {.importc: "vec3_print", header: "sol.h".}

################################################################################
# Vec4 Functions ###############################################################
################################################################################

proc vec4_init*(x, y, z, w: Float): Vec4 {.importc: "vec4_init", header: "sol.h".}
proc vec4_initf*(f: Float): Vec4 {.importc: "vec4_initf", header: "sol.h".}
proc vec4_zero*(): Vec4 {.importc: "vec4_zero", header: "sol.h".}

proc vec4_norm*(v: Vec4): Vec4 {.importc: "vec4_norm", header: "sol.h".}
proc vec4_mag*(v: Vec4): Float {.importc: "vec4_mag", header: "sol.h".}

proc vec4_sum*(v: Vec4): Float {.importc: "vec4_sum", header: "sol.h".}
proc vec4_add*(a, b: Vec4): Vec4 {.importc: "vec4_add", header: "sol.h".}
proc vec4_addf*(v: Vec4; f: Float): Vec4 {.importc: "vec4_addf", header: "sol.h".}
proc vec4_sub*(a, b: Vec4): Vec4 {.importc: "vec4_sub", header: "sol.h".}
proc vec4_subf*(v: Vec4; f: Float): Vec4 {.importc: "vec4_subf", header: "sol.h".}
proc vec4_fsub*(f: Float; v: Vec4): Vec4 {.importc: "vec4_fsub", header: "sol.h".}
proc vec4_mul*(a, b: Vec4): Vec4 {.importc: "vec4_mul", header: "sol.h".}
proc vec4_mulf*(v: Vec4; f: Float): Vec4 {.importc: "vec4_mulf", header: "sol.h".}
proc vec4_div*(a, b: Vec4): Vec4 {.importc: "vec4_div", header: "sol.h".}
proc vec4_divf*(v: Vec4; f: Float): Vec4 {.importc: "vec4_divf", header: "sol.h".}
proc vec4_fdiv*(f: Float; v: Vec4): Vec4 {.importc: "vec4_fdiv", header: "sol.h".}
proc vec4_avg*(a, b: Vec4): Vec4 {.importc: "vec4_avg", header: "sol.h".}
proc vec4_avgf*(v: Vec4, f: Float): Vec4 {.importc: "vec4_avgf", header: "sol.h".}

proc vec4_print*(v: Vec4): void {.importc: "vec4_print", header: "sol.h".}

#########################
# Vec2 Initializer Meta #
#########################

proc vec2*(x, y: Float): Vec2 {.inline.} =
    return vec2_init(x, y)

proc vec*(x, y: Float): Vec2 {.inline.} =
    return vec2_init(x, y)

######################
# Vec2 Advanced Meta #
######################

proc norm*(v: Vec2): Vec2 {.inline.} =
    return vec2_norm(v)

proc mag*(v: Vec2): Float {.inline.} =
    return vec2_mag(v)

proc rot*(v: Vec2; rad: Float): Vec2 {.inline.} =
    return vec2_rot(v, rad)

proc `cross`*(a, b: Vec2): Float {.inline.} =
    return vec2_cross(a, b)

proc `dot`*(a, b: Vec2): Float {.inline.} =
    return vec2_dot(a, b)

#################
# Vec2 Op= Meta #
#################

proc `+=`*(a: var Vec2; b: Vec2) {.inline.} =
    a = vec2_add(a, b)

proc `+=`*(v: var Vec2; f: Float) {.inline.} =
    v = vec2_addf(v, f)

proc `-=`*(a: var Vec2; b: Vec2) {.inline.} =
    a = vec2_sub(a, b)

proc `-=`*(v: var Vec2; f: Float) {.inline.} =
    v = vec2_subf(v, f)

proc `*=`*(a: var Vec2; b: Vec2) {.inline.} =
    a = vec2_mul(a, b)

proc `*=`*(v: var Vec2; f: Float) {.inline.} =
    v = vec2_mulf(v, f)

proc `/=`*(a: var Vec2; b: Vec2) {.inline.} =
    a = vec2_div(a, b)

proc `/=`*(v: var Vec2; f: Float) {.inline.} =
    v = vec2_divf(v, f)

###################
# Vec2 Basic Meta #
###################

proc `+`*(a, b: Vec2): Vec2 {.inline.} =
    return vec2_add(a, b)

proc `+`*(v: Vec2; f: Float): Vec2 {.inline.} =
    return vec2_addf(v, f)

proc `+`*(f: Float; v: Vec2): Vec2 {.inline.} =
    return vec2_addf(v, f)

proc `-`*(a, b: Vec2): Vec2 {.inline.} =
    return vec2_sub(a, b)

proc `-`*(v: Vec2; f: Float): Vec2 {.inline.} =
    return vec2_subf(v, f)

proc `-`*(f: Float; v: Vec2): Vec2 {.inline.} =
    return vec2_fsub(f, v)

proc `*`*(a, b: Vec2): Vec2 {.inline.} =
    return vec2_mul(a, b)

proc `*`*(v: Vec2; f: Float): Vec2 {.inline.} =
    return vec2_mulf(v, f)

proc `*`*(f: Float; v: Vec2): Vec2 {.inline.} =
    return vec2_mulf(v, f)

proc `/`*(a, b: Vec2): Vec2 {.inline.} =
    return vec2_div(a, b)

proc `/`*(v: Vec2; f: Float): Vec2 {.inline.} =
    return vec2_divf(v, f)

proc `/`*(f: Float, v: Vec2): Vec2 {.inline.} =
    return vec2_fdiv(f, v)

#########################
# Vec3 Initializer Meta #
#########################

proc vec3*(x, y, z: Float): Vec3 {.inline.} =
    return vec3_init(x, y, z)

proc vec*(x, y, z: Float): Vec3 {.inline.} =
    return vec3_init(x, y, z)

######################
# Vec3 Advanced Meta #
######################

proc norm*(v: Vec3): Vec3 {.inline.} =
    return vec3_norm(v)

proc mag*(v: Vec3): Float {.inline.} =
    return vec3_mag(v)

proc rot*(v: Vec3; q: Vec4): Vec3 {.inline.} =
    return vec3_rot(v, q)

proc `cross`*(a, b: Vec3): Vec3 {.inline.} =
    return vec3_cross(a, b)

proc `dot`*(a, b: Vec3): Float {.inline.} =
    return vec3_dot(a, b)

#################
# Vec3 Op= Meta #
#################

proc `+=`*(a: var Vec3; b: Vec3) {.inline.} =
    a = vec3_add(a, b)

proc `+=`*(v: var Vec3; f: Float) {.inline.} =
    v = vec3_addf(v, f)

proc `-=`*(a: var Vec3; b: Vec3) {.inline.} =
    a = vec3_sub(a, b)

proc `-=`*(v: var Vec3; f: Float) {.inline.} =
    v = vec3_subf(v, f)

proc `*=`*(a: var Vec3; b: Vec3) {.inline.} =
    a = vec3_mul(a, b)

proc `*=`*(v: var Vec3; f: Float) {.inline.} =
    v = vec3_mulf(v, f)

proc `/=`*(a: var Vec3; b: Vec3) {.inline.} =
    a = vec3_div(a, b)

proc `/=`*(v: var Vec3; f: Float) {.inline.} =
    v = vec3_divf(v, f)

###################
# Vec3 Basic Meta #
###################

proc `+`*(a, b: Vec3): Vec3 {.inline.} =
    return vec3_add(a, b)

proc `+`*(v: Vec3; f: Float): Vec3 {.inline.} =
    return vec3_addf(v, f)

proc `+`*(f: Float, v: Vec3): Vec3 {.inline.} =
    return vec3_addf(v, f)

proc `-`*(a, b: Vec3): Vec3 {.inline.} =
    return vec3_sub(a, b)

proc `-`*(v: Vec3; f: Float): Vec3 {.inline.} =
    return vec3_subf(v, f)

proc `-`*(f: Float; v: Vec3): Vec3 {.inline.} =
    return vec3_fsub(f, v)

proc `*`*(a, b: Vec3): Vec3 {.inline.} =
    return vec3_mul(a, b)

proc `*`*(v: Vec3; f: Float): Vec3 {.inline.} =
    return vec3_mulf(v, f)

proc `*`*(f: Float; v: Vec3): Vec3 {.inline.} =
    return vec3_mulf(v, f)

proc `/`*(a, b: Vec3): Vec3 {.inline.} =
    return vec3_div(a, b)

proc `/`*(v: Vec3; f: Float): Vec3 {.inline.} =
    return vec3_divf(v, f)

proc `/`*(f: Float; v: Vec3): Vec3 {.inline.} =
    return vec3_fdiv(f, v)

#########################
# Vec4 Initializer Meta #
#########################

proc vec4*(x, y, z, w: Float): Vec4 {.inline.} =
    return vec4_init(x, y, z, w)

proc vec*(x, y, z, w: Float): Vec4 {.inline.} =
    return vec4_init(x, y, z, w)

######################
# Vec4 Advanced Meta #
######################

proc norm*(v: Vec4): Vec4 {.inline.} =
    return vec4_norm(v)

proc mag*(v: Vec4): Float {.inline.} =
    return vec4_mag(v)

#################
# Vec4 Op= Meta #
#################

proc `+=`*(a: var Vec4; b: Vec4) {.inline.} =
    a = vec4_add(a, b)

proc `+=`*(v: var Vec4; f: Float) {.inline.} =
    v = vec4_addf(v, f)

proc `-=`*(a: var Vec4; b: Vec4) {.inline.} =
    a = vec4_sub(a, b)

proc `-=`*(v: var Vec4; f: Float) {.inline.} =
    v = vec4_subf(v, f)

proc `*=`*(a: var Vec4; b: Vec4) {.inline.} =
    a = vec4_mul(a, b)

proc `*=`*(v: var Vec4; f: Float) {.inline.} =
    v = vec4_mulf(v, f)

proc `/=`*(a: var Vec4; b: Vec4) {.inline.} =
    a = vec4_div(a, b)

proc `/=`*(v: var Vec4; f: Float) {.inline.} =
    v = vec4_divf(v, f)

###################
# Vec4 Basic Meta #
###################

proc `+`*(a, b: Vec4): Vec4 {.inline.} =
    return vec4_add(a, b)

proc `+`*(v: Vec4; f: Float): Vec4 {.inline.} =
    return vec4_addf(v, f)

proc `+`*(f: Float; v: Vec4): Vec4 {.inline.} =
    return vec4_addf(v, f)

proc `-`*(a, b: Vec4): Vec4 {.inline.} =
    return vec4_sub(a, b)

proc `-`*(v: Vec4; f: Float): Vec4 {.inline.} =
    return vec4_subf(v, f)

proc `-`*(f: Float; v: Vec4): Vec4 {.inline.} =
    return vec4_fsub(f, v)

proc `*`*(a, b: Vec4): Vec4 {.inline.} =
    return vec4_mul(a, b)

proc `*`*(v: Vec4; f: Float): Vec4 {.inline.} =
    return vec4_mulf(v, f)

proc `*`*(f: Float; v: Vec4): Vec4 {.inline.} =
    return vec4_mulf(v, f)

proc `/`*(a, b: Vec4): Vec4 {.inline.} =
    return vec4_div(a, b)

proc `/`*(v: Vec4; f: Float): Vec4 {.inline.} =
    return vec4_divf(v, f)

proc `/`*(f: Float; v: Vec4): Vec4 {.inline.} =
    return vec4_fdiv(f, v)
