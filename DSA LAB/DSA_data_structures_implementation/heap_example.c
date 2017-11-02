#include<stdio.h>
#include<stdlib.h>



struct Heap{
	int *array;
	int heapsize;
	int max;

};



int getLeft(int index){

	return index * 2;	

}



int getRight(int index){

	return (index * 2) + 1;

}



int getParent(int index){

	return index / 2;

}



void MaxHeapify(struct Heap* H, int index){

	int root = index, temp;

	if(getLeft(index) < H->heapsize){

		if(H->array[getLeft(index)] > H->array[index]){

			root = getLeft(index);

		}

	

		if(getRight(index) < H->heapsize){

			if(H->array[getRight(index)] > H->array[root]){

				root = getRight(index);

			}

		}

	}



	if(root != index){

		temp = H->array[index];

		H->array[index] = H->array[root];

		H->array[root] = temp;

		MaxHeapify(H, root);

	}

	return;

}



void BuildHeap(struct Heap* H){

	int i;

	

	for(i = H->heapsize/2; i >= 0 ; --i){

		MaxHeapify(H, i);

	}

	

	return;

}



int main(){

	int n, temp, i;

	scanf("%d", &n);

	

	struct Heap* H = (struct Heap*)malloc(sizeof(struct Heap));

	int* a = (int*)malloc(n * sizeof(int));

	

	H->heapsize = 0;

	H->max = n;

	H->array = a;

	

	for(i = 0; i < H->max; i++){

		scanf("%d", &temp);

		H->array[i] = temp;

		H->heapsize++;

	}



	BuildHeap(H);

	

	for(i = 0; i < H->heapsize; ++i){

		printf("%d ", H->array[i]);

	}



	return 0;



}

