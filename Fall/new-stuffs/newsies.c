#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    // The ternary operator! An in-line if statement.
    // condition ? true_value : false_value
    int d = 9;
    printf("d is %s\n", d % 2 == 0 ? "even" : "odd");

    // Switch statements! We need the breaks to stop fall through.
    // Otherwise it will execute all cases after first valid case.
    switch (d) {
        case 2:
            puts("2");
            break;
        case 3:
            puts("3");
            break;
        case 9:
            puts("Ha, tricked you!");
            break;
        default:
            puts("Tricked you even more! :! :)");
    }

    // Do while! A fibbing example:
    int a = 0;
    int b = 1;
    do {
        printf("%i\n", b);

        int z = a + b;
        a = b;
        b = z;
    } while (b < 999);

    return 0;
}
