// sol_test.c
#define SOL_NEON
#define SOL_F_SIZE 32
#include "sol.h"

int main() {
  Vec2 a = vec2_init(1, 0);
  Vec2 b = vec2_init(0, 1);
  Vec2 c = vec2_add(a, b);
}
