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

# ARCH: default, native, armv8, armv7
ARCH=default
# BITS: default, 64, 32
BITS=default
# SIMD: default, auto, omp, avx2, avx, neon, disabled
SIMD=default
# OPT: g, 0, 1, s, 2, 3
OPT=2

# Build Variables #

# ARCH -> CARCH
ifeq ($(ARCH), default)
	CARCH=
endif
ifeq ($(ARCH), native)
	CARCH=-march=native
endif
ifeq ($(ARCH), armv8)
	CARCH=-march=arvm8-a
endif
ifeq ($(ARCH), armv7)
	CARCH=-march=armv7-a
endif

# BITS -> CBITS

ifeq ($(BITS), default)
	CBITS=
endif
ifeq ($(BITS), 64)
	CBITS=-m64
endif
ifeq ($(BITS), 32)
	CBITS=-m32
endif

# SIMD -> CSIMD

ifeq ($(SIMD), default)
	CSIMD=
endif
ifeq ($(SIMD), auto)
	CSIMD=-DSOL_SIMD
endif
ifeq ($(SIMD), omp)
	CSIMD=-DSOL_OMP
endif
ifeq ($(SIMD), avx2)
	CSIMD=-DSOL_AVX -mavx2
endif
ifeq ($(SIMD), avx)
	CSIMD=-DSOL_AVX -mavx
endif
ifeq ($(SIMD), neon)
	CSIMD=-DSOL_NEON -mfloat-abi=hard -mfpu=neon
endif
ifeq ($(SIMD), disabled)
	CSIMD=-DSOL_NO_SIMD -DSOL_NO_OMP -DSOL_NO_NEON
endif

# Build Options

all: build

build:
	-@$(CC) $(CFLAGS) $(CARCH) $(CBITS) $(CSIMD) -O$(OPT) -c $(CSOURCE) $(LDFLAGS) $(ARGS)

dylib:
	-@$(CC) $(CLFAGS) -shared -fPIC -Wl,-soname,libsol-so.so -o libsol-so.so *.o $(LDFLAGS) $(ARGS) -lc

statlib:
	-@ar rc libsol-a.a *.o

install:
	-@sudo cp -r libsol-a.a /usr/local/lib >/dev/null 2>/dev/null || true
	-@sudo cp -r libsol-so.so /usr/local/lib >/dev/null 2>/dev/null || true
	-@rm -rf *.o *.exe *.out *.a *.so *.dylib *.dll >/dev/null 2>/dev/null || true
	-@sudo cp -r . /usr/local/include/sol >/dev/null 2>/dev/null || true

uninstall:
	-@sudo rm -rf /usr/local/lib/libsol-a.a >/dev/null 2>/dev/null
	-@sudo rm -rf /usr/local/lib/libsol-so.so >/dev/null 2>/dev/null
	-@sudo rm -rf /usr/local/include/sol >/dev/null 2>/dev/null

clean:
	-@rm -rf build *.o *.exe *.out *.gch >/dev/null 2>/dev/null

reset: clean
	-@rm -rf *.a *.so *.dylib *.dll >/dev/null 2>/dev/null
