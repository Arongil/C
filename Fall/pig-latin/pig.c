#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

bool is_vowel(char c) {
    char s = (char)tolower(c);
    return s == 'a' || s == 'e' || s == 'i' || s == 'o' || s == 'u' || s == 'y';
}

bool is_uppercase(const char c) {
    return c >= 65 && c < 91;
}

int consonant_prefix_length(const char *str) {
    int index = 0;
    if (str[0] == 'y' || str[0] == 'Y') {
        // edge case: y is a vowel UNLESS it's at the start of a word
        index++;
    }
    while (!is_vowel(str[index])) {
        index++;
    }
    return index;
}

char *word_to_pig_latin(const char *word) {
    // Assess the word to enter one of two cases:
    // 1) Vowel starts as in 'eagle'. Then just add 'w' to the end.
    // 2) Consonant string starts as in 'scream'. Add consonant string to end and remove from start.
    // No matter what, add 'ay' to the end.
    int consonant_start = consonant_prefix_length(word);
    int len = strlen(word);
    int new_len = consonant_start == 0 ? len + 4 : len + 3;
    char *new_str = calloc(new_len, sizeof(char));
    if (consonant_start == 0) {
        strcpy(new_str, word);
        new_str[len] = 'w';
    } else {
        strcpy(new_str, word + consonant_start);
        strncpy(new_str + len - consonant_start, word, consonant_start);
        if (is_uppercase(new_str[len - consonant_start])) {
            // Ex: turn 'Smote' --> 'oteSm' -- > 'otesm'
            new_str[len - consonant_start] += 32;
        }
        if (is_uppercase(word[0]) && !is_uppercase(new_str[0])) {
            // Ex: turn 'Smote' --> 'otesm' -- > 'Otesm'
            new_str[0] -= 32;
        }
    }
    new_str[new_len - 3] = 'a';
    new_str[new_len - 2] = 'y';

    return new_str;
}

void test_pig_latin() {
    const char *cases[][2] = {
        { "exit", "exitway" },
        { "Yellow", "Ellowyay" },
        { "scram", "amscray" },
        { "blue", "ueblay" },
        { "Type", "Ypetay" },
        { "igloo", "iglooway" },
        { "Float", "Oatflay" },
        { "bandanda",  "andandabay" },
        { "Apple", "Appleway" },
        
        // feel free to add more cases above this line,
        // but leave the { NULL, NULL } line intact.
        { NULL, NULL }
    };
    
    size_t i = 0;
    int failed_cases = 0, passed_casses = 0;
    while(1) {
        const char *original = cases[i][0];
        const char *expected_latin = cases[i][1];
        
        if(!original || !expected_latin) {
            break;
        }
        
        char *actual_latin = word_to_pig_latin(original);
        
        if(!actual_latin || strcmp(expected_latin, actual_latin) != 0) {
            printf("Test case failed: expected '%s' -> '%s', but got '%s'\n", original, expected_latin, actual_latin);
            
            failed_cases++;
        }
        else {
            passed_casses++;
        }
        
        free(actual_latin);
        
        i++;
    }
    
    printf("%d/%d cases passed\n", passed_casses, failed_cases + passed_casses);
}

int main(int argc, char *argv[]) {
    test_pig_latin();

    return 0;
}
