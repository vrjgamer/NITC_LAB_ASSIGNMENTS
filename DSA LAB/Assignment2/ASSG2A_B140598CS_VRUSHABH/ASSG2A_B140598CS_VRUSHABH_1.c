#include<stdio.h>

int findSumPair(int *a, int n, int sum){
	int i = 0, j = n - 1;
	while(i < j){
		if((a[i] + a[j]) == sum){
			printf("%d %d\n", a[i] , a[j]);
			return 1;
		}else if((a[i] + a[j]) > sum){
			j--;
		}else{
			i++;
		}
	}
	return 0;
}

int checkSorted(int *a, int n){
	int i;
	for(i = 1; i < n; ++i){
		if(a[i] < a[i - 1]){
			return 0;
		}
	}
	return 1;
}

int main(){
	int i, n , sum;
	int a[100];
	
	scanf("%d", &n);
	
	for(i = 0; i < n; ++i){
		scanf("%d", &a[i]);
	}
	
	scanf("%d", &sum);
	
	if(checkSorted(a, n) == 0){
		printf("Array is not in Sorted Order!!\n");
		return -1;
	}
	
	
	if(findSumPair(a, n, sum) == 0){
		printf("No two elements sum up to %d\n", sum);
		return -1;
	}
	
	return 0;
}