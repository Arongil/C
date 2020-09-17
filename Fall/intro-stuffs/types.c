#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    // Philosophy: C has lots of datatypes and variations, because C was invented when we cared about the size of our data. When we have hundreds of thousands of variables, these little optimizations can add up.
    /*
     * char = 8 bit min size --> for characters and tiny numbers
     * short = 16 bit min size --> medium-size numbers (uncommon)
     * int = 16 bit min (usually 32) --> standard integer type
     * long = 32 bit min (usually 64) --> bigger numbers
     * long long = 64 bits --> bigger bigger numbers
     */
    // unsigned makes an int always positive, i.e. char is between -32767 and 32767, but unsigned char is between 0 and 65536.
    short c = -32767;
    unsigned short woah = 65535;
    /*
     * The floating point family!
     * float "single precision" usually 32 bits (not that precise)
     * double "double precision" usually 64 bits (standard floating point)
     * long double "extended precision" usually 128 bits (uncommon)
     */
    // There's no unsigned floating point!
    float floater = 9.2301;
    double real_floater = 3.22392132823238239;
    double dat_sum = floater + real_floater;
    // float + double = double ; int + char = int
    // BUT dividing two ints gives an int...
    if (3 / 2 == 1) {
        puts("We got here. Why???");
    }
    // casting:
    if (3 / 2.0 == 1 || 3 / (double)2 == 1) {
        puts("Now that's a lot better. You'll never see this!");
    }
    // Rules of thumb: don't worry about numeric types too much. Usually int and double are fine. Sometimes unsigned in semantically nice.
    // On booleans: until 1999, booleans were just char and ints that were 0 = false, 1 = true. C interprets 0 as false and anything else as true.
    if (1) {
        puts("YO. 1 = true");
    }
    // Now it lives in stdbool.h.
    // Always include stdio and stdbool.
    // The type is called bool. Constants are true and false.
    bool b = true;
    bool b2 = false;
    if (b) {
        puts("s");
    }
    // Bitwise: | OR, & AND, ^ XOR, ~ NOT

    // How to freaking print stuff!
    // printf and friends are the typical print
    /*
     * printf returns something no one chars about
     * arguments are const char *format (char star means string)
     * ... parameter means it can take as many arguments of any type as you want.
     * Thus printf can print as much stuff as you want.
     * printf uses the first argument (format string) to interpret the remaining arguments.
     */
    printf("pi = %f\n", 3.14159);
    // Format specifiers begin with a % and are followed by a sequence of characters that define the type that is expected.
    // We need exactly one format specifier for each extra argument.
    printf("We can also print strings with no extra arguments.\n");
    printf("You'd never believe it!\n");
    /*
     * char = %c
     * int = %i (or %d)
     * long long = %lli (like "long long int")
     * float = %f
     * double = %lf (like "long float")
     * string (char *) = %s
     */
    printf("\n");
    printf("These are the arguments you passed into types.\n");
    for (int i = 0; i < argc; i++) {
        printf("argv[%i] = %s\n", i, argv[i]);
    }

    // Tweaking outputs, i.e. print just a few decimals of a float.
    double pi = 3.14159265358979323646897;
    printf("%.4f\n", pi); // modifiers go between % and f. Ex: %.2f
    // ^^^ it rounds!

    return 0;
}
