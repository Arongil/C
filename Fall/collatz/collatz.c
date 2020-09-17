#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int stopping_time(int n) {
    int count = 0;
    while (n > 1) {
        count++;
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3*n + 1;
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        puts("Please enter a number! The program will output the largest stopping time for numbers less than what you input in the Collatz Conjecture.");
        return 1;
    }

    int bound = atoi(argv[1]);

    int largest = 0;
    int n;
    int s;
    for (int i = 1; i < bound; i++) {
        s = stopping_time(i);
        if (s > largest) {
            largest = s;
            n = i;
        }
    }

    printf("The number < %i with the largest stopping time is %i, with a stopping time of %i", bound, n, largest);

    return 0;
}
