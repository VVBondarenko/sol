# C Compiler Settings
CC=gcc
CFLAGS=
LDFLAGS=-lm

# Nim Compiler Settings
NIMC=nim
NIMFLAGS=
NIMARGS=

# Terra Compiler Settings
TERRAC=terra
TERRAFLAGS=

# Source Files
SOL_MODSRC=sol_sph2.c sol_sph3.c sol_box2.c sol_box3.c sol_mod2.c sol_mod3.c
SOL_VECSRC=sol_vec2.c sol_vec3.c sol_vec4.c sol_lin2.c sol_lin3.c sol_ray2.c sol_ray3.c sol_seg2.c sol_seg3.c
SOL_FLTSRC=sol_float.c sol_conv.c

CSOURCE=sol.h $(SOL_MODSRC) $(SOL_VECSRC) $(SOL_FLTSRC)
NIMSOURCE=sol.nim
TERRASOURCE=sol.t

# Build Options
all: build

build: statlib dylib

statlib:
	-@printf "[sol] Making static library..."
	-@$(CC) $(CFLAGS) -c $(CSOURCE) $(LDFLAGS)
	-@ar rc libsol-a.a *.o
	-@rm -rf *.o *.gch *.out *~
	-@printf "done.\n"

dylib:
	-@printf "[sol] Making dynamic library..."
	-@$(CC) $(CFLAGS) -c -fPIC $(CSOURCE) $(LDFLAGS)
	-@$(CC) $(CLFAGS) -shared -fPIC -Wl,-soname,libsol-so.so -o libsol-so.so *.o $(LDFLAGS) -lc
	-@rm -rf *.o *.gch *.out *~
	-@printf "done.\n"

install: build
	-@printf "[sol] Adding libsol-a.a to /usr/local/lib..."
	-@sudo cp -r libsol-a.a /usr/local/lib
	-@printf "done.\n"
	-@printf "[sol] Adding libsol-so.so to /usr/local/lib..."
	-@sudo cp -r libsol-so.so /usr/local/lib
	-@printf "done.\n"
	-@printf "[sol] Exporting libsol-a.a and libsol-so.so..."
	-@export LD_LIBRARY_PATH=/usr/local/lib
	-@printf "done.\n"
	-@printf "[sol] Installing /sol/ to /usr/local/include..."
	-@sudo cp -r . /usr/local/include/sol
	-@printf "done.\n"

uninstall:
	-@printf "[sol] Uninstalling /usr/local/lib/sol.a..."
	-@sudo rm -rf /usr/local/lib/libsol-a.a
	-@printf "done.\n"
	-@printf "[sol] Uninstalling /usr/local/lib/sol-so.so..."
	-@sudo rm -rf /usr/local/lib/libsol-so.so
	-@printf "done.\n"
	-@printf "[sol] Uninstalling /usr/local/include/sol..."
	-@sudo rm -rf /usr/local/include/sol
	-@printf "done.\n"

clean:
	-@printf "[sol] Removing .o, .gch, .out, and ~ files..."
	-@rm -rf *.o *.gch *.out *~ >/dev/null 2>/dev/null
	-@printf "done.\n"

reset: clean
	-@printf "[sol] Removing .a, .so, and .dylib files..."
	-@rm -rf *.a *.so *.dylib
	-@printf "done.\n"
