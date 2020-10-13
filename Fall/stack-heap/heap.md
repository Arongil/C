## The Heap

Sometimes we want to create memory for local variables that will persist. The heap stores this memory -- although the compiler manages the stack, we manage the heap. We have to ask for heap storage and declare when we are done with it. Heap memory lives until we say we are finished. Heap memory also works well for big allocations, because it is far less limited than the stack.

The relevant functions are `malloc` and `calloc` and `free` and `realloc`.
