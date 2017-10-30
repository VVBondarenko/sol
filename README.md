# Sol
## A vector library written in pure C.
Sol is a fast, maintainable, and portable vector library written in C.

Nim bindings are provided "out of the box" for those who don't want to deal with C's memory management or lack of high level features, but still want to enjoy the speed benefits Sol provides.

## Disclaimer
This is a hobbyist project. Please don't use this for production-level code until further notice.

# Goals
## Speed *(Why C?)*
C is well-known for being a "fast" language, not because the language spec itself somehow makes it fast, but because the cost of low-level operations is well-displayed to the programmer and because of compiler maturity and ready availability of intrinsics without any sort of linking overhead.

For these reasons, C was chosen.

## Maintainability *(Why not C++?)*
Although it may seem antithetical to call C maintainable, C's lack of high level features to distract from optimization help avoid data-hiding antipatterns which are common in OOP code; using a higher-level language invites use of these antipatterns.

Instead of Sol's functions being interfaces for a class, they are just more streamlined and efficient SIMD-optimized versions of what the end programmer wants-- the way a library should be.

## Portability *(Aren't intrinsics, well, platform intrinsic?)*
By using the target platform macros available in most modern C compilers, it is possible to discern wether or not the target platform supports a given intrinsic, and adjust the generated code accordingly. 

Thanks to this, Sol can be made to use only standard C or to automatically adapt to the target platform.

## Ease of Contribution
Commentation is done before each function to help improve the readability of the library to newcomers. An example of this is shown below.

```C
/// vec3_add ///
// Description
//   Adds the elements of two vectors.
// Arguments
//   a: vector (Vec3)
//   b: vector (Vec3)
// Returns
//   vector (Vec3) {a.xyz + b.xyz}

sol_inline
Vec3 vec3_add(Vec3 a, Vec3 b) {
  // etc.
}
```

# Features
## Implemented
2D Vectors (`Vec2`)

3D Vectors (`Vec3`)

4D Vectors (`Vec4`)

## Planned
2D Lines (`Lin2`)

3D Lines (`Lin3`)

2D Rays (`Ray2`)

3D Rays (`Ray3`)

2D Segments (`Seg2`)

3D Segments (`Seg3`)

2D Boxes (`Box2`)

3D Boxes (`Box3`)

2D Spheres* (`Sph2`)

3D Spheres (`Sph3`)

* Better known as "Circles", but muh consistency.

# Examples
Here are some basic examples for C and Nim, using Sol bundled into the current directory.
## C
```C
#include "sol/sol.h"

int main() {
  Vec3 a = vec3_init(0, 1, 2);
  Vec3 b = vec3_init(2, 1, 0);
  Vec3 c = vec3_cross(a, b);
  vec3_print(c);
  return 0;
}
```
## Nim
```Nim
import sol/sol

var a = vec3_init(0, 1, 2)
var b = vec3_init(2, 1, 0)
var c = vec3_cross(a, b)
vec3_print(c)
```
