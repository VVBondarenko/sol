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
{.compile: "./src/sol_vec2.c".}
{.compile: "./src/sol_vec3.c".}
{.compile: "./src/sol_vec4.c".}

{.passc:"-I.".}
{.passl:"-lm".}

################################################################################
# Type Definitions #############################################################
################################################################################

type Float {.importc: "Float", header: "sol.h".} = cfloat

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

proc flt_clamp(f, lower, upper: Float): Float {.importc: "flt_clamp", header: "sol.h".}
proc flt_pow(a, b: Float): Float {.importc: "flt_pow", header: "sol.h".}
proc flt_sqrt(f: Float): Float {.importc: "flt_sqrt", header: "sol.h".}
proc flt_sin(f: Float): Float {.importc: "flt_sin", header: "sol.h".}
proc flt_cos(f: Float): Float {.importc: "flt_cos", header: "sol.h".}

################################################################################
# Vec2 Functions ###############################################################
################################################################################

proc vec2_init*(x, y: Float): Vec2 {.importc: "vec2_init", header: "sol.h".}
proc vec2_initf*(f: Float): Vec2 {.importc: "vec2_initf", header: "sol.h".}
proc vec2_zero*(): Vec2 {.importc: "vec2_zero", header: "sol.h".}

proc vec2_norm*(v: Vec2): Vec2 {.importc: "vec2_norm", header: "sol.h".}
proc vec2_mag*(v: Vec2): Float {.importc: "vec2_mag", header: "sol.h".}

proc vec2_rot*(v: Vec2, rad: Float): Float {.importc: "vec2_rot", header: "sol.h".}

proc vec2_dot*(a, b: Vec2): Float {.importc: "vec2_dot", header: "sol.h".}

proc vec2_sum*(v: Vec2): Float {.importc: "vec2_sum", header: "sol.h".}
proc vec2_add*(a, b: Vec2): Vec2 {.importc: "vec2_add", header: "sol.h".}
proc vec2_addf*(v: Vec2, f: Float): Vec2 {.importc: "vec2_addf", header: "sol.h".}
proc vec2_sub*(a, b: Vec2): Vec2 {.importc: "vec2_sub", header: "sol.h".}
proc vec2_subf*(v: Vec2, f: Float): Vec2 {.importc: "vec2_subf", header: "sol.h".}
proc vec2_fsub*(f: Float, v: Vec2): Vec2 {.importc: "vec2_fsub", header: "sol.h".}
proc vec2_mult*(a, b: Vec2): Vec2 {.importc: "vec2_mult", header: "sol.h".}
proc vec2_multf*(v: Vec2, f: Float): Vec2 {.importc: "vec2_multf", header: "sol.h".}
proc vec2_div*(a, b: Vec2): Vec2 {.importc: "vec2_div", header: "sol.h".}
proc vec2_divf*(v: Vec2, f: Float): Vec2 {.importc: "vec2_divf", header: "sol.h".}
proc vec2_fdiv*(f: Float, v: Vec2): Vec2 {.importc: "vec2_fdiv", header: "sol.h".}

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
proc vec3_dot*(a, b: Vec3): Vec3 {.importc: "vec3_dot", header: "sol.h".}

proc vec3_sum*(v: Vec3): Float {.importc: "vec3_sum", header: "sol.h".}
proc vec3_add*(a, b: Vec3): Vec3 {.importc: "vec3_add", header: "sol.h".}
proc vec3_addf*(v: Vec3, f: Float): Vec3 {.importc: "vec3_addf", header: "sol.h".}
proc vec3_sub*(a, b: Vec3): Vec3 {.importc: "vec3_sub", header: "sol.h".}
proc vec3_subf*(v: Vec3, f: Float): Vec3 {.importc: "vec3_subf", header: "sol.h".}
proc vec3_fsub*(f: Float, v: Vec3): Vec3 {.importc: "vec3_fsub", header: "sol.h".}
proc vec3_mult*(a, b: Vec3): Vec3 {.importc: "vec3_mult", header: "sol.h".}
proc vec3_multf*(v: Vec3, f: Float): Vec3 {.importc: "vec3_multf", header: "sol.h".}
proc vec3_div*(a, b: Vec3): Vec3 {.importc: "vec3_div", header: "sol.h".}
proc vec3_divf*(v: Vec3, f: Float): Vec3 {.importc: "vec3_divf", header: "sol.h".}
proc vec3_fdiv*(f: Float, v: Vec3): Vec3 {.importc: "vec3_fdiv", header: "sol.h".}

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
proc vec4_addf*(v: Vec4, f: Float): Vec4 {.importc: "vec4_addf", header: "sol.h".}
proc vec4_sub*(a, b: Vec4): Vec4 {.importc: "vec4_sub", header: "sol.h".}
proc vec4_subf*(v: Vec4, f: Float): Vec4 {.importc: "vec4_subf", header: "sol.h".}
proc vec4_fsub*(f: Float, v: Vec4): Vec4 {.importc: "vec4_fsub", header: "sol.h".}
proc vec4_div*(a, b: Vec4): Vec4 {.importc: "vec4_div", header: "sol.h".}
proc vec4_divf*(v: Vec4, f: Float): Vec4 {.importc: "vec4_divf", header: "sol.h".}
proc vec4_fdiv*(f: Float, v: Vec4): Vec4 {.importc: "vec4_fdiv", header: "sol.h".}
proc vec4_avg*(a, b: Vec4): Vec4 {.importc: "vec4_avg", header: "sol.h".}
proc vec4_avgf*(v: Vec4, f: Float): Vec4 {.importc: "vec4_avgf", header: "sol.h".}

proc vec4_print*(v: Vec4): void {.importc: "vec4_print", header: "sol.h".}
