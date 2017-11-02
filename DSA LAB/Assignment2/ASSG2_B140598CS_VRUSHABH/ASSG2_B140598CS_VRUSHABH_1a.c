#include<stdio.h>


int BinarySearch(int a[100], int k, int length){
	int lower = 0, upper = (length - 1), mid;
	
	while(lower < upper){
		mid = (lower + upper)/2;
		if(a[mid]== k){
			return  mid;
		}else if(a[mid] < k){
			upper = mid - 1;
		} else{
			lower = mid + 1;
		}
	}
	return -1;
}

int checksorted(int a[100], int length){
	int i = 0;
	
	for(i = 1; i < length; ++i){
		if(a[i -1] > a[i]){
			return 0;
		}
	}
	
	return 1;
}


int main(){
	int a[100];
	int n, k, i = 0, position = 0;
	
	scanf("%d", &n);
	if(n >= 2147483648 || n < 0){
		printf("Please Enter a Valid Input!!\n");
		return -1;
	}
	for(i = 0; i < n ; ++i){
		scanf("%d",&a[i]);
	}
	
	if(checksorted(a, n) == 0){
		printf("The array is not sorted\n");
		return -1;
	}

	scanf("%d", &k);
	
	position = BinarySearch(a, k , n);
	
	if(position > 0){
		printf("%d\n", position + 1);
	}else{
		printf("NOT_FOUND\n");
	}
	return 0;
}