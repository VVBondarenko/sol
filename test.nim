import sol

var v = vec2(0, 1)
var v2 = vec3(0, 1, 0)
var q = axis(1, 0, 0, 90.cv_deg_rad)

while true:
    v = v.rot(90.cv_deg_rad)
    v2 = v2.rot(q)
    echo "Vec2: ", v
    echo "Vec3: ", v2
