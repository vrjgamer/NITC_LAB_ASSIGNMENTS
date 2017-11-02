#include<stdio.h>
#include<stdlib.h>

int stack1_top = -1;
int stack2_top = -1;

struct treeElement{
	int data;
	struct treeElement* left;
	struct treeElement* right;
}*stack_1[100], *stack_2[100];

int isEmpty_stack_1(){
	if(stack1_top == -1){
		return 1;
	}else{
		return 0;
	}
}

int isEmpty_stack_2(){
	if(stack2_top == -1){
		return 1;
	}else {
		return 0;
	}
}

void push_stack1(struct treeElement* element){
	stack1_top++;
	stack_1[stack1_top] = element;
	return;
}

void push_stack2(struct treeElement* element){
	stack2_top++;
	stack_2[stack2_top] = element;
	return;
}

struct treeElement* pop_stack1(){
	stack1_top--;
	return stack_1[stack1_top + 1];
}
struct treeElement* pop_stack2(){
	stack2_top--;
	return stack_2[stack2_top + 1];
}


//non-recursive methods

void preOrder(struct treeElement* root){
	struct treeElement* temp = (struct treeElement*)malloc(sizeof(struct treeElement));
	
	stack1_top = -1; // initialize stack1
	temp = root;
	if(temp != NULL){
		push_stack1(temp);
		while(isEmpty_stack_1() == 0){
			temp = pop_stack1(); 
			printf("%d ", temp->data);
			if(temp->right != NULL){
				push_stack1(temp->right);
			}
			if(temp->left != NULL){
				push_stack1(temp->left);
			}
		}
	}
	printf("\n\n");
	return;
}

void inOrder(struct treeElement* root){
	struct treeElement* temp = (struct treeElement*)malloc(sizeof(struct treeElement));
	int done = 0;
	stack1_top = -1;//initialize stack1
	temp = root;
	if(temp != NULL){
		while(done == 0){
			if(temp != NULL){
				push_stack1(temp);
				temp = temp->left;
			}else{
				if(isEmpty_stack_1() == 0){
					temp = pop_stack1();
					printf("%d ", temp->data);
					temp = temp->right;
				}else{
					done = 1;
				}
			}
		}
	}
	printf("\n\n");
}


void postOrder(struct treeElement* root){
	struct treeElement* temp = (struct treeElement*)malloc(sizeof(struct treeElement));
	stack1_top = -1; //initialize stack1
	stack2_top = -1; //initialize stack2
	
	temp = root;
	if(temp != NULL){
		push_stack1(temp);
		while(isEmpty_stack_1() == 0){
			temp = pop_stack1();
			push_stack2(temp);
			if(temp->left != NULL){
				push_stack1(temp->left);
			}
			if(temp->right != NULL){
				push_stack1(temp->right);
			}
		}
		while(isEmpty_stack_2() == 0){
			temp = pop_stack2();
			printf("%d ", temp->data);
		}	
	}
	printf("\n\n");
	return;
}

struct treeElement* insert(struct treeElement* root, int element){
	if(root == NULL){
		struct treeElement *new = (struct treeElement*)malloc(sizeof(struct treeElement));
		new->data = element;
		new->left = NULL;
		new->right = NULL;
		return new;
	}else{
		if(root->data < element){
			root->right = insert(root->right, element);
		}else{
			root->left =  insert(root->left, element);
		}
		return root;
	}
}

int main(){
	int temp, choice = 0;
	struct treeElement* root = (struct treeElement*)malloc(sizeof(struct treeElement));
	root = NULL;
	
	do{
		printf("\nEnter choice:\n1. Insert\n2. InOrder\n3. PreOrder\n4. PostOrder\n5. Stop\nChoice: ");
		scanf(" %d", &choice);
		switch(choice){
			case 1:
				scanf("%d", &temp);
				root = insert(root, temp);
				break;
			case 2:
				inOrder(root);
				break;
			case 3:
				preOrder(root);
				break;
			case 4:
				postOrder(root);
				break;
			case 5:
				return 0;
		}
	}while(1);
	
	return 0;
}



