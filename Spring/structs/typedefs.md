# Type Defs

A *typedef* is a way to create an alias of an type. Use it outside of functions.

```
#include <stdio.h>

// makes the second position into an alias for the first position
typedef old_type new_type;
typedef int my_int;

int main(int argc, char *argv[]) {
    my_int x = argc;

    return 0;
}
```

The code above compiles because, under the hood, C views `my_int` as equivalent to `int`. In CS50 at Harvard, they made a library to make C easier for intro students. One of the first lines of their library is `typedef char* string;`. Then you can write:

```
int main(int argc, string argv[]) {
    string hello = "hello";
    return 0;
}
```
