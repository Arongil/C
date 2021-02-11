# Motivation

Often, an algorithm has lots of static machinery and one little component that needs to change. For example, when sorting one might prefer to compare `x > y` or `x < y`. If elements are structs, we might even need to compare `x.level > y.level`, which a sorting algorithm otherwise couldn't know.

## Potential solution: Python

The modern sort function in Python is `sorted`, which takes an optional `key` argument. If provided, `key` specifies a function which maps an object to a sortable quantity. For example:

```
class Player:

   def __init__(self, name="", level=100):
        self.name = name
        self.level = level

def f(player):
    return player.level

players = [Player("Bob", 5), Player("Jill", 2), Player("Tim", 4)]

print(sorted(players, key=f))
```

## Potential solution (JavaScript)

In JavaScript, the optional function takes a `compare(a, b)` function which returns:

* `-1` if `a < b`
* `1` if `a > b`
* `0` if `a == b`

Sometimes, this strategy of passing functions themselves around as values is called *higher order programming*. The best example is, of course, functional programming itself!


# Back to function pointers

We do the same in C, except we need to specify the type of the function. For a simple example, say we want a function `repeat(f, n)` function that takes a function `f` and calls it `n` times.

```
void repeat(some_type f, size_t n) {
    for (size_t i = 0; i < n; i++) {
        // call f
    }
}
```

The website [goshdarnfunctionpointers.com](https://goshdarnfunctionpointers.com) is your savior!

In short: the type of a function pointers includes the type of its return value and the type of all its arguments. Here's how it works:

```
return_type (*function_name)(types_of_function_parameters)
```

So, for the `repeat` function:

```
// Only takes void functions with no parameters
void repeat(void (*f)(), size_t n) {
    for (size_t i = 0; i < n; i++) {
        f();
    }
}

void say_hello() {
    printf("hi!");
}

int main(int argc, char *argv[]) {
    repeat(say_hello, 5);

    return 0;
}
```

Note: the `repeat` function as defined accepts only `void (*f)()` type function pointers, i.e. functions that take no parameters and return nothing.

Question: why don't we need to pass `&say_hello`? Well, it turns out C already interprets functions as pointers. You could say `&say_hello`, but you don't need to. Similarly, the dereference has no effect. So you could technically write `repeats(*&&***&say_hello, 5)`. Nothing would change!

## Example: QSORT

One example of a sorting function in C is `qsort`:

```
void qsort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *));
```

The void pointers ensure that `qsort` can accept any array type to sort. In addition to the length of the array (`nel` is "number of elements"), we need to pass the `width` of an element. The width is the size of an element in bytes, i.e. `4` for int.

Our job is to write a `compar(const void *a, const void *b)` function that returns:
* `-1` if `a < b`
* `1` if `a > b`
* `0` if `a == b`

Let's write a comparison function.

```
int compare(const void *a_ptr, const void *b_ptr) {
    const double *a = a_ptr;
    const double *b = b_ptr;
    return *a - *b;
}

int main(int argc, char *argv[]) {
    double a[] = {4, 2, 6.5, 3, 4, -5, 22.1, 3.14};
    qsort(a, 8, sizeof(double), compare);

    return 0;
}
```
