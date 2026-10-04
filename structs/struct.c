#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>


/*
 *Create a new fraction, setting num and den as the numerator
 *and denominator of the fraction.
 *The function returns NULL on out of memory
 *Otherwise the fraction object is returned;
 * */
int *create_fraction(int *f, int num, int den){
    int *f = malloc(sizeof(int) * 2);

    if(*f == NULL) return NULL;


    f[0] = num;
    f[1] = den;
}

void simplify_fraction(int *f){
    
}

void print_fraction(int *f){
    printf("%d%d", f[0], f[1]);
}


int main(void){
    int *f1 = create_fraction(f,1,2);
    int *f2 = create_fraction(f,3,4);
    simplify_fraction(f1);
    set_fraction(*f,1,2);

    print_fraction(f);
    
    return 0;
}

