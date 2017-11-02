#include<stdio.h>

int getLeft(int root){
	return ((root * 2) + 1);
}

int getRight(int root){
	return ((root * 2) + 2);
}

void PrintList(int *a, int length){
	int i;
	for(i = 0; i < length; ++i){
		printf("%d ",a[i]);
	}	
	printf("\n");
	return;
}

void FixHeap(int *a, int index, int heapsize){
	int root = index, temp;
	
	if(getLeft(index) < heapsize){
		if(a[getLeft(index)] > a[index]){
			root = getLeft(index);
		}
	}
	if(getRight(index) < heapsize){
			if(a[getRight(index)] > a[root]){
				root = getRight(index);
			}
		}
	if(root != index){
		temp = a[root];
		a[root] = a[index];
		a[index] = temp;
		FixHeap(a, root, heapsize);
	}
	
	return;
}


void BuildHeap(int *a, int length){
	int heapSize = length, i;
	
	for(i = heapSize - 1; i >= 0; --i){
		FixHeap(a, i, heapSize);
	}
	return;
}


void HeapSort(int *a, int length){
	int top = length, temp;
	BuildHeap(a, length);
	while(top > 0){
		//swap first and last
		temp = a[top];
		a[top] = a[0];
		a[0] = temp;
		top--;
		FixHeap(a, 0, top);
	}
	
	return;
}

int checkIfSorted(int *a, int length){
	int i;
	for(i = 1; i < length; ++i){
		if(a[i] < a[i - 1]){
			return 0; 
		}
	}
	return 1;
}

int main(){
	int a[100], i, n;
	
	scanf("%d", &n);
	if(n >= 2147483648 || n < 0){
		printf("Please Enter a Valid Input!!\n");
		return -1;
	}
	for(i = 0; i < n; ++i){
		scanf("%d", &a[i]);
	}
	HeapSort(a, n);
	
	checkIfSorted(a , n);
	
	PrintList(a, n);
	
	return 0;
}


