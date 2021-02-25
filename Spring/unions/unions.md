# Unions

Unions are like a struct, but all members coexist in the same place in memory. For example:

```
typedef union {
    int i;
    double d;
} int_or_double;

int_or_double val;
val.i = 5;
```

We could then read back `val.i`. But if we set the double field `val.d`, then we can't read back `val.i`. Same vice versa.

The program stores the magic combination of bits and bytes that comprise our number, in whatever standard for doubles the program uses. We get nonsense if we read back the same bits and bytes under the integer standard.

## Unions in structs

Unions are often most useful when used in structs. For example:

```
typedef enum {
    shape_kind_square,
    shape_kind_rectangle,
    shape_kind_circle
} shape_kind;

typedef struct {
    int centerx;
    int centery;
    shape_kind kind;     // sometimes called a tag (and a tagged union)
    union {
        int side_length; // square
        double radius;   // circle
        struct {         // rectangle
            int width;
            int height;
        };
    };
} shape;

void shape_print(const shape *s) {
    if (s->kind == shape_kind_square) {
        // print using side_length
    }
    else if ( ... ) {
        // ...
    } else ( ... ) {
        // ...
    }
}

int main (int argc, char *argv[]) {
    shape square = {
        .centerx = 0,
        .centery = 1,
        .kind = shape_kind_square,
        .side_length = 4
    };

    return 0;
}
```

When we intentionally withhold a name from the union within a struct, we can access the value without an intermediate level. We say the value is *transparent*. We can say `square.side_length` instead of, maybe, `square.dimensions.side_length`, if we named the transparent union `dimensions`.
