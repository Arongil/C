#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_prime(int n) {
    if(n % 2 == 0) {
        // Even? Bail.
        return false;
    }

    // Check the odds up to n / 2.
    // Yes, the square root would be smarter, but we haven't
    // talked about compiling in the math library yet :-p
    for(int divisor = 3; divisor < n / 2; divisor += 2) {
        if(n % divisor == 0) {
            // Found a divisor!
            return false;
        }
    }

    // If we got here without hitting that return,
    // we exhausted all options & it must be prime.
    return true;
}

int main(int argc, char *argv[]) {
    // Convert the second argument to an int.
    // (The first argument is always the name of our program)
    if (argc == 1) {
        puts("Please enter an argument.");
        return 1; // the program failed
    }
    int n = atoi(argv[1]);
    if(is_prime(n)) {
        puts("prime");
    }
    else {
        puts("composite");
    }

    return 0;
}
