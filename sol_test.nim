import sol

var a: Vec3 = vec3_init(0, 1, 2)
var b: Vec3 = vec3_init(2, 1, 0)
var c: Vec3 = vec3_cross(a, b)
vec3_print(c)
