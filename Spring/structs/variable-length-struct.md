Fixed size arrays are no problem on the stack or the heap, but variable size arrays are tricky. You might think to just use a pointer.

```
typedef struct {
    size_t len;
    int *elems;
} list;
```

Technically the above works, but we'd need to create a separate allocation for the array's memory. We'd ned two mallocs.

```
list *l = malloc(sizeof(list));
l->len = 4;

l->elems = calloc(4, sizeof(int));
l->elems[1]] = 8;

free(l->elems);
free(l);
```

The sometimes better option is called *flexible array members*. The idea is to just slap an array at the end of the struct in memory! Unfortunately we can only hold one array per struct here; it must come last in the struct.

```
typdef struct {
    size_t len;
    int elems[];
} list;
```

If you ask for `sizeof(list)`, it will return just `sizeof(len)`! The size of the struct ignores the size of the flexible array.

Repercussion: we need to allocate memory for these dynamic structs ourselves. We'd need to say:

```
// Create ten slots of memory for the int array.
list *l10 = malloc(sizeof(list) + 10 * sizeof(int));
// Create twenty!
list *l20 = malloc(sizeof(list) + 20 * sizeof(int));
```

The type of the array elements can also be other structs.

Caveats!
1. You can't put flexible size structs into an array, because C expects all elements of an array ot have the same size.
2. You must use flexible arrays on the heap, because C can never know the ultimate size of the struct. You can't even dereference on to the stack.
3. You can't return them by value from a function. (Use a pointer!)
4. You can't take them as arguments by value to a function. (Use a pointer!)
