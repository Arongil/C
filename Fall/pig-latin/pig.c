#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool is_vowel(char c) {
    char s = (char)tolower(c);
    return s == 'a' || s == 'e' || s == 'i' || s == 'o' || s == 'u' || s == 'y';
}

bool is_uppercase(const char c) {
    return c >= 65 && c < 91;
}
bool is_lowercase(const char c) {
    return c >= 97 && c < 123;
}
bool is_letter(const char c) {
    // for our purposes, an apostrophe ' is a letter. Thus, "can't" --> "an'tcay".
    return is_lowercase(c) || is_uppercase(c) || c == 39;
}
bool is_space(const char c) {
    return c == 32;
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

// Ex: "Hello, world!" --> "Ellohay, orldway!"
char *to_pig_latin(const char *str) {
    int word_count = 1;
    int str_length = strlen(str);
    for (int i = 0; i < str_length; i++) {
        if (is_space(str[i])) {
            word_count += 1;
        }
    }

    // Each word lengthens by at most 3 characters in pig latin.
    // We run through str and construct new_str on the fly.
    char *new_str = calloc(str_length + word_count * 3, sizeof(char));
    int index = 0; // where we are in building new_str
    for (int i = 0; i < str_length; i++) {
        if (!is_letter(str[i])) {
            new_str[index] = str[i];
            index++;
            continue;
        }
        // Assume we are at the first letter of a word.
        // Find the entire word, transform it, move on.
        int word_length = 1;
        while (is_letter(str[i + word_length])) {
            word_length++;
        }
        char *word = calloc(word_length + 1, sizeof(char));
        strncpy(word, str + i, word_length);
        char *pig_word = word_to_pig_latin(word);
        strcpy(new_str + index, pig_word);
        index += strlen(pig_word);
        i += word_length - 1;
    }

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

char *read_str() {
    printf("What sentence would you like to translate?\n>");
    char *str = malloc(16384 * sizeof(char));
    fgets(str, 16384 * sizeof(char), stdin);
    return str;
}

int main(int argc, char *argv[]) {
    // test_pig_latin();

    // char *str = "Today is such a lovely day! I can't wait to get programming.";
    // printf("Original:  %s\nPig Latin: %s\n", str, to_pig_latin(str));

    char *str = read_str();
    printf("%s", to_pig_latin(str));
    free(str);

    return 0;
}
