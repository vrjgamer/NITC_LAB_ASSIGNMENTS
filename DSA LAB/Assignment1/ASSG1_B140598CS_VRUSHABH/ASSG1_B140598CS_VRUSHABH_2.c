#include<stdio.h>

int count(int n ,int sum){	
	if(n < 0){
		return sum;
	}
	
	if(n%2 == 1){
		sum++;
	}
	count(n/2,sum);
}

int main(){
	int decimal,n , count_one =0;
	printf("Enter a positive decimal number: ");
	scanf("%d",&decimal);
	n = decimal;
	count_one = count(n,0);
	printf("The binary representation of %d contains %d 1's.\n",decimal , count_one);
	return 0;
}