# C Compiler Settings
CC=gcc
CFLAGS=-std=c11 -fPIC
LDFLAGS=-lm

# Nim Compiler Settings
NIMC=nim
NIMFLAGS=
NIMARGS=

# Source Files
SOL_MODSRC=sol_sph2.c sol_sph3.c sol_box2.c sol_box3.c sol_mod2.c sol_mod3.c
SOL_VECSRC=sol_vec2.c sol_vec3.c sol_vec4.c sol_lin2.c sol_lin3.c sol_ray2.c sol_ray3.c sol_seg2.c sol_seg3.c
SOL_FLTSRC=sol_float.c sol_conv.c

CSOURCE=sol.h $(SOL_MODSRC) $(SOL_VECSRC) $(SOL_FLTSRC)
NIMSOURCE=sol.nim

# Build Options

all: script

script:
	-@$(CC) -o build build.c
	-@./build
	-@rm -rf build || true

clean:
	-@rm -rf build *.o *.exe *.out *.gch >/dev/null

reset: clean
	-@rm -rf *.a *.so *.dylib *.dll >/dev/null
