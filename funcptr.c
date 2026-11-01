#include <stdio.h>

void hello(void) { printf("Hello! \n"); }

void baubau(void) { printf("Bau Bau! \n"); }

int main(void) {
    int (*myf)(void);

    myf = main;

    printf("%p\n", main);
    printf("%p\n", myf);
    myf();
    return 0;
}
