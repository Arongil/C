#include <stdio.h>

int *bad_idea() {
    int x = 5;
    return &x;
}

int main(int argc, char *argv[]) {
    int *p = bad_idea();
    printf("five?? %i\n", *p);
    printf("five?? %i\n", *p);

    return 0;
}
