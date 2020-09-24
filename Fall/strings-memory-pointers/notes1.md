# Compilation order

C compilers are "one pass," which means they compile in order of the code. Java sweeps through the code to get a lay of the land first. That means C can _only reference functions defined before they are called_, while Java and many other languages can call functions that are defined later on in the code.

What if we have the following?

```
int f1() {
    return f2();
}

int f2() {
    return f1();
}
```

Then we need _forward declarations_, which define the types ahead of time. The way to do this is to copy the _prototype_ of the function (its definition without the body). For example:

```
double square(double n);

int main(int argc, char *argv[]) {
    printf("%.3f", square(4.5));
    return 0;
}

double square(double n) {
    return n*n;
}
```
