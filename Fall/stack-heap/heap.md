## The Heap

Sometimes we want to create memory for local variables that will persist. The heap stores this memory -- although the compiler manages the stack, we manage the heap. We have to ask for heap storage and declare when we are done with it. Heap memory lives until we say we are finished. Heap memory also works well for big allocations, because it is far less limited than the stack.

The relevant functions are `malloc` and `calloc` and `free` and `realloc`.

The upside is we control memory. The downside is it's easy to forget memory, or forget to free it, which is called a _memory leak_. Over time, we pile up junk memory until we crash. When our program exits, all its memory gets freed, so memory leaks are only a problem when a program runs for a long time (i.e. an operating system or video game).

Memory allocate = malloc:

```
#include <stdlib.h>
void *malloc(size_t size)
```

What's a void pointer? Well, `malloc` needs to be able to return memory for any type, an int or double or string or anything. So a void pointer is a wildcard. It points to anything, so we can cast it to anything but we can never dereference it.

What's `size`? Recall that `size_t` is the integer large enough to represent any index of any array. The parameter `size` tells C how many bytes to allocate.

How to find how many bytes we need? There's the _operator_ `sizeof`. We write it a little weirdly, as if it were a function, but it can do more than a function.

```
sizeof(int);
sizeof(double);
sizeof(long int);

double pi = 3.14159;
sizeof(pi);
```

Use `sizeof` to pass an argument to `malloc`. C automatically lets us cast type `void *` to type `int *`.

```
// cast void pointer to int pointer
int *p = malloc(sizeof(int));
// deferencing assignment to put 10 in memory
*p = 10;
```

How to _release_ memory: `void free(void *ptr)`. Feed `free` the pointer `malloc` returns, and it will free the memory as good to go again! It will not zero out the memory or zero out the pointer. It's okay to pass `free` any kind of pointer as well, not just a void pointer.

*ALWAYS* use `malloc` and `free` as a pair:

```
int *p = malloc(sizeof(int));
*p = 10;

printf("%i", *p);

free(p);
```

Danger zones:
* Once we free memory, the next time `malloc` looks for space, it will probably allocate memory in the same old place. So `malloc(sizeof(int))` then `free` then `malloc(sizeof(int))` might reassign the first malloc by the second malloc.
* _Dangling pointers_: `int *p1 = malloc(sizeof(int)` then `*p1 = 5` then `free(p1)` then `*p1 = 10`. We call the `p1` a dangling pointer at the end, because it's assigned to freed memory.

Null pointers point to 0, which in modern memory doesn't correspond to anywhere. Set `int *p = NULL` if we just want to instantiate a dummy pointer for now.

Note: `free` is only for memory on the heap. Calling `free` on variables that live in the stack crashes!
