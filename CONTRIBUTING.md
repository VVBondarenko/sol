# Sol Contribution Guidelines
Sol is by no means a professional project but I would still like for things to be somewhat organized and well documented.
Here are some basic rules to follow when contributing:

# Variable Naming
Same as most standard-ish C code.
```C
int local_variable;
int libname_global_variable;
int GLOBAL_VARIABLE;
#define GLOBAL_MACRO
#define libname_global_macro;

struct type_mystruct {
  // items
} MyStruct;
```

# Bracketing Style
Not backed by functionality, purely an aesthetical choice.
```C
int main() {
  // code
}
```

# Pointer Style
Pointers should be next to the name, not the type, for functional reasons as shown:
```C
int *a, *b, *c;
```
Were you to do it like:
```C
int* a, b, c;
```
Then b and c would not be pointers, which would mean you would end up with:
```C
int* a, *b, *c;
```
which looks ugly and non-uniform.

# Function Commentation Style
Makes functions easier to understand by skimming through the documentation. A single format for it makes summarizing what things
do easy. Adding a formula for the function after the "out:" field using square brackets is optional.
```C
/// add ///
// Description
//   Adds two numbers.
// Arguments
//   a: addend (int)
//   b: addend (int)
// Returns
//   out: sum (int) [out = a + b]

int add(int a, int b) {
  return a + b;
}
```

# Non-Storage Function Attributes
I think it shows intent more to have "inline", "static", etc. on a seperate line from storage specifiers
such as const and volatile.

```C
static inline
const int add(int a, int b) {
  return a + b;
}
```

# Macro Usage
Indentation and #endif labeling helps code clarity more for nested ifdefs.
```C
#ifdef THING
      #ifdef OTHER_THING
            // stuff
      #endif // OTHER_THING
#endif // THING
```
