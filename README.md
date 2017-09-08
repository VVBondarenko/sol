# Sol
Sol is an experimental vector library written in C.

# Notice
Sol is not intended to be production-ready code. It is just a hobbyist project. If you use Sol in a large project, be aware that you will have to take responsibility for any bugs that it may have.

# Examples

```C
// C Example
#include <sol/sol.h>

int main(int argc, char **argv) {
  Vec2 a = vec2_init(0, 1, 2);
  Vec2 b = vec2_init(2, 1, 0);
  Vec2 c = vec2_cross(a, b);
  vec2_print(c);
  return 0;
}
```
NOTE: I am uncertain if Nim can leverage an install of sol.
```Nim
# Nim Example
import sol/sol

var a: Vec2 = vec2_init(0, 1, 2)
var b: Vec2 = vec2_init(2, 1, 0)
var c: Vec2 = vec2_cross(a, b)
vec2_print(c)
```
NOTE: I am uncertain if Terra can leverage an install of sol.
```Terra
-- Terra Example
local sol = require("sol/sol")

a = sol.vec2_init(0, 1, 2)
b = sol.vec2_init(2, 1, 0)
c = sol.vec2_cross(a, b)
sol.vec2_print(c)
```

# Installation
Installing Sol will add the source code to your `/usr/local/include` directory and the static and dynamic libraries (`libsol-a.a` and `libsol-so.so`) built via gcc to your `/usr/local/lib` directory.

Note that this is optional-- you could just bundle Sol into your application.

```Bash
git clone https://github.com/TeamEpoch/sol
cd sol
make install ARGS=-O2 # The ARGS variable passes command line arguments to cc.
```

Side tip: You can use the "-D" option to pass macros to the compiler via the `ARGS` variable exposed by the Makefile, so you could enable features like `SOL_OMP`, `SOL_SIMD`, etc. as you please. Such optimizations could lead to huge performance gains if your target platform supports them.

# Library Usage
Suppose we've installed Sol and have the following code:

```C
// test.c
#include <sol/sol.h>

int main() {
  Vec2 a = vec2_init(0, 5);
  vec2_print(a);
}
```

To compile this with the static Sol library:

```Bash
cc test.c -lsol-a -L/usr/local/lib -lm
```

To compile it with the dynamic Sol library:

```Bash
cc test.c -lsol-so -L/usr/local/lib
```

Note that to run the dynamic version you must do:

```Bash
export LD_LIBRARY_PATH=/usr/local/lib
```

before runtime.
