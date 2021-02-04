# Linked lists!

Let's review big O notation for the start.

*Definition* Say a Turing machine runs in time O(f(n)) if there exists some number k such that the Turing machine always halts in time at most k*f(n).

We say O(n) is *linear time*. The number k limits us to asymptotic considerations.

- Finding a value of an array at an index is O(1).
- Inserting a value into an array at an index is O(n).
- Deleting an element in an array is O(n).

*Linked lists flip this paradigm*. Finding a value is O(n), but inserting and deleting is O(1). This is useful when we don't care about the order of objects, but we need to frequently add and remove elements. For example, all the objects in the world of a video game. We need to add bullets, remove occluded trees, etc. We never care about the "fifth" object in the world. Linked lists would be a good architecture here.

# Structure of linked lists

Each element is a node. Each node has a value and next pointer.

(12, X) --> (99, X) --> (37, X) --> (23, NULL)

The data structure is a chain of paired values and pointers. We call the first node the *head*. The linked list itself is a pointer to the head.

Indexing and search are now O(n), but insertion is O(1). To insert 23 to

(A, X) --> (B, X) --> (C, X) --> ...,

we edit to

(A, X) --> (23, X) --> (B, X) --> (C, X) --> ....

Deletions similarly take O(1) time.

We need to use the original struct notation so we can recursively reference the type within the struct. Then we can typedef it into a single `node` type.

```
struct node {
    int value;
    struct node *next;
};

typedef struct node node;
```

Alternatively, we can smash all the typedefs into one:

```
typedef struct node {
    int value;
    struct node *next;
} node;
```

# Doubly linked lists

Sometimes we want both a `next` and a `prev` pointer:

```
typedef struct node {
    int value;
    node *next;
    node *prev;
} node;
```

Now deletions look like this (without edge case considerations):

```
void list_remove(node loc) {
    loc->prev->next = loc->next;
    loc->next->prev = loc->prev;
}
```

To perform an indexing operation:

```
node get_index(node *head, size_t index) {
    node *n = head;
    int j = 0;
    while (n != NULL) {
        if (i == j) {
            return n;
        }

        j++;
        n = n->next;
    }

    return NULL;
}
```
