#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Using 'malloc()' this time
 * Initialise a prefixed length string with the specified
 * string in 'init' of length 'len'.
 *
 * The created strings have the following layout:
 *
 * +----+------------\\\
 * |LLLL|My strings here
 * +----+------------\\\
 *
 * Where L is the 4 unsigned bytes stating the total length of the string.
 * Thus, these strings are binary safe: zero bytes are permitted in the middle.
 *
 * Warning: this function does not check for buffer overflows. */
char *ps_create(char *init, int len) {
    /* 4 bytes for the length, len bytes for the string and 1 for the
     * NULL terminator, so that the string is also a valid C string. */
    char *s = malloc(4 + len + 1);
    uint32_t *lenptr = (uint32_t *)s;
    *lenptr = len;

    /* Move the pointer past the header: from now on 's' points to the
     * first character of the string, so it can be used by any C function. */
    s += 4;
    for (int j = 0; j < len; j++) {
        s[j] = init[j]; // We should use memcpy() instead here.
    }
    s[len] = 0;
    return s;
}

/* Display the string 's' on the screen. */
void ps_print(char *s) {
    uint32_t *lenptr = (uint32_t *)(s - 4);
    for (int j = 0; j < *lenptr; j++) {
        putchar(s[j]);
    }
    printf("\n");
}

/* Free a previously created PS string. */
void ps_free(char *s) {
    /* free() wants the exact pointer returned by malloc(), and that
     * pointer is 4 bytes before the string, where the header lives. */
    free(s - 4);
}

/* Return the length of the string in O(1) time. */
uint32_t ps_len(char *s) {
    uint32_t *lenptr = (uint32_t *)(s - 4);
    return *lenptr;
}

char *global_string;

int main(void) {
    char *mystr = ps_create("Hello WorldHelloWorldHelloWorld", 33);
    global_string = mystr;
    ps_print(mystr);
    ps_print(mystr);
    printf("%s %d\n", mystr, (int)ps_len(mystr));
    ps_free(mystr);
    printf("%s\n", global_string);
    return 0;
}
