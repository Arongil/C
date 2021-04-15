#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <stdint.h>

int digits(const mpz_t n) {
    size_t sz = mpz_sizeinbase(n, 10) + 1;
    char *buffer = malloc(sz + 1);

    if (buffer != NULL) {
        gmp_sprintf(buffer, "%Zd", n);
        sz = strlen(buffer);
        free(buffer);
    }

    return sz;
}

void find_fib_with_digits(int n) {
    mpz_t other;
    mpz_t temp;
    mpz_t res;
    mpz_init(other);
    mpz_init(temp);
    mpz_init(res);
    mpz_set_ui(other, 1);
    mpz_set_ui(temp, 1);
    mpz_set_ui(res, 1);

    int i = 3;
    while (1) {
        mpz_set(temp, res);
        mpz_add(res, other, res); // res = other + res
        mpz_set(other, temp); // other = old_res
        if (mpz_sizeinbase(res, 10) >= n) {
            // possibly mpz_sizeinbase will be 1 too big
            int d = digits(res);
            if (d == -1) {
                fprintf(stderr, "Error in digits function!");
            }
            if (d == n) {
                break;
            }
        }
        i++;
    }

    mpz_clear(temp);
    mpz_clear(other);

    printf("The %ith Fibonacci number is the first with 1000 digits:\n\n", i);
    gmp_printf("%Zd", res);

    mpz_clear(res);
}

int main(int argc, char* argv[]) {
    find_fib_with_digits(1000);

    return 0;
}
