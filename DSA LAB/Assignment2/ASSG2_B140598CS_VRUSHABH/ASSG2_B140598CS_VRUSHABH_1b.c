#include<stdio.h>

int BinarySearch(int a[100], int k, int upper, int lower){
	int mid = (upper + lower)/2;
	
	if(lower > upper){
		return -1;
	}
	if(a[mid] > k){
		return BinarySearch(a, k, upper, mid + 1);	
	}else if(a[mid] < k) {
		return BinarySearch(a, k, mid -1, lower);
	}else{ 
		return mid;
	}
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
	
	int a[100], n, i, k, position;
	
	scanf("%d",&n);
	if(n >= 2147483648 || n < 0){
		printf("Please Enter a Valid Input!!\n");
		return -1;
	}
	for(i =0 ; i < n; ++i){
		scanf("%d",&a[i]);
	}
	
	if(checksorted(a, n) == 0){
		printf("The array is not sorted\n");
		return -1;
	}

	scanf("%d",&k);
	
	position = BinarySearch(a, k, n-1, 0);
	
	if(position > 0){
		printf("%d\n", position + 1);
	}else{
		printf("NOT_FOUND\n");
	}
	
	return 0;
}



