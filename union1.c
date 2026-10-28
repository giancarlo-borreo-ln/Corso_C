#include <stdio.h>
#include <string.h>
#include <limits.h>
struct foo {
    union {
        unsigned int i;
        unsigned char a[4];
    };
};

/* IIII0123 */

int main(void) {
    struct foo f;
    f.i = UINT_MAX;
    printf("%d [%d %d %d %d] \n", f.i, f.a[0], f.a[1], f.a[2], f.a[3]);
    return 0;
}
