#include<stdio.h>
#include<stdlib.h>

struct Queue{
	int *array;
	int max;
	int front;
	int back;
};

void InitializeQueue(struct Queue *Q, int max){
	Q->max = max;
	Q->array = (int*)malloc(max * sizeof(int));
	Q->front = 0;
	Q->back = 0;	
}

int IsEmpty(struct Queue *Q){
	if(Q->front == Q->back){
		return 1;	
	}else{
		return 0;		
	}
}

int IsFull(struct Queue *Q){
	if(Q->back != (Q->max)){
		if(((Q->back) + 1) == Q->front){
			return 1;		
		}else{
			return 0;
		}	
	}else {
		if(Q->front == 0){
			return 1;	
		}else{
			return 0;		
		}	
	}	
}

int Enqueue(struct Queue *Q, int element){
	if(IsFull(Q) == 0){
		Q->array[Q->back] = element;
		if(Q->back == (Q->max)){
			Q->back = 0;		
		}else {
			Q->back = Q->back + 1;		
		}
		return 1;	
	}else {
		printf("OVERFLOW\n");
		return 0;	
	}
}

void printList(struct Queue *Q){
	int i = Q->front, n =  Q->back - 1;
	if(IsEmpty(Q)){
		printf("EMPTY\n");
		return;
	}
	while(i <= n){
		printf("%d ", Q->array[i]);
		i++;
	}
	printf("\n");
	return;
}

int Dequeue(struct Queue *Q){
	int out = NULL, n = Q->max;
	if(IsEmpty(Q) == 0){
		out = Q->array[Q->front]; 
		if(Q->front != n){
			Q->front = Q->front + 1;		
		}else {
			Q->front = 0;		
		}
		return out;
	}else {
		printf("EMPTY\n");
		return 0;		
	}
}

int main(){
	int n, temp;
	char choice;
	
	struct Queue *Q = (struct Queue*)malloc(sizeof(struct Queue));
	
	scanf("%d", &n);

	InitializeQueue(Q, n);
	
	do{
		scanf(" %c", &choice);
		switch(choice){
			case 'e':
				scanf("%d", &temp);
				if(temp >= 0){
					Enqueue(Q, temp);
				}else{
					printf("Negative Input\n");
				}
				break;
			case 'd':
				if((temp = Dequeue(Q)) != 0){
					printf("%d\n", temp);
				}
				break;
			case 'p':
				printList(Q);
				break;
			case 's':
				choice = 's';
				return 0;
				break;
			default: 
				printf("Invalid Case\n");
		}	
	}while(choice != 's');
	
	return 0;

}
