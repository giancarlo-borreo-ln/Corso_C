#include<stdio.h>
#include<string.h>

int main(void){
    char *mystr = "Hello World\n";
    size_t len = strlen(mystr);
    for(size_t j = 0; j < len; j++){
        //write(STDOUT_FILENO, mystr+j, 1);
        putchar(mystr[j]);
        fflush(stdout);
    }
    return 0;
}
