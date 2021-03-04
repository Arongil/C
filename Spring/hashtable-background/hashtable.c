#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t string_hash(const char *s) {
    uint64_t hash = 7;
    for (size_t i = 0; i < strlen(s); i++) {
        hash = hash * 31 + s[i];
    }

    return hash;
}

int main(int argc, char *argv[]) {

    return 0;
}
