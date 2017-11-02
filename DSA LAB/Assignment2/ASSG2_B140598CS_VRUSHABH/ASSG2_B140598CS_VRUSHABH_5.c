#include<stdio.h>

void InsertionSort(unsigned int  *a, int n){
	int i, j;
	unsigned int key, temp;
	for(i = 1; i < n; ++i){
		key = a[i];
		j = i;
		while((j > 0) && (a[j - 1] > key)){
			temp = a[j - 1];
			a[j - 1] = a[j];
			a[j] = temp;
			j--;
		}
	}
	
	return;
}

int checkForNegative(int *a, int n){
	int i = 0;

	while(i < n){
		if(a[i] >= 4294960000){
			return 0;
		}
		++i;	
	}
	return 1;
}


void printList(int *a, int length){
	int i = 0;
	for(i = 0; i < length; ++i){
		printf("%u  ",a[i]);
	}
	printf("\n");
	return;
}

int main(){
	int i, n;
	unsigned int a[100];
	
	scanf("%d", &n);
	if(n >= 2147483648 || n < 0){
		printf("Please Enter a Valid Input!!\n");
		return -1;
	}
	
	for(i = 0; i < n; ++i){
		scanf("%u",&a[i]);
	}

	if(checkForNegative(a, n) == 0){
		printf("Enter Only Positive Numbers!!\n");
		return -1;		
	}
	
	InsertionSort(a, n);
	printList(a, n);

	return 0;
}