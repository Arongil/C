**Question**: How to use multiple C files?

One solution is forward declarations, which inform the compiler that a certain function exists. Then a joint compile statement can combine the two files.

```
void a(int); // forward declaration

void b() {
    a(5);
}

void a(int x) {
    printf("%i", x);
}
```

We can use forward declarations across files as well, but there is still an error if we only compile one file. The error comes from the *linker*. This is the final stage of turning code into an executable. The linker makes sure everything that the compiler assumed was in the code actually is.

The four steps are:
1. Preprocess
2. Compile
3. Assemble
4. Link

We need to compile the two files together to satisfy the linker. The command becomes:

```
clang -std=gnu11 -Wall main.c utils.c -o main
```

At linking time, the compiler will know all the files to look at. The order of the files in the command usually does not matter.

**Question**: Can't we just include a C file at the top?

*WARNING: Never include C files!*

While it may occasionally work, there are various nasty errors structs and other bits of C code can cause.

**Question**: What are header files?

Header files are a place to shove lots of forward declarations together. For a library with lots of functions, a header file can make importing all the forward declarations a single line. Even `stdio.h` is just a lot of forward declarations. The standard library functions all get automatically linked to your program at the end.

For example, we can write `#include "utils.h"` if we create a header file called `utils.h` with all the forward declarations for a library we've written called `utils.c`. We just need to remember to include `utils.c` in the compile command.

**Fun Fact**: the `.h` in `stdio.h` and other include statements stands for `.header`.

*WARNING: include guards!*

Say a file `main.c` needs functions from `utils.h` and `my_strings.h`, but `my_strings.h` also includes `utils.h`. We'll get a two copies of `utils.c`. While it is sometimes not a problem, we should deal with the double inclusion.

Solution: allow the file to be included as many times as we want, but only the first time will any new text get included.

```
#ifndef _UTILS_H_GUARD
#define _UTILS_H_GUARD

// blah blah blah
// all header code goes here, even other includes

void something_useful();
void something_else(int, int, double);

#endif // end include guard
```

Get in the habit of creating an include guard for every header file you write.

**Fun Fact**: Use quotes for header files that are from your project, angle brackets for system header files. That's why we write `#include <stdio.h>` and `#include "utils.c"`.

Use relative paths rather than absolute paths for headers, because you don't know where the file will live if, for example, someone clones your git repository.
