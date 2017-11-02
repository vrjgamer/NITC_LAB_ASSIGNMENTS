#include<stdio.h>
#include<stdlib.h>

struct Stack{
		int *array;
		int top;
		int array_size;
};

void InitializeStack(struct Stack *S, int size){
	S->top = 0;
	S->array = (int*)malloc(size * sizeof(int));
	S->array_size = size;
}

int IsFull(struct Stack *S){
	if(S->top != S->array_size){
		return 0;
	}else{
		return 1;
	}
}

int IsEmpty(struct Stack *S){
	if(S->top != 0){
		return 0;
	}else{
		return 1;
	}
}

int push(struct Stack *S, int element){
	if(IsFull(S) == 1){
		printf("OVERFLOW\n");
		return 0;
	}else{
		S->array[S->top] = element;
		S->top = (S->top) + 1;
		return 1;
	}
	
}
int pop(struct Stack *S){
	int out;
	if(IsEmpty(S) == 1){
		printf("EMPTY\n");
		return -1;
	}else{
		out = S->array[S->top - 1];
		S->top = (S->top) - 1;
		return out;
	}
}

void printList(struct Stack *S){
	int i;
	if(IsEmpty(S)){
		printf("EMPTY\n");
		return;
	}
	for(i = S->top - 1; i >= 0; i--){
		printf("%d ", (*S).array[i]);
	}
	printf("\n");
	return;
}
int main(){
	struct Stack *S = (struct Stack*)malloc(sizeof(struct Stack));
	int temp, n;
	char choice;
	
	scanf("%d", &n);
	InitializeStack(S, n);
	
	do{
		scanf(" %c", &choice);
		switch(choice){
			case 'a':
				scanf("%d", &temp);
				if(temp >= 0){
					push(S, temp);
				}else{
					printf("Negative Input\n");
				}
				break;
			case 'r':
				if((temp = pop(S)) != -1){
					printf("%d\n", temp);
				}	
				break;
			case 'p':
				printList(S);
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


