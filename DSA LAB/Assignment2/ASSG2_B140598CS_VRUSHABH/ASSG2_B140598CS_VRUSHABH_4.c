#include<stdio.h>

void BubbleSort(float a[100], int n){
	
	float temp = 0;
	int i, j;
	
	for(i = 0; i < n; ++i){
		for(j = i; j < n; ++j){
			if(a[i] > a[j]){
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
	
	return;
}
void printList(float a[100], int length){
	int i = 0;
	for(i = 0; i < length; ++i){
		printf("%0.4f ",a[i]);
	}
	return;
}
int main(){
	int i,n;
	float a[100];
	
	scanf("%d",&n);
	if(n >= 2147483648 || n < 0){
		printf("Please Enter a Valid Input!!\n");
		return -1;
	}
	for(i = 0; i < n; ++i){
		scanf("%f",&a[i]);
	}
	BubbleSort(a, n);
	printList(a,n);
	
	return 0;
}