#include <stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node *next; //self Referencing
};

void printList(struct node *mList){
     struct node *currentnode = (struct node*)malloc(sizeof(struct node));
	 currentnode = mList->next;
     while(currentnode != NULL){
        printf("%d  ",currentnode->data);
        currentnode = currentnode->next;
     }
}

int swap(struct node *head, int x, int y){
	int present_x = 0, present_y = 0;
	if(x == y){
		printf("Same Numbers\n");
		return 0;
	}
	struct node *X = (struct node*)malloc(sizeof(struct node));
	struct node *Y = (struct node*)malloc(sizeof(struct node));
	struct node *p = (struct node*)malloc(sizeof(struct node));
	struct node *X_pre = (struct node*)malloc(sizeof(struct node));
	struct node *Y_pre = (struct node*)malloc(sizeof(struct node));
	
	p = head;
	while(p->next != NULL){
		if(p->next->data == x){
			X_pre = p;
			X = p->next;
			present_x = 1;
		}else if(p->next->data == y){
			Y_pre = p;
			Y = p->next;
			present_y = 1;
		}
		p = p->next;
	}
	if((present_x == 1) && (present_y == 1)){
		struct node *temp = (struct node*)malloc(sizeof(struct node));
		temp = X->next;
		X->next = Y->next;
		Y->next = temp;
		X_pre->next = Y;
		Y_pre->next = X;
		return 1;
	}else{ 
		if(present_x == 0){
			printf("%d not found\n", x);
		}
		if(present_y == 0){
			printf("%d not found\n", y);
		}
		return 0;
	}
}

void readList(struct node* head, int length){
	struct node *cast = (struct node*)malloc(sizeof(struct node));
	int i = 0, temp_data;
	
	head->next = NULL;
	while(i < length){
		struct node* temp = (struct node*)malloc(sizeof(struct node));
		scanf("%d", &temp_data);
		temp->data = temp_data;
		temp->next = NULL;
		if(head->next == NULL){
			head->next = temp;	
		}else{
			cast->next = temp;
		}
		cast = temp;
		i++;
	}
	cast->next = NULL;	
	return;
}


int main(){
	struct node *mList = (struct node*)malloc(sizeof(struct node));
	int n, x, y;
	
	scanf("%d", &n);
	
	if(n <=0){
		printf("Invalid Input\n");
		return -1;
	}
	
	mList->next = NULL;
	
	readList(mList, n);
	
	scanf("%d", &x);
	
	scanf("%d", &y);
	
	if(swap(mList, x, y) == 1){
		printList(mList);
		return 0;
	}
	return -1;
}
