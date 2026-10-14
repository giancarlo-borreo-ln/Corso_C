#include<stdio.h>


void diamante(int n){
	for (int i = 0; i < 2 * n - 1; i++) {

      	 	int comp;
        	if (i < n){ 
			comp = 2 * (n - i) - 1;
		}
        	else {
			comp = 2 * (i - n + 1) + 1;
		}

        	for (int j = 0; j < comp; j++){
            		printf(" ");
		}

        	for (int k = 0; k < 2 * n - comp; k++) {
            		printf("* ");
        	}
        	printf("\n");
    	}

}

void floyd(int n){
	for(int i=0; i<=n; i++){
		for(int j=0; j<=i; j++){
			printf("%d ", j);	
		}
		printf("\n");
	}
}

int main(void)
{
	int a;
	scanf("%d", &a);
	floyd(a);
}
