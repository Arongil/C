#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* PART 2: my_strspn and my_strcspan */
/* NOTE: needed to place parts out of order to compile. */

// size_t strspn(const char *s, const char *delims)
// EXAMPLES:
//   - strspn("aabb", "a") == 2
//   - strspn("aabb", "ab") == 4
//   - strspn("abcdefg", "df") == 0
// PURPOSE: get out of a swamp of delimiters
// ",,,,real stuff"
//
// size_t strcspn(const char *s, const char *delims)
// EXAMPLES:
//   - strcspn("aabb", "a") == 0
//   - strcspn("aabb", "b") == 2
//   - strcspn("abcdefg", "df") == 3
// PURPOSE: get to next delimiter
// "real stuff,,,,more real stuff"

size_t my_strspn(const char *s, const char *delims) {
    size_t counter = 0;
    while (s[counter] != '\0') {
        size_t delim_index = 0;
        bool found_delim = false;
        while (delims[delim_index] != '\0') {
            if (s[counter] == delims[delim_index]) {
                found_delim = true;
                break;
            }
            delim_index++;
        }
        if (found_delim) {
            counter++;
        } else {
            break;
        }
    }
    return counter;
}

size_t my_strcspn(const char *s, const char *delims) {
    size_t counter = 0;
    while (s[counter] != '\0') {
        size_t delim_index = 0;
        while (delims[delim_index] != '\0') {
            if (s[counter] == delims[delim_index]) {
                return counter;
            }
            delim_index++;
        }
        counter++;
    }
    return counter;
}

/* ---------- PART 1: COMMENTS ON MY_STRTOK ----------  */
/* NOTE: replaced strspn and strcspn with my_ variants. */

char *my_strtok(char *s, const char *delims) {
    // static variables maintain their value between
    // calls to the function in which they are declared.
    static char *next_token = NULL;
    
    if(s == NULL) {
        // If the first argument is NULL, we're
        // starting from the last token we found.
        s = next_token;
    }
    
    // strspn finds the first character in s that is NOT IN delims,
    // i.e. we want to start counting once we're out of the delimiters.
    // If we had "a b : ; c \0" with delims ": ; \0" and s starting at
    // the ":", then s will move forward two so it begins at 'c'.
    s += my_strspn(s, delims);
    
    // If we're at the end of the string, we're done
    if(*s == '\0') {
        return NULL;
    }
    
    // strcspn finds the first character in S that is IN delims,
    // i.e. it spans the complement. This line finds the next
    // character in our delimiter set and moves us up to there.
    next_token = s + my_strcspn(s, delims);
    
    // If the next delimiter we find is already '\0',
    // i.e. we've reached the end of the original string,
    // then just return and be done. Otherwise, set the
    // current delimiter to '\0' and advanced next_token
    // so that the next call to my_strtok starts at the
    // correct location in the string.
    if(*next_token != '\0') {
        *next_token = '\0';
        next_token++;
    }
    
    return s;
}

int main(int argc, char *argv[]) {
    // <SAMPLE CODE FROM THE CANVAS ASSIGNMENT>
    // strtok will modify its argument,
    // so we can't use a literal directly.
    char *s = strdup("This is an example of a, well, a sentence. Hmm, do you wonder what we'll see in it? Ha! I knew you would say it; I knew all along! Apples are great: the greatest indeed!");

    const char *delims = ",.;:!?";

    // The first call needs the string we're
    // tokenizing.
    char *tok_start = strtok(s, delims);

    while(tok_start != NULL) {
        // strtok will add null bytes to our
        // original string so that the things
        // it returns are effectively substrings
        printf("got a token: \"%s\"\n", tok_start);

        // Subsequent calls operating on the
        // same string need to pass NULL for
        // the first argument.
        tok_start = strtok(NULL, delims);
    }

    free(s);
    // </SAMPLE CODE FROM THE CANVAS ASSIGNMENT>
}
