## The Stack

We know ampersand returns the address of a variable. So far getting that space has been automatic. Space just exists for `int x;`.

What happens when we call a function? For example, a recursive factorial function. When calling `factorial(3)`, we get `3 * factorial(2)`. So we have to put `factorial(3)` on hold until we finish other processes. We need to store the state it was in. All local variables need to stay around.

We end up building a stack. A _stack_ is a chunk of memory that the compiler automatically manages for us. It's the same as in a Pushdown Automaton: we can add to the top but not so much from the bottom. When we call a function, we push a _stack frame_ on to the stack. When a function returns, it pops its stack frame. That means, upon return, the stack frame flags old local variables as _okay to reuse_! Those local variables are not safe once the function returns.

```
int *bad_idea() {
    int x = 5;
    return &x;
}
```

As long as `bad_idea` is running, the address to `x` is fine and dandy to use. As soon as we return `&x`, the computer is free to write whatever it wants over the address. Many times, this results in garbage values in memory addresses.


## Stack Overflow

The stack has a finite amount of memory. If we use too much, it's called a _stack overflow error_.

```
void overflow(int x) {
    overflow(x + 1);
}

int main(int argc, char *argv) {
    overflow(0);
    return 0;
}
```

On modern operating systems, each program gets a specified chunk of memory. That's why individual programs can't take down the whole machine (unless the program asks for more memory!!).
