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


int getLength(struct node* head){
	struct node* p = (struct node*)malloc(sizeof(struct node));
	int length = 0;
	p = head->next;
	while(p != NULL){
		p = p->next;
		length++;
	}
	return length;
}

struct node* k_last(struct node* head, int k){
	int length, i = 0;
	struct node* p = (struct node*)malloc(sizeof(struct node));
	length = getLength(head);

	length = length - k;

	p = head->next;
	while((i < length) && (p != NULL)){
		p = p->next;
		i++;
	}
	if(p != NULL){
		return (p);
	}else{
		return NULL;
	}
}

int main(){
	int n, k;
	
	scanf("%d", &n);
	
	if(n <= 0){
		printf("Invalid Input\n");
		return -1;
	}
	struct node* mList = (struct node*)malloc(sizeof(struct node));
	struct node* k_last_data = (struct node*)malloc(sizeof(struct node));
	
	readList(mList, n);

	
	scanf("%d", &k);
	if(k <= 0){
		printf("Invalid Input\n");
		return -1;
	}
	if(n < k){
		printf("Invalid Input: %d>%d", k, n);
		return -1;
	}
	k_last_data = k_last(mList, k);
	
	if(k_last_data != NULL){
		printf("%d\n", k_last_data->data);
	}else{
		printf("NULL");
	}
	
	return 0;
}
