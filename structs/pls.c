#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

struct pls {
    uint32_t len;
    uint32_t refcount;
    uint32_t magic;
    char str[];
};
/* Initialise a prefixed length string with the specified
 * string in 'init' of length 'len'.
 *
 * The created strings have the following layout:
 *
 * +----+----+------------\\\
 * |LLLL|CCCC|My strings here
 * +----+----+------------\\\
 *
 * Where L is the 4 unsigned bytes stating the total length 
 * of the string
 * and C is the 4 unsigned bytes counting how many owners share the string.
 * Thus, these strings are binary safe: zero bytes are 
 * permitted in the middle.
 *
 * Warning: this function does not check for buffer overflows. */
char *ps_create(char *init, int len) {
    /* Space for the header struct, len bytes for the string and 1 for the
     * NULL terminator, so that the string is also a valid C string. */
    struct pls *p = malloc(sizeof(struct pls) + len + 1);
    if (p == NULL) return NULL;

    p->len = len;
    p->refcount = 1;

    for (int j = 0; j < len; j++) {
        p->str[j] = init[j]; // We should use memcpy() instead here.
    }
    p->str[len] = 0;

    /* Return the pointer to the string, not to the header. */
    return p->str;
}

/* Display the string 's' on the screen. */
void ps_print(char *s) {
    struct pls *p = ps_header(s);
    for (uint32_t j = 0; j < p->len; j++) {
        putchar(p->str[j]);
    }
    printf("\n");
}

/* Register another owner of the string and return it back. */
char *ps_ref(char *s) {
    struct pls *p = ps_header(s);
    p->refcount++;
    return s;
}

/* Free a previously created PS string. Since the object may be shared, the
 * memory is released only when the last owner drops it. */
void ps_free(char *s) {
    struct pls *p = ps_header(s);
    if (--p->refcount > 0) return;
    free(p);
}

/* Return the length of the string in O(1) time. */
uint32_t ps_len(char *s) {
    return ps_header(s)->len;
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
