#include<stdio.h>

int main(int argc, char **argc){
    for(int i=0; i<argc; i++){
        printf("%d: %s\n", i, argv[i]);
    }
}
