#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "weather.h"
#include "listener.h"

void get_weather() {
    printf("What is your zip code? ");
    char *zip = calloc(20, sizeof(char));
    scanf("%s", zip);
    output_weather(zip);
}
int main(int argc, char *argv[]) {
    if (argc == 2) {
        if (strcmp(argv[1], "help") == 0) {
            printf("Talk to the genie. If you say the magic word, he will open.\n\nTo reset the magic word, run \"./genie key\".\n\nTo get the weather the boring way, run \"./genie weather\".");
        } else if (strcmp(argv[1], "weather") == 0) {
            get_weather();
        } else if (strcmp(argv[1], "key") == 0) {
            reset_key();
        }
        return 0;
    }

    if (attempt_genie() == 0) {
        printf("\n\n~~~ The genie has denied you. ~~~");
    } else {
        printf("\n\n~~~ The genie has been summoned! ~~~");
        printf("\n\nHe will grant you one wish.\n\n");
        get_weather();
    }

    return 0;
}
