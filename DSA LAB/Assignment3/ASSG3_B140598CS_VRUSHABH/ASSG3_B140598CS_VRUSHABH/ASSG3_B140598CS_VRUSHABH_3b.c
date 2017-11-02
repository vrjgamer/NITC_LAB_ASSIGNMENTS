#include<stdio.h>
#include<stdlib.h>

struct node{
	int data;
	struct node *next;	
};

struct Queue{
	struct node *front;
	struct node *back;
};

void InitializeQueue(struct Queue *Q){
	Q->front = (struct node*)malloc(sizeof(struct node));
	Q->back = (struct node*)malloc(sizeof(struct node));
	Q->front = NULL;
	Q->back = NULL;	
}

int IsEmpty(struct Queue *Q){
	if(Q->front == NULL){
		return 1;	
	}else{
		return 0;		
	}
}

void Enqueue(struct Queue *Q, int element){
	struct node *in = (struct node*)malloc(sizeof(struct node));
	in->data = element;
	in->next = NULL;
	if(IsEmpty(Q) == 0){
		Q->back->next = in;	
		Q->back = in;	
	}else {
		Q->front = in;
		Q->back = in;	
	}
}

struct node* Dequeue(struct Queue *Q){
	struct node *out = (struct node*)malloc(sizeof(struct node));
	if(IsEmpty(Q) == 0){
		out = Q->front;
		Q->front = Q->front->next;
		if(Q->back == out){
			Q->back = Q->back->next;		
		}
		return out;	
	}else {
		printf("EMPTY\n");
		return NULL;	
	}
}
void printList(struct Queue *Q){
	if(IsEmpty(Q)){
		printf("EMPTY\n");
		return;
	}
	struct node *current = (struct node*)malloc(sizeof(struct node));
	current = Q->front;
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
 	struct Queue *Q = (struct Queue*)malloc(sizeof(struct Queue));
	struct node *element = (struct node*)malloc(sizeof(struct node));
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
				if((element = Dequeue(Q)) != NULL){
					printf("%d\n", element->data);
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
				printf("Invalid case\n");
		}
	}while(choice != 's');
	
	return 0;
}

