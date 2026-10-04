#include<stdio.h>

int potenza_ric(int a, int b)
{
	int res=1;

	if(b==0)
	{
		res = 1; 	
	}
	else
	{
		res = a * potenza_ric(a,b-1);	
	}

	return res;
}


int main(void)
{
	printf("%d \n", potenza_ric(4,2));
}
