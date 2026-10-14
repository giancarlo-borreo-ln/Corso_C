#include<stdio.h>

int somma(int n)
{
	int res;
	if(n==1)
	{
		res = 1;
	}else
	{	
		res = n + somma(n-1);		
	}

	return res;	
}



int main(void)
{
	int a;

	scanf("%d", &a);

	printf("%d \n", somma(a));	
}
