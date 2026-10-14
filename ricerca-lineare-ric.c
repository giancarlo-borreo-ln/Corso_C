#include<stdio.h>

int ricercaLineareRicorsiva(int a[], int lenA, int chiave, int indice){
	int res = -1;
	
	if(lenA>indice){
		if(a[indice] == chiave){
			res = indice;
		} else{
			res = ricercaLineareRicorsiva(a,lenA,chiave, indice+1);
		}
	}
	return res;
}

int main(){
	int a[] = {1,2,3,4,5,6,7,8,9};
	int res = ricercaLineareRicorsiva(a,9,9,0);

	printf("%d \n", res);	
}
