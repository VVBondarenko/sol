  //////////////////////////////////////////////
 // sol_build.c | Sol's custom build script. //
//////////////////////////////////////////////

#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

char OUTPUT[BUFSIZ];
char INPUT[BUFSIZ];
char ARCH[4] = " ";
char SIMD[20] = " ";
char CC[10] = " ";
char OS[20] = " ";
char OPT[4] = " ";
char BIT;

static inline
void getarch() {
  printf("[sol/build.c] Select Arch: [x]86 / [A]RM: ");
  fgets(INPUT, BUFSIZ, stdin);
  ARCH[0] = tolower(INPUT[0]);
  if (!(ARCH[0] == 'x' || ARCH[0] == 'a')) {
    printf("[sol/build.c] Invalid Arch selection.\n");
    getarch();
  }
}

static inline
void getos() {
  printf("[sol/build.c] Select OS: *[N]ix / [W]indows: ");
  fgets(INPUT, BUFSIZ, stdin);
  OS[0] = tolower(INPUT[0]);
  if (!(OS[0] == 'n' || OS[0] == 'm' || OS[0] == 'w')) {
    printf("[sol/build.c] Invalid OS selection.\n");
    getos();
  }
}

static inline
void getcc() {
  printf("[sol/build.c] Select CC: [G]CC / [C]lang: ");
  fgets(INPUT, BUFSIZ, stdin);
  CC[0] = tolower(INPUT[0]);
  if (!(CC[0] == 'g' || CC[0] == 'c')) {
    printf("[sol/build.c] Invalid CC selection.\n");
    getcc();
  }
}

static inline
void getbit() {
  printf("[sol/build.c] Select Size: [64] Bit / [32] Bit: ");
  fgets(INPUT, BUFSIZ, stdin);
  BIT = atoi(INPUT);
  BIT = (BIT > 32) ? 64 : 32;
}

static inline
void getopt() {
  printf("[sol/build.c] Select Opt: [F]ast / [B]alanced / [S]mall: ");
  fgets(INPUT, BUFSIZ, stdin);
  OPT[0] = tolower(INPUT[0]);
  if (!(OPT[0] == 'f' || OPT[0] == 'b' || OPT[0] == 's')) {
    printf("[sol/build.c] Invalid Opt selection.\n");
    getopt();
  }
}

static inline
void getsimd() {
  if (ARCH[0] == 'x') {
    printf("[sol/build.c] Select SIMD: [A]uto / [L]inear / [O]penMP / [A]VX: ");
    fgets(INPUT, BUFSIZ, stdin);
    SIMD[0] = tolower(INPUT[0]);
    if (!(SIMD[0] == 'l' || SIMD[0] == 'a' || SIMD[0] == 'o' || SIMD[0] == 'a')) {
      printf("[sol/build.c] Invalid SIMD selection.\n");
      getsimd();
    }
  } else if(ARCH[0] == 'a') {
    printf("[sol/build.c] Select SIMD: [A]uto / [L]inear / [O]penMP / [N]EON: ");
    fgets(INPUT, BUFSIZ, stdin);
    SIMD[0] = tolower(INPUT[0]);
    if (!(SIMD[0] == 'l' || SIMD[0] == 'a' || SIMD[0] == 'o' || SIMD[0] == 'n')) {
      printf("[sol/build.c] Invalid SIMD selection.\n");
      getsimd();
    }
  } else {
    printf("[sol/build.c] Error: Arch must be determined before SIMD.\n");
    exit(EXIT_FAILURE);
  }
}

static inline
void translate() {
  // Compiler Translation
  if (CC[0] == 'g') {
    if (OS[0] == 'w') {
      printf("[sol/build.c] GCC targeting windows requires mingw-gcc. Continue? [Y]es / [N]o: ");
      fgets(INPUT, BUFSIZ, stdin);
      if (tolower(INPUT[0]) == 'y') {
        strcpy(CC, "mingw-gcc");
   } else {
        printf("[sol/build.c] Exited: User-indicated lack of mingw-gcc.\n");
        exit(EXIT_FAILURE);
      }
    } else {
      strcpy(CC, "gcc");
    }
  } else {
    strcpy(CC, "clang");
  }
  // Optimization Translation
  if (OPT[0] == 'f') {
    strcpy(OPT, "-O3");
  } else if(OPT[0] == 'b') {
    strcpy(OPT, "-O2");
  } else if(OPT[0] == 's') {
    strcpy(OPT, "-Os");
  } else {
    printf("[sol/build.c] Error: Optimization must be determined before translation.\n");
  }
}

int main() {
  printf("[sol/build.c] To build Sol, please provide target info:\n");
  // Gather target info:
  getos();
  getcc();
  getarch();
  getsimd();
  getbit();
  getopt();
  // Translate it into a usable format:
  translate();
  printf("%s %s %s %s %hhu %s\n", OS, CC, ARCH, SIMD, BIT, OPT);
  return 0;
}
