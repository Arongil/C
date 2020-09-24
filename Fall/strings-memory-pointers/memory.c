#include <stdio.h>
#include <stdbool.h>
#include <math.h>

/*
 * Memory is about magically finding storage for data.
 * In C, it's generally the caller's job to find memory.
 * If you want extra info on things, it's your job to keep it around. Arrays don't know their length. If you want that, store it.
 *
 */

/*
 * Arrays: must specify type; fixed size at creation.
 * Syntax: int arr[] = ... NOT int[] arr = ...
 * Ex: char *argv[] is an array of "char stars," i.e. pointers.
 */

int main(int argc, char *argv[]) {
    int nums[] = {2, 4, 6, 8};
    printf("%i\n", nums[1]);
    nums[1] *= 2;
    printf("%i\n", nums[1]);

    int primes[50]; // inits array of length 50
    // size_t is an alias for the type that holds whatever number best represents the index of the array, so it changes by computer architecture to hold up to the largest possible array index.
    // not a big deal to use int instead
    //for (size_t i = 0; i < 50; i++) {
    //    printf("%i\n", primes[i]);
    //}
    
    // Uninitialized local variables in C have a potentially garbage value. We can't assume `int primes[50]` will have zero as its entries.

    /*
     *
    int a[] = {1, 2, 3}; // 3 elements: [1,2,3]
    int a[3] = {1, 2, 3}; // same
    
    int a[20]; // POTENTIAL GARBAGE
    int a[20] = {1, 2}; // [1, 2, 0, 0, ...]
    int a[20] = {0}; // all zeros

    int a[]; // invalid 
     *
     */

    int a[20] = {1, 2}; // [1, 2, 0, 0, ...]
    for (size_t i = 0; i < 20; i++) {
        printf("%i\n", a[i]);
    }

    // When printing arrays, remember you need the contents and the length both stored, because C doesn't know the length offhand.

    /*
     * Array caveats:
     * Arrays exist on the _stack_ not the _heap_ so far.
     * You _cannot return arrays made this way from functions._
     * You would need to make the arrays differently, with the heap.
     */

    return 0;
}
