#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int *resize(int *original_array, size_t original_length, size_t new_length) {
    int *new_array = malloc(sizeof(int) * new_length);
    for (size_t i = 0; i < original_length; i++) {
        *(new_array + i) = *(original_array + i);
    }
    free(original_array);
    return new_array;
}

// Takes array pointer, size of array, int to insert, and index at which to insert
// If array pointer is NULL, then we insert into a freshly malloc-ed array.
int *insert(int *array, size_t size, int insertion, size_t index) {
    assert(index >= 0 && index < size + 1);
    array = realloc(array, sizeof(int) * (size + 1));
    // bump everything to the right of the insertion index one to the right
    // Ex. for index = 3:
    // old:  1 0 0 1 0 4 5
    // bump: 1 0 0 _ 1 0 4 5
    // new:  1 0 0 3 1 0 4 5
    for (size_t i = size; i > index; i--) {
        array[i] = array[i - 1];
    }
    array[index] = insertion;
    return array;
}

int main(int argc, char *argv[]) {
    // Create an array with size 2, then add 8 slots. Set one equal to 5 so we can confirm it's larger!
    printf("Testing the resize function...\n");
    printf("Adding 8 slots to a two-slot array...\n");
    int *arr = malloc(sizeof(int) * 2);
    for (int i = 0; i < 2; i++) {
        printf("%i\n", arr[i]);
    }
    arr = resize(arr, 2, 10);
    for (int i = 2; i < 10; i++) {
        arr[i] = 10 - i;
    }
    printf("\n");
    for (int i = 0; i < 10; i++) {
        printf("%i\n", arr[i]);
    }
    free(arr);

    //// ----- ////

    printf("\nTesting the insert function...\n");
    int *ins_test = malloc(sizeof(int)*4);
    for (int i = 0; i < 4; i++) {
        ins_test[i] = i;
    }
    printf("Inserting 9 at the end of {1, 2, 3, 4}...\n");
    insert(ins_test, 4, 9, 4);
    for (int i = 0; i < 5; i++) {
        printf("%i\n", ins_test[i]);
    }

    return 0;
}
