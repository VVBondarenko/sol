# Sol's Makefile #

# C Compiler Settings #

CC=clang
CFLAGS=-Weverything -O3 -ffast-math
LDFLAGS=-lm

# Nim Compiler Settings #

NIMC=nim
NIMFLAG=

# Build Options #

default: build

build:
	-@$(CC) -c $(CFLAGS) *.h src/*.c $(LDFLAGS)

test:
	-@$(CC) $(CFLAGS) sol_test.c *.h src/*.c $(LDFLAGS)

disas:
	-@$(CC) $(CFLAGS) -S -masm=intel *.h src/*.c $(LDFLAGS)

clean:
	-@rm -rf *.s *.o src/*.o *.out src/*.out *.exe src/*.exe nimcache >/dev/null || true

reset: clean
	-@rm -rf *.gch *.a *.so *.dylib *.dll
