#include<stdio.h>

int calcFatFor(int n)
{
	res = 1;
	for(int i=1; i<=n; i++)
	{
		res*=n;
	}	
}
int calcFatWhile(int n)
{
	res = 1;
	int i=1;
	while(i<=n)
	{
		res*=n;
	}
}

int main(void)
{
	int a;
	scanf("%d \n");
	printf("Il fattoriale di %d è: %d", a, calcFatWhile(a));
}
