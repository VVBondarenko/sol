###########################################################
## sol.nim ################################################
## Description: Nim bindings for the Sol vector library. ##
## Author: Team Epoch (https://github.com/TeamEpoch/sol) ##
###########################################################

################################################################################
# Compiler Configuration #######################################################
################################################################################

{.emit: """
#define SOL_F_SIZE 64
#define SOL_NO_FAM
""".}

{.passc:"-I.".}
{.passl:"-lm".}

################################################################################
# Type Definitions #############################################################
################################################################################

type sol_f = cdouble

type Vec2* {.importc: "Vec2", header: "sol.h".} = object
    x*, y*: sol_f

type Vec3* {.importc: "Vec3", header: "sol.h".} = object
    x*, y*, z*: sol_f

type Vec4* {.importc: "Vec4", header: "sol.h".} = object
    x*, y*, z*, w*: sol_f

type Seg2* {.importc: "Seg2", header: "sol.h".} = object
    orig*, dest*: Vec2

type Seg3* {.importc: "Seg3", header: "sol.h".} = object
    orig*, dest*: Vec3

type Box2* {.importc: "Box2", header: "sol.h".} = object
    min*, max*: Vec2

type Box3* {.importc: "Box3", header: "sol.h".} = object
    min*, max*: Vec3

type Sph2* {.importc: "Sph2", header: "so.h".} = object
    pos*: Vec2
    radius*: sol_f

type Sph3* {.importc: "Sph3", header: "sol.h".} = object
    pos*: Vec3
    radius*: sol_f

type Lnk2* {.importc: "Lnk2", header: "sol.h".} = object
    pos*: Vec2
    next*: cuint

type Lnk3* {.importc: "Lnk3", header: "sol.h".} = object
    pos*: Vec3
    next*: cuint

type Mod2* {.importc: "Mod2", header: "sol.h".} = object
    size*: cuint
    link*: ptr Lnk2

type Mod3* {.importc: "Mod3", header: "sol.h".} = object
    size*: cuint
    link*: ptr Lnk3

################################################################################
# Vec2 Functions ###############################################################
################################################################################

proc vec2_init*(x, y: sol_f): Vec2 {.importc: "vec2_init", header: "sol.h".}
proc vec2_initf*(f: sol_f): Vec2 {.importc: "vec2_initf", header: "sol.h".}
proc vec2_zero*(): Vec2 {.importc: "vec2_zero", header: "sol.h".}

proc vec2_norm*(v: Vec2): Vec2 {.importc: "vec2_norm", header: "sol.h".}
proc vec2_mag*(v: Vec2): sol_f {.importc: "vec2_mag", header: "sol.h".}

proc vec2_rot*(v: Vec2, rad: sol_f): sol_f {.importc: "vec2_rot", header: "sol.h".}

proc vec2_dot*(a, b: Vec2): sol_f {.importc: "vec2_dot", header: "sol.h".}

proc vec2_add*(a, b: Vec2): Vec2 {.importc: "vec2_add", header: "sol.h".}
proc vec2_addf*(v: Vec2, f: sol_f): Vec2 {.importc: "vec2_addf", header: "sol.h".}
proc vec2_sub*(a, b: Vec2): Vec2 {.importc: "vec2_sub", header: "sol.h".}
proc vec2_subf*(v: Vec2, f: sol_f): Vec2 {.importc: "vec2_subf", header: "sol.h".}
proc vec2_fsub*(f: sol_f, v: Vec2): Vec2 {.importc: "vec2_fsub", header: "sol.h".}
proc vec2_mult*(a, b: Vec2): Vec2 {.importc: "vec2_mult", header: "sol.h".}
proc vec2_multf*(v: Vec2, f: sol_f): Vec2 {.importc: "vec2_multf", header: "sol.h".}
proc vec2_div*(a, b: Vec2): Vec2 {.importc: "vec2_div", header: "sol.h".}
proc vec2_divf*(v: Vec2, f: sol_f): Vec2 {.importc: "vec2_divf", header: "sol.h".}
proc vec2_fdiv*(f: sol_f, v: Vec2): Vec2 {.importc: "vec2_fdiv", header: "sol.h".}

proc vec2_print*(v: Vec2): void {.importc: "vec2_print", header: "sol.h".}

################################################################################
# Vec3 Functions ###############################################################
################################################################################

proc vec3_init*(x, y, z: sol_f): Vec3 {.importc: "vec3_init", header: "sol.h".}
proc vec3_initf*(f: sol_f): Vec3 {.importc: "vec3_initf", header: "sol.h".}
proc vec3_zero*(): Vec3 {.importc: "vec3_zero", header: "sol.h".}

proc vec3_norm*(v: Vec3): Vec3 {.importc: "vec3_norm", header: "sol.h".}
proc vec3_mag*(v: Vec3): sol_f {.importc: "vec3_mag", header: "sol.h".}

proc vec3_rot*(v: Vec3, q: Vec4): Vec3 {.importc: "vec3_rot", header: "sol.h".}

proc vec3_cross*(a, b: Vec3): Vec3 {.importc: "vec3_cross", header: "sol.h".}
proc vec3_dot*(a, b: Vec3): Vec3 {.importc: "vec3_dot", header: "sol.h".}

proc vec3_add*(a, b: Vec3): Vec3 {.importc: "vec3_add", header: "sol.h".}
proc vec3_addf*(v: Vec3, f: sol_f): Vec3 {.importc: "vec3_addf", header: "sol.h".}
proc vec3_sub*(a, b: Vec3): Vec3 {.importc: "vec3_sub", header: "sol.h".}
proc vec3_subf*(v: Vec3, f: sol_f): Vec3 {.importc: "vec3_subf", header: "sol.h".}
proc vec3_fsub*(f: sol_f, v: Vec3): Vec3 {.importc: "vec3_fsub", header: "sol.h".}
proc vec3_mult*(a, b: Vec3): Vec3 {.importc: "vec3_mult", header: "sol.h".}
proc vec3_multf*(v: Vec3, f: sol_f): Vec3 {.importc: "vec3_multf", header: "sol.h".}
proc vec3_div*(a, b: Vec3): Vec3 {.importc: "vec3_div", header: "sol.h".}
proc vec3_divf*(v: Vec3, f: sol_f): Vec3 {.importc: "vec3_divf", header: "sol.h".}
proc vec3_fdiv*(f: sol_f, v: Vec3): Vec3 {.importc: "vec3_fdiv", header: "sol.h".}

proc vec3_print*(v: Vec3): void {.importc: "vec3_print", header: "sol.h".}

################################################################################
# Vec4 Functions ###############################################################
################################################################################

proc vec4_init*(x, y, z, w: sol_f): Vec4 {.importc: "vec4_init", header: "sol.h".}
proc vec4_initf*(f: sol_f): Vec4 {.importc: "vec4_initf", header: "sol.h".}
proc vec4_zero*(): Vec4 {.importc: "vec4_zero", header: "sol.h".}

proc vec4_norm*(v: Vec4): Vec4 {.importc: "vec4_norm", header: "sol.h".}
proc vec4_mag*(v: Vec4): sol_f {.importc: "vec4_mag", header: "sol.h".}

proc vec4_print*(v: Vec4): void {.importc: "vec4_print", header: "sol.h".}
