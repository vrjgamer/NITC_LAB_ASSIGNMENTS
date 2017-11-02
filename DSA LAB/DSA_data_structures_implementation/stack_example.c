#include<stdio.h>
#include<stdlib.h>

struct node{
	int data;
	struct node* next;
};

int isEmpty(struct node* S){
	if(S->next == NULL){
		return 1;
	}else {
		return 0;	
	}
	
}
int push(struct node* S, int e){
	
	struct node* temp = (struct node*) malloc(sizeof(struct node));
	temp->data = e;
	temp->next = S->next;
	
	S->next = temp;
	return 1;
}

struct node* pop(struct node* S){
	
	struct node* temp = (struct node*)malloc(sizeof(struct node));	
	if(isEmpty(S) == 0){
		temp = S->next;
		S->next = S->next->next;
		return temp;
	}else{
		return NULL;
	}

}


int main(){
	int temp;
	char c;
	struct node* S = (struct node*) malloc(sizeof(struct node));
	S->next = NULL;
	struct node* out = (struct node*) malloc(sizeof(struct node));
	
	do{
		scanf(" %c", &c);
		
		switch(c){
			case 'p':
				scanf("%d", &temp);
				push(S, temp);
				break;
			case 'q':
				if((out = pop(S)) != NULL){
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


int x = 0;