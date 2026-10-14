#include<stdio.h>

int fattoriale(int n)
{
	int res = 1;

	if(n == 0) 
	{
		res=1;
	}
	else
	{

		res =n * fattoriale(n-1);
	}

	return res;
	
}

int main(void)
{
	int a;
	scanf("%d", &a);
	int risultato = fattoriale(a);
	printf("Il fattoriale di %d e' %d \n", a, risultato);
}
