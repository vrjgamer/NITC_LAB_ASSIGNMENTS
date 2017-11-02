#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int top, t, j;
struct node{
	char element;
	struct node *left;
	struct node *right;
}*S[100], *stack[100], *holder[100];

int isOperator(char a){
	if(a == '+' || a == '-' || a == '/' || a == '*' || a == '^'){
		return 1;
	}else{
		return 0;
	}
}
void InitializeStack(){
	top = -1;
	t = -1;
	j = -1;
}

int IsEmpty(int which){

	if(which == 0){
		if(top == -1){
			return 1;
		}else{
			return 0;
		}
	}else if(which == 1){
		if(t == -1){
			return 1;
		}else{
			return 0;
		}
	}else if(which == 2){
		if(j == -1){
			return 1;
		}else{
			return 0;
		}
	}
}

int push(struct node *element, int which){
	if(which == 0){
		top++;
		S[top] = element;
		return top;
	}else if(which == 1){
		t++;
		stack[t] = element;
		return t;
	}else if(which == 2){
		j++;
		holder[j] = element;
		return j;
	}
}

struct node* pop(int which){
	struct node* out = (struct node*)malloc(sizeof(struct node));
	if(IsEmpty(which) == 1){
		return NULL;
	}else{

		switch(which){
		case 0:
			out = S[top];
			top--;
			return S[top + 1];
		case 1:
			out = stack[t];
			t--;
			return stack[t + 1];
		case 2:
			out = holder[j];
			j--;
			return holder[j + 1];
		}
	}
	return NULL;
}

struct node* buildExpTree(char *E){
	struct node *newNode, *leftNode, *rightNode;
	int length = strlen(E), i;	

	InitializeStack();
	for(i = length - 1; i >= 0; --i){
		if(isOperator(E[i]) == 1){
			leftNode = pop(0);
			rightNode = pop(0);
			newNode = (struct node*)malloc(sizeof(struct node));
			newNode->element = E[i];
			newNode->left = leftNode;
			newNode->right = rightNode;
			push(newNode, 0);
		}else if(E[i] >= 'a' && E[i] <= 'z'){
			newNode = (struct node*)malloc(sizeof(struct node));
			newNode->element = E[i];
			newNode->left = NULL;
			newNode->right = NULL;
			push(newNode, 0);
		}else{
			printf("Invalid Input\n");
			return;
		}		
	}
	return pop(0);
}

void postOrder(struct node* root){
	InitializeStack();
	if(root == NULL){

		return;
	}
	struct node* p =(struct node*)malloc(sizeof(struct node));
	p = root;

	push(p, 1);
	while(IsEmpty(1) == 0){
		p = pop(1);
		push(p, 2);
		if(p->left != NULL)
		  push(p->left, 1);
		if(p->right != NULL)
		  push(p->right, 1);
	    }
	while(IsEmpty(2) == 0){
	    	p = pop(2);
		printf("%c",p->element);
	    }
	
}

void preOrder(struct node* root){
	struct node* p =(struct node*)malloc(sizeof(struct node));
	InitializeStack();
	if(root != NULL){
		push(root, 0);
		while(IsEmpty(0) == 0){
			p = pop(0);
			printf("%c", p->element);
			if(p->right != NULL){
				push(p->right, 0);
			}
			if(p->left != NULL){
				push(p->left, 0);
			}
		}
	}
	return;
}

void inOrder(struct node* root){
	struct node* p =(struct node*)malloc(sizeof(struct node));
	int done = 0, right = 0, left = 0;
 	p = root;
	InitializeStack();
	if(p != NULL){
		while(done == 0){
			if(p != NULL){
				push(p, 0);
				p = p->left;									
			}else{
				if(IsEmpty(0) == 0){
					p = pop(0);
					printf("%c", p->element);
					p = p->right;
				}else{
					done = 1;	
				}
			}
		
		}
	}
	return;
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