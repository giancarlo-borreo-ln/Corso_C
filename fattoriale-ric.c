#include<stdio.h>

int fattoriale(int n){
    if(n==0) return 1;
   
    return n * fattoriale(n-1);
}

int main(void)
{
	int a;
	scanf("%d", &a);
	int risultato = fattoriale(a);
	printf("Il fattoriale di %d e' %d \n", a, risultato);
}
