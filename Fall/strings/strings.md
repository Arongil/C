Remember to `#include <string.h>`!

Strings are `char *` type. They are arrays that end with a null value `\0`. All string literals are immutable, so technically we write:

```
const char *str = "Hello, world!";
```

Useful function: `char *strdup(const char* str);` duplicates strings so we can mutate them.

Print strings: `printf("%s\n", str);`
Print chars: `printf("%c\n", 'a');`

Chars are really ASCII ints 0 - 255, so `'z' - 'a' == 25`. Use *single quotes* to denote characters. That's the only meaning of single quotes, and double quotes won't work.

Get the length of strings with `size_t strlen(const char *str);`.

Compare two strings with `int strcmp(const char* a, const char* b)`, which returns 0 if `a` and `b` have the same value, something else otherwise. Warning!!! The code `"a" == "a"` only checks whether the two pointers are the same.

```
char *str = { 'a', 'b', 'c', '\0' };
if (strcmp("abc", str) == 0) {
    printf("The same!");
} else {
    printf("Not the same!");
}
```

To concatenate, use `char *strcat(char *s1, const char *s2)`. It puts `s2` at the end of `s1`.

```
char *buffer = calloc(100, sizeof(char));
strcat(buffer, "Hello");
strcat(buffer, ", world");
strcat(buffer, "!");
printf("%s\n", buffer);
// will printf "Hello, world!" because the result of the 100 calloc'ed spaces are still 0, which the compiler interprets as the string having ended.
```

To copy, use `char *strcpy(char *dst, const char *src)`. Will copy the second argument to the first.

```
char *buffer = calloc(100, sizeof(char));
strcpy(buffer, "Hello, world!!");
printf("%s\n", buffer); // prints "Hello, world!!"
```

Because strings are pointers, adding `1` to a string will shift it forward by one. It's still null-terminated, so it'll compile. For example:

```
const char *str = "Howdy!";
printf("%s\n", str + 1);
// prints "owdy!"
```

This lets us get all the substring operations we could want:

```
char *buffer = calloc(100, sizeof(char));
strcpy(buffer, "abcdefg");
strcpy(buffer + 3, "NO ALPHABETS HERE");
// now buffer looks like "abcNO ALPHABETS HERE"
```

To search for a substring or character, use `char *strstr(const char *haystack, const char *needle)` or `char *strchr(const char *s, int c)`. Note: these return a pointer to where the pattern was found.

```
const char *haystack = "Hello world";
const char *pos = strstr(haystack, 'o');

printf("%s\n", pos);
// will return "o world"
// to get the index, just subtract the pointers:
printf("%zu\n", pos - haystack);
// prints 4, because 'o' appears at index 4
```
