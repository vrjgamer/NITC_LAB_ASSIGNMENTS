#include<stdio.h>
#include<stdlib.h>

struct node{
	int data;
	struct node* next;
};

struct Stack{
		struct node *top;
};

void InitializeStack(struct Stack *S){
	S->top = (struct node*)malloc(sizeof(struct node));
	S->top = NULL;
	return;
}

int IsEmpty(struct Stack *S){
	if(S->top != NULL){
		return 0;
	}else{
		return 1;
	}
}

int push(struct Stack *S, int element){
	struct node *cast = (struct node*)malloc(sizeof(struct node));
	cast->data = element;
	cast->next = S->top;
	S->top = cast;
	return 1;
}

struct node* pop(struct Stack *S){
	if(IsEmpty(S) == 0){
		struct node *out = (struct node*)malloc(sizeof(struct node));
		out = S->top;
		S->top = S->top->next;
		return out;
	}else{
		printf("EMPTY\n");
		return NULL;
	}
	
}

void printList(struct Stack *S){
	if(IsEmpty(S)){
		printf("EMPTY\n");
		return;
	}
	struct node *current = (struct node*)malloc(sizeof(struct node));
	current = S->top;
	while(current != NULL){
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
	return;
}

int main(){
	int temp;
	char choice;
	struct Stack *S = (struct Stack*)malloc(sizeof(struct Stack));
	struct node *element = (struct node*)malloc(sizeof(struct node));
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
				if((element = pop(S)) != NULL){
					printf("%d", element->data);
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


