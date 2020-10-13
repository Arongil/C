#include <stdio.h>

void divmod(int a, int b, int *quotient, int *modulus) {
    *quotient = a / b;
    *modulus = a % b;
}

int main(int argc, char *argv[]) {
    int a = 17, b = 5, q, r;
    divmod(a, b, &q, &r);
    printf("%i = %i * %i + %i", a, q, b, r);

    return 0;
}
