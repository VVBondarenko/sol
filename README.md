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

```
// Nim Example
import sol/sol

var a: Vec2 = vec2_init(0, 1, 2)
var b: Vec2 = vec2_init(2, 1, 0)
var c: Vec2 = vec2_cross(a, b)
vec2_print(c)
```

```
-- Terra Example
local sol = require("sol/sol")

a = sol.vec2_init(0, 1, 2)
b = sol.vec2_init(2, 1, 0)
c = sol.vec2_cross(a, b)
sol.vec2_print(c)
```
