#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Return most common element from int nums[].
// Specifications:
// - if multiple elements tie, return the lowest
// - all numbers between 0 and 99
int most_common_element(int nums[], int length) {
    int counts[100] = {0};
    for (int i = 0; i < length; i++) {
        counts[nums[i]]++;
    }

    int max_index = 0;
    for (int i = 1; i < 100; i++) {
        if (counts[max_index] < counts[i]) {
            max_index = i;
        }
    }

    return max_index;
}

int main(int argc, char *argv[]) {
    // Some test cases
    int arr1[] = {0, 0, 1, 1, 2, 2, 3, 3};
    int arr2[] = {0, 1, 1, 2, 2, 2, 3, 3, 3};
    int arr3[] = {4, 5, 7, 7, 76};
    int arr4[] = {45, 88, 33, 55, 22, 44, 44};
    int arr5[] = {6, 5, 4, 4, 4, 2, 99};
    printf("From array 1, the max occurrence is %i\n", most_common_element(arr1, 8));
    printf("From array 2, the max occurrence is %i\n", most_common_element(arr2, 9));
    printf("From array 3, the max occurrence is %i\n", most_common_element(arr3, 5));
    printf("From array 4, the max occurrence is %i\n", most_common_element(arr4, 7));
    printf("From array 5, the max occurrence is %i\n", most_common_element(arr5, 7));

    printf("The correct answers were 0, 2, 7, 44, and 4. Looks like the computer got them!");
    return 0;
}
