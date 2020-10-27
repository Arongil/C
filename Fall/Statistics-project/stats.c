#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const char *suffix(int n) {
    if (n % 100 == 11 || n % 100 == 12 || n % 100 == 13) {
        return "th";
    } else if (n % 10 == 1) {
        return "st";
    } else if (n % 10 == 2) {
        return "nd";
    } else if (n % 10 == 3) {
        return "rd";
    } else {
        return "th";
    }
}

double *read_array(int *count) {
    printf("How many numbers would you like to enter?\n>");
    scanf("%i", count);
    double *array = malloc(*count * sizeof(int));
    for (int i = 0; i < *count; i++) {
        printf("Please enter the %i%s number>", i + 1, suffix(i + 1));
        if (scanf("%lf", &array[i]) != 1) {
            fprintf(stderr, "*** Invalid Entry -- EXITING \n");
            return NULL;
        }
    }
    return array;
}

double get_sum(const double *nums, size_t length) {
    double sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += nums[i];
    }
    return sum;
}
double get_avg(const double *nums, size_t length) {
    double sum = get_sum(nums, length);
    return sum / (int)length;
}
double get_stdev(const double *nums, size_t length) {
    double average = get_avg(nums, length);
    double stdev = 0, term;
    for (size_t i = 0; i < length; i++) {
        term = (nums[i] - average);
        stdev += term*term;
    }
    stdev = sqrt(stdev / length);
    return stdev;
}

int main(int argc, char *argv[]) {
    printf("Welcome to the STATISTICS SUITE!\n");
    int count;
    double *nums = read_array(&count);
    if (nums == NULL) {
        return 1;
    }
    double sum = get_sum(nums, count);
    double avg = get_avg(nums, count);
    double stdev = get_stdev(nums, count);
    printf("\nSum: %lf\nAverage: %lf\nStandard Deviation: %lf\n", sum, avg, stdev);
    
    free(nums);
    return 0;
}
