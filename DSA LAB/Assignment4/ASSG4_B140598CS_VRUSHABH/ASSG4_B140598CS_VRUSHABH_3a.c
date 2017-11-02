#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int top;
struct node{
	char element;
	struct node *left;
	struct node *right;
}*S[100];

int isOperator(char a){
	if(a == '+' || a == '-' || a == '/' || a == '*' || a == '^'){
		return 1;
	}else{
		return 0;
	}
}
void InitializeStack(){
	top = -1;
}

int IsEmpty(){
	if(top == -1){
		return 1;
	}else{
		return 0;
	}
}

int push(struct node *element){
	top++;
	S[top] = element;
	return top;	
}

struct node* pop(int element){
	struct node* out = (struct node*)malloc(sizeof(struct node));
	if(IsEmpty() == 1){
		return NULL;
	}else{
		out = S[top];
		top--;
		return S[top + 1];
	}
}



struct node* buildExpTree(char *E){

	struct node *newNode, *leftNode, *rightNode;

	int length = strlen(E), i;	

InitializeStack();

	for(i = length - 1; i >= 0; --i){
		if(isOperator(E[i]) == 1){
			leftNode = pop(top);
			rightNode = pop(top);
			newNode = (struct node*)malloc(sizeof(struct node));
			newNode->element = E[i];
			newNode->left = leftNode;
			newNode->right = rightNode;
			push(newNode);
		}else if(E[i] >= 'a' && E[i] <= 'z'){
			newNode = (struct node*)malloc(sizeof(struct node));
			newNode->element = E[i];
			newNode->left = NULL;
			newNode->right = NULL;
			push(newNode);
		}else{
			printf("Invalid Input\n");
			return;
			}
			
		}
	return pop(top);
	
}

void postOrder(struct node* root){
	if(root == NULL){
		return;
	}else{
		postOrder(root->left);
		postOrder(root->right);
		printf("%c", root->element);
	}
}

void preOrder(struct node* root){
	if(root == NULL){
		return;
	}else{
		printf("%c", root->element);
		preOrder(root->left);
		preOrder(root->right);
	}
}

void inOrder(struct node* root){
	if(root == NULL){
		return;
	}else{
		if(!(root->left == NULL && root->right ==  NULL))
			printf("(");
		if(root->left != NULL)
			inOrder(root->left);
		printf("%c", root->element);
		if(root->right != NULL)
			inOrder(root->right);
		if(!(root->left == NULL && root->right == NULL))
			printf(")");
	}

}



int main(){

	char pre[100];
	scanf("%s", pre);
	struct node* root = (struct node*)malloc(sizeof(struct node));

	root = buildExpTree(pre);
	
	printf("inOrder: ");
		inOrder(root);

	printf("\npreOrder: ");
		preOrder(root);

	printf("\npostOrder: ");
		postOrder(root);

	return 0;

	

}