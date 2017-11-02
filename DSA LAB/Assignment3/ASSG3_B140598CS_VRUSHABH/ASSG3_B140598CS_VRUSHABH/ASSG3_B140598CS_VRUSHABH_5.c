#include<stdio.h>
#include<stdlib.h>

struct QueueElement{
	int data;
	int priority;
};

struct Heap{
	int heapSize;
	struct QueueElement *priorityQueue;
};

int getLeft(int root){
	return ((root * 2));
}

int getRight(int root){
	return ((root * 2) + 1);
}

void Initialize(struct Heap *H, struct QueueElement Q[]){
	H->heapSize = 0;
	H->priorityQueue = Q;
}

int IsEmpty(struct Heap *H){
	if(H->heapSize == 0){
		return 1;
	}else{
		return 0;
	}
}

void FixHeap(struct Heap *H, int index){
	int root = index; 
	struct QueueElement temp;
	
	if(getLeft(index) < H->heapSize){
		if(H->priorityQueue[getLeft(index)].priority < H->priorityQueue[index].priority){
			root = getLeft(index);
		}
	}
	if(getRight(index) < H->heapSize){
			if(H->priorityQueue[getRight(index)].priority < H->priorityQueue[root].priority){
				root = getRight(index);
			}
		}
	if(root != index){
		temp = H->priorityQueue[root];
		H->priorityQueue[root] = H->priorityQueue[index];
		H->priorityQueue[index] = temp;
		FixHeap(H, root);
	}	
	return;
}

int insert(struct Heap *H, int element, int priority){
	H->heapSize++;
	H->priorityQueue[H->heapSize - 1].priority = 2147483600;
	decrease_priority(H, H->heapSize - 1, element, priority);
	return 1;
}

int decrease_priority(struct Heap *H, int index, int element, int priority){
	
	H->priorityQueue[index].data = element;
	H->priorityQueue[index].priority = priority;
	struct QueueElement temp;
	while((index > 0) && (H->priorityQueue[index / 2].priority > H->priorityQueue[index].priority))
	{
		temp = H->priorityQueue[index];
		H->priorityQueue[index] = H->priorityQueue[index / 2];
		H->priorityQueue[index / 2] = temp;
		index = index / 2;
	}
	return 1;
}

int get_min(struct Heap *H){
	if(IsEmpty(H) == 1){
		printf("EMPTY\n");
		return -1;
	}else{
		return (H->priorityQueue[0].data);	
	}
}

int needTodecrease(struct Heap *H, int element, int priority){
	int i = 0;
	for(i = 0; i <= H->heapSize; ++i){
		if(H->priorityQueue[i].data == element){
			if(H->priorityQueue[i].priority > priority){
				return i;
			}else {
				printf("Invalid Priority Change\n");
				return -1;
			}
		}
	}
	printf("Element Not Found\n");
	return -1;
}

int extract_min(struct Heap *H){
	if(IsEmpty(H) == 1){
		printf("EMPTY\n");
		return -1;
	}else{
		struct QueueElement out;
		out = H->priorityQueue[0];
		H->priorityQueue[0] = H->priorityQueue[H->heapSize - 1];
		H->heapSize--;
		FixHeap(H, 0);
		return out.data;
	}
}
int main(){
	int x, priority;
	char choice;
	int temp;
	struct Heap *H = (struct Heap*)malloc(sizeof(struct Heap));
	struct QueueElement queue[1000] = {{0}};
	
	Initialize(H, queue);
	
	do{
		scanf(" %c", &choice);
		switch(choice){
			case 'a':
				scanf("%d%d", &x, &priority);
				if(x >= 0 && priority >= 1){
					insert(H, x, priority);
				}else{
					printf("Invalid Input\n");
				}
				break;
			case 'e':
				if((temp = extract_min(H)) != -1){
					printf("%d\n", temp);
				}
				break;
			case 'g':
				if((temp = extract_min(H)) != -1){
					printf("%d\n", temp);
				}
				break;
			case 'd':
				scanf("%d%d", &x, &priority);
				if(x >= 0 && priority >= 1){
					if((temp = needTodecrease(H, x, priority)) != -1){
						decrease_priority(H, temp, x, priority);
					}
				}else{
					printf("Invalid Input\n");
				}
				break;
			case 's':
				choice = 's';
				return 0;
				break;
			default:
				printf("INVALID CASE\n");
		}
		
	}while(choice != 's');
	
	return 0;
	
}
