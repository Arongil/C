# Structs!

## Motivation

Say we want to code an RPG. We need to keep track of many values for a character, like health or inventory. How can we store these in C?

The answer is *structs*! It's like a class, but no methods. Only instance variables. No constructor, no inheritance. Basic syntax:

```
struct point {
    double x;
    double y;
};
```

Since this defines a *type*, you typically put it outside of functions at the top of the file. That way it's visible throughout the file. Here's an example of using the `point` struct.

```
int main(int argc, char *argv[]) {
    struct point p; // p is a point on the stack

    // We can use dot syntax.
    p.x = 5;
    p.y = 10;

    printf("(%f, %f)\n", p.x, p.y);
}
```

Nowadays, there's a better way to make structs. REPEAT: MAKE STRUCTS LIKE THIS:

```
typedef struct {
    double x;
    double y;
} point;
```

Defining structs with `typedef` lets you avoid typing `struct` every time you want to declare a variable of type `point`. That is, you can write `point p;`.

We have many ways to initialize a struct. Recall that it's dangerous to define `int x;` without assigning it a value, because stack internals mean that we can't predict the value of `x` this way. Similarly for structs. It's better to assign a value to a struct upfront.

```
point p; // undefined initial values; risky

point p = { .x = 0, .y = 2 }; // explicitly set member values
point p = { .y = 2 }; // omitted members are set to 0

point p = {5, 10 }; // set members are set in order of the definition
point p = {0}; // omitted members are set to 0
```

What can we do with structs?!?

1. Struct variables can be `const`.
2. Assign one struct variable to another to overwrite member values.

```
point p = {1, 2};
point q = {3, 4};

q = p; // q is now {1, 2} and in different memory than p
```

3. Pass structs around as arguments and return them from functions. Note: struct parameters are immutable! They get copied. You can't write a function `void do_damage(player p, int damage) { p.hp -= damage; }`. To bypass this, you would need to pass the pointer to a struct, i.e. `void do_damage(player *p, int damage);`. Then you could call `do_damage(&p, 10);`. Here are two more examples of functions using structs:

```
double dist(point p1, point p2) {
    return ...;
}

point midpoint(point p1, point p2) {
    return ...;
}
```

Note: since we're copying the entire struct for each function call, deep function stacks or structs with many items can quickly exhaust stack space. Therefore, it's much more common to pass and return pointers to structs.

4. You **can't** compare structs. No ``if (point1 == point2)``. To check equality of structures, you would have to write a function for it.

5. You can *nest* structs!

```
typedef struct {
    int r;
    int g;
    int b;
} color;

typedef struct {
    color start;
    color end;
} gradient;
```

6. You can make arrays of structs like `player players[] = {};`. But the structs themselves do not act as arrays.

7. You can put an array in the struct, but be warned: it will always have a constant amount of elements. You must know how long the array should be.

```
typedef struct {
    const char *name;
    int hp;
    int exp;
    point pos;

    int stats[16];
} player;
```

8. You can nest initializers, so for example:

```
gradient g = {
    {0, 0, 255},
    {255, 0, 0}
};
```

9. You can cast in the return instead of creating a temp variable.

```
player make_player(const char *name) {
    return (player) {
        .name = name,
        .exp = 0,
        .hp = 100,
        .pos = {5, 5}
    };

    /*
    The above is the same as

    player p = {
        .name = name,
        .exp = 0,
        .hp = 100,
        .pos = {5, 5}
    };
    
    return p;

    */
}
```

That's it, folks! At the end of the day, structs are just a way to package values into one place with one name. They are really bad classes. Just a bunch of variables and that's all there is to it.
