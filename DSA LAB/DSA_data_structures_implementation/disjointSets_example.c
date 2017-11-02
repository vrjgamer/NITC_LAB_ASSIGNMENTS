#include<stdio.h>
#include<stdlib.h>

struct NODE{
	int rank;
	int data;
	struct NODE* parent;
};

struct DISJOINTSET{
	struct NODE** set;	
	int findOperations;
};

void makeSet(struct DISJOINTSET* S, int x){
	struct NODE* temp = (struct NODE*) malloc(sizeof(struct NODE));
	temp->rank = 0;
	temp->data = x;
	temp->parent = temp;
	
	if(S->set[x] == NULL){
		S->set[x] = temp;
	}else{
		printf("PRESENT\n");
	}
}

struct NODE* findSet_simple(struct DISJOINTSET* S, int x){
	
	S->findOperations++;
	if(S->set[x] != NULL){
		if(S->set[x]->parent == S->set[x]){
			return S->set[x]->parent;
		}else{
			return findSet_simple(S->set[x]->parent);
		}
	}else{
		return NULL;
	}
}

struct NODE* Union_simple(struct DISJOINTSET* S, int x, int y){
	struct NODE* xRoot;
	struct NODE* yRoot;
	
	xRoot = findSet_simple(S, x);
	if(xRoot == NULL){
		printf("\aERROR: %d not present\n", x);
		return NULL;
	}
	yRoot = findSet_simple(S, y);
	if(yRoot == NULL){
		printf("\aERROR: %d not present\n", y);
		return NULL;
	}
	
	xRoot->parent = yRoot;
	return yRoot;
}