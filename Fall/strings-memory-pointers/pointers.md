# Pointers, a gentle introduction

Secretly, all higher-level languages hide something: at the CPU level, functions can only accept integer and floating point parameters.

When you pass an object or string into a function, you're _really_ passing in the *memory addresses*. These addresses fit in integers.

That's why integers are immutable. They are primitives! When you pass an array into a function, really you're giving the function a pointer to where the array is stored in memory. Then the function can manipulate the actual array.

```
def f(x):
    x = 2
y = 3
f(y)
print(y) # outputs 3

def g(arr):
    arr.append(10)
a = [1, 2, 3]
f(a)
print(a) # prints [1, 2, 3, 10]
```

High level languages try to hide the difference between primitives and reference types. C makes it front and center!

First, how to declare a variable to hold a pointer? We need to store not just "a pointer," but "a pointer to a value of some type." A pointer is written `type *name;`.

```
int *p;
int* p;
// Both syntax options are valid, but Tim prefers the first one!!
```

Remember, a variable of type `int *` is *not an integer*. How to make it point to something?

Use the `&` operator. It returns the address of a variable. Example:

```
// This will print the location of x in memory. Remember, & for *A*mpersand for *A* for address.
int x = 5;
printf("%p", &x);

// Thus, to make a pointer:
int n = 5;
int *p = &p; // set p to point to n

// How to use pointers? How to dereference, i.e. fetch the thing it's pointing to. The operator that does that is *.
int o = *p;
printf("%i", o); // prints 5

// * and & are opposites.
// & gets address of variable
// * gets value of address
```

*Deferencing assignment*: we can also change the value at the other end of a pointer.

```
int n = 5;
int *p = &n;
*p = 10; // now n is 10
int *q = p; // now pointer p points to &n, too
```

To point to pointers, use:

```
int n = 5;
int *p = &n;
int **q = *p;
```

Use cases! One big one is arrays. Another is returning more than one value from a function.

## Case study: out parameters

We can pass arguments by _value_ or by _reference_. Passing primitives passes by value because the function receives a value only. Reassinging it just overwrites the copy. Passing more complex objects like arrays gives the function a reference, i.e. a pointer to where the array lives in memory.

Pass by reference to allow functions to mutate parameters.

```
void change_arg(int *x) {
    *x = 5;
    printf("in function: %i\n", *x);
}

int main(int argc, char *argv[]) {
    int n = 10;
    change_arg(&n);

    printf("in main: %d\n", n);

    // This program will print 5 twice.
    return 0;
}
```

Common application: return multiple values from a function.

```
#include <stdio.h>

void divmod(int a, int b, int *quotient, int *modulus) {
    *quotient = a / b;
    *modulus = a % b;
}

void main(int argc, char *argv[]) {
    int q, r;
    divmod(17, 5, &q, &r);
    printf("(%i, %i)", q, r);
    return 0;
}
```

Thus, to return multiple things, create dummy local variables which you allow the function to modify by passing them as pointers.
