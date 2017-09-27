# Sol's Makefile #

# C Compiler Settings #
CC=gcc
CFLAGS=-std=c11 -fPIC
LDFLAGS=-lm

# Nim Compiler Settings #
NIMC=nim
NIMFLAGS=
NIMARGS=

# Source Files #
SOL_MODSRC=sol_sph2.c sol_sph3.c sol_box2.c sol_box3.c sol_mod2.c sol_mod3.c
SOL_VECSRC=sol_vec2.c sol_vec3.c sol_vec4.c sol_lin2.c sol_lin3.c sol_ray2.c sol_ray3.c sol_seg2.c sol_seg3.c
SOL_FLTSRC=sol_float.c sol_conv.c

CSOURCE=sol.h $(SOL_MODSRC) $(SOL_VECSRC) $(SOL_FLTSRC)
NIMSOURCE=sol.nim

# Build Options #

# ARCH: generic, native, armv8, armv7
ARCH=generic
# BITS: 64, 32
BITS=64
# SIMD: auto, omp, avx, neon
SIMD=auto
# OPT: g, 0, 1, s, 2, 3
OPT=2

# Build Options

all: build

build:
ifeq ($(ARCH), generic)
	-@$(CC) $(CFLAGS) -c -m$(BITS) -O$(OPT) $(CSOURCE) $(LDFLAGS)
endif
ifeq ($(ARCH), native)
	-@$(CC) $(CFLAGS) -c -march=native -m$(BITS) -O$(OPT) $(CSOURCE) $(LDFLAGS)
endif
ifeq ($(ARCH), armv8)
	-@$(CC) $(CFLAGS) -c -march=armv8-a -m$(BITS) -O$(OPT) $(CSOURCE) $(LDFLAGS)
endif
ifeq ($(ARCH), armv7)
	-@$(CC) $(CFLAGS) -c -march=armv7-a -O$(OPT) $(CSOURCE) $(LDFLAGS)
endif

dylib:
	-@$(CC) $(CLFAGS) -shared -fPIC -Wl,-soname,libsol-so.so -o libsol-so.so *.o $(LDFLAGS) -lc

statlib:
	-@ar rc libsol-a.a *.o

install:
	-@sudo cp -r libsol-a.a /usr/local/lib >/dev/null 2>/dev/null
	-@sudo cp -r libsol-so.so /usr/local/lib >/dev/null 2>/dev/null
	-@rm -rf *.o *.exe *.out *.a *.so *.dylib *.dll >/dev/null 2>/dev/null
	-@sudo cp -r . /usr/local/include/sol >/dev/null 2>/dev/null

uninstall:
	-@sudo rm -rf /usr/local/lib/libsol-a.a >/dev/null 2>/dev/null
	-@sudo rm -rf /usr/local/lib/libsol-so.so >/dev/null 2>/dev/null
	-@sudo rm -rf /usr/local/include/sol >/dev/null 2>/dev/null

clean:
	-@rm -rf build *.o *.exe *.out *.gch >/dev/null 2>/dev/null

reset: clean
	-@rm -rf *.a *.so *.dylib *.dll >/dev/null 2>/dev/null
