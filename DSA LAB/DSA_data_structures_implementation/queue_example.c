#include<stdio.h>
#include<stdlib.h>

struct node{
	int data;
	struct node* next;
};

struct queue{
	struct node* head;
	struct node* tail;
};

int isEmpty(struct queue* Q){
	if(Q->tail == NULL){
		return 1;
	}else {
		return 0;	
	}	
}

int enqueue(struct queue* Q, int e){
	
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->data = e;
	temp->next = NULL;
	
	if(isEmpty(Q) == 1){
		Q->head = temp;
		Q->tail = temp;
	}else{
		Q->tail->next = temp;
		Q->tail = temp;
	}
	return 1;
}


struct node* dequeue(struct queue* Q){
	
	struct node* out = (struct node*)malloc(sizeof(struct node));
	if(isEmpty(Q) == 1){
		return NULL;
	}else{
		out = Q->head;
		Q->head = Q->head->next;
		if(Q->tail == out){
			Q->tail = Q->tail->next;
		}	
		return out;
	}
}


int main(){
	int temp;
	char c;
	struct queue* Q = (struct queue*)malloc(sizeof(struct node));
	Q->head = NULL;
	Q->tail = NULL;
	struct node* out = (struct node*)malloc(sizeof(struct node));
	
	do{
		scanf(" %c", &c);
		
		switch(c){
			case 'e':
				scanf("%d", &temp);
				enqueue(Q, temp);
				break;
			case 'd':
				if((out = dequeue(Q)) != NULL){
					printf("%d\n", out->data);
				}else{
					printf("EMPTY\n");
				}
				break;	
			case 's':
				return 0;
				break;
			default:
				printf("Invalid Input\n");
		}

	}while(1);
	
	return 0;

}
