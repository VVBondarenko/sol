# Sol's Makefile #

# C Compiler Settings #

CC=clang
CFLAGS=-Weverything -O3 -ffast-math
LDFLAGS=-lm

# Nim Compiler Settings #

NIMC=nim
NIMLANG=c
NIMFLAGS=

# Build Options #

default: build

build:
	-@$(CC) -c $(CFLAGS) *.h src/*.c $(LDFLAGS)

bench:
	-@$(NIMC) $(NIMLANG) $(NIMFLAGS) bench.nim

disas:
	-@$(CC) $(CFLAGS) -S -masm=intel *.h src/*.c $(LDFLAGS)

clean:
	-@rm -rf *.s *.o src/*.o *.out src/*.out *.exe src/*.exe sol bench unit nimcache >/dev/null || true

reset: clean
	-@rm -rf *.gch *.a *.so *.dylib *.dll
