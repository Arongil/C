#include <stdio.h>
#include <math.h>
int main(int argc, char *argv[]) {
    // int modf(double x, int *y) returns the float component of x and sets *y to the integer component of x.
    double x, int_part, float_part;
    x = 8.1234;
    float_part = modf(x, &int_part);
    printf("%f = %f + %f", x, int_part, float_part);
}
