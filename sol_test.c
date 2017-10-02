// sol_test.c
#include "sol.h"

int main() {
  Vec2 out = vec2_init(1, 2);
  while(1) {
    out = vec2_multf(out, 1.10);
    vec2_print(out);
    if (out.x > ) { break; }
  }
  return 0;
}
