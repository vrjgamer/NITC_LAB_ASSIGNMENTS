#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int root = 0;
struct BST{
	int value;
	struct BST *left;
	struct BST *right;
	struct BST *parent;
};

void initializeBST(struct BST *B){
	B = (struct BST*)malloc(sizeof(struct BST));
	B=NULL;
	return;
}

void inorder(struct BST *B){
	if(B == NULL){
		return;
	}else{
		inorder(B->left);
		printf("%d ",B->value);
		inorder(B->right);
	}
}

void preorder(struct BST *B){
	if(B == NULL){
		return;
	}else{
		printf("%d ", B->value);
		preorder(B->left);
		preorder(B->right);
	}
}

void postorder(struct BST *B){
	if(B == NULL){
		return;
	}else{
		postorder(B->left);
		postorder(B->right);
		printf("%d ", B->value);
	}
}

struct BST* findMax(struct BST *B){
	if(B != NULL){
		if(B->right == NULL){
			return B;
		}else{
			return findMax(B->right);
		}
	}else{
		return NULL;
	}
}

struct BST* findMin(struct BST *B){
	if(B != NULL){
		if(B->left == NULL){
			return B;
		}else{
			return findMin(B->left);
		}
	}else{
		return NULL;
	}
}

struct BST* insert(struct BST* B, int element){
	if(B == NULL){
		struct BST *new = (struct BST*)malloc(sizeof(struct BST));
		new->value = element;
		new->left = NULL;
		new->right = NULL;
		if(root == 0){
			new->parent = NULL;
			root = 1;
		}else{
			new->parent = B;
		}
		return new;
	}else{
		if(B->value < element){
			B->right = insert(B->right, element);
			B->right->parent = B;
		}else{
			B->left =  insert(B->left, element);
			B->left->parent = B;
		}
		return B;
	}
}

struct BST* search(struct BST* B, int element){
	if(B == NULL){
		printf("NOT FOUND\n");
		return NULL;
	}else{
		if(B->value == element){
			printf("FOUND\n");
			return B;
		}else if(B->value < element){
			search(B->right, element);
		}else{
			search(B->left, element);
		}
	}
}

struct BST* predecessor(struct BST* B){
	if(B == NULL){
		return NULL;
	}else{
		if(B->left == NULL){
			struct BST* temp = (struct BST*)malloc(sizeof(struct BST));
			temp = B->parent;
			while(temp!= NULL || B == temp->left){
				B = temp;
				temp = temp->parent;
			}
			return temp;
		}else{
			return findMax(B->left);
		}
	}
}

struct BST* successor(struct BST* B){
	if(B == NULL){	
		return NULL;
	}else{
		if(B->right == NULL){
			struct BST* temp = (struct BST*)malloc(sizeof(struct BST));
			temp = B->parent;
			while(temp!= NULL || B == temp->right){
				B = temp;
				temp = temp->parent;
			}
			return temp;
		}else{
			return findMin(B->right);
		}
	}
}

struct BST* delete(struct BST* B,int element){
	if(B == NULL){
		printf("element not found\n");
		return NULL;
	}else{
		if(B->value == element){
			if((B->left == NULL) && (B->right == NULL)){
				if(B->parent->right->value == B->value){
					B->parent->right = NULL;
				}else if(B->parent->left->value == B->value){
					B->parent->left = NULL;
				}
			}else if((B->left == NULL) && (B->right != NULL)){
				B = B->right;
			}else if((B->right == NULL) && (B->left != NULL)){
				B = B->left; 
			}else{
				int f = findMax(B)->value;
				B->value = f;
				delete(B->right, f);
			}
		}else if(B->value < element){
			B->right = delete(B->right, element);
		}else{
			B->left = delete(B->left, element);
		}
		return B;
	}
}

int CheckValid(char *read){
	int length = strlen(read), i = 0, value;
	
	for(i = 0; i < length; i++){
		if(read[i] == '.'){
			printf("Invalid Input, Floating Point Number\n");
			return -1;		
		}
	}	
		
	if(strcmp(read, "2147483648") >= 0 || strcmp(read, "0") < 0){
		printf("Invalid Input\n");
		return -1;	
	}else{
		return 1;
	}
}

int main(){
	int temp;
	struct BST *B;
	char choice[10];
	initializeBST(B);
	char read[100];
	scanf("%s", read);

	if(CheckValid(read) == 1){
		n = atoi(read);
	}else{
		return -1;
	}
	
	do{
		scanf(" %s", choice);
		if(strcmp(choice, "insr") == 0){
			scanf("%s", read);
			if(CheckValid(read) == 1){
				temp = atoi(read);
				B = insert(B, temp);
			}else{
				return -1;
			}
		}else if(strcmp(choice,"srch") == 0){
			scanf("%s", read);
			if(CheckValid(read) == 1){
				temp = atoi(read);
				search(B, temp);
			}else{
				return -1;
			}
		}else if(strcmp(choice, "minm") == 0){
			struct BST *T = (struct BST*)malloc(sizeof(struct BST));
			if((T = findMin(B)) != NULL && (root != 0)){
				printf("%d\n", T->value);
			}else{
				printf("NIL\n");
			}
		}else if(strcmp(choice, "maxm") == 0){
			struct BST *T = (struct BST*)malloc(sizeof(struct BST));
			if((T = findMax(B)) != NULL && (root != 0)){
				printf("%d\n", T->value);
			}else{
				printf("NIL\n");
			}
		}else if(strcmp(choice, "pred") == 0){
			struct BST *T = (struct BST*)malloc(sizeof(struct BST));
			scanf("%s", read);
			if(CheckValid(read) == 1){
				temp = atoi(read);
				if((T = predecessor(search(B, temp))) != NULL && (root != 0)){
				printf("%d\n", T->value);
			}else{
				printf("NIL\n");
			}
			}else{
				return -1;
			}
			
		}else if(strcmp(choice, "succ") == 0){
			struct BST *T = (struct BST*)malloc(sizeof(struct BST));
			scanf("%s", read);
			if(CheckValid(read) == 1){
				temp = atoi(read);
				if((T = successor(search(B, temp))) != NULL && (root != 0)){
				printf("%d\n", T->value);
				}else{
					printf("NIL\n");
				}
		}else if(strcmp(choice, "delt") == 0){
			scanf("%s", read);
			if(CheckValid(read) == 1){
				temp = atoi(read);
				delete(B, temp);
			}else{
				return -1;
			}
		}else if(strcmp(choice, "inor") == 0){
			inorder(B);
		}else  if(strcmp(choice, "prer") == 0){
			preorder(B);
		}else  if(strcmp(choice, "post") == 0){
			postorder(B);
		}else if(strcmp(choice, "stop") == 0){
			return 0;
		}else{
			printf("Invalid case\n");
			return -1;
		}
	}while(1);
	
	return 0;
}
