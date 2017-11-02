#include<stdio.h>
#include<stdlib.h>

int findSet1 = 0, findSet2 = 0, findSet3 = 0, findSet4 = 0;

struct NODE{
	int rank;
	int data;
	struct NODE *parent;
}*Type1[10000], *Type2[10000], *Type3[10000], *Type4[10000];


//make set for all
int makeSet(int x){
	struct NODE *temp1 = (struct NODE*)malloc(sizeof(struct NODE));
	temp1->rank = 0;
	temp1->data = x;
	temp1->parent = temp1;

	struct NODE *temp2 = (struct NODE*)malloc(sizeof(struct NODE));
	temp2->data = x;
	temp2->parent = temp2;
	temp2->rank = 0;

	struct NODE *temp3 = (struct NODE*)malloc(sizeof(struct NODE));
	temp3->data = x;
	temp3->parent = temp3;
	temp3->rank = 0;

	struct NODE *temp4 = (struct NODE*)malloc(sizeof(struct NODE));
	temp4->data = x;
	temp4->parent = temp4;
	temp4->rank = 0;

	if(Type1[x] == NULL){
        Type1[x] = temp1;
        Type2[x] = temp2;
        Type3[x] = temp3;
        Type4[x] = temp4;
        printf("%d\n",temp1->data);
	}else{
         printf("PRESENT\n");
         return 1;
	}
	return 1;
}


//1. Simple operations
struct NODE* find_simple(int x){
	findSet1++;
	if(Type1[x] != NULL){
		if(Type1[x]->parent == Type1[x]){
			return Type1[x]->parent;
		}else{
			return find_simple(Type1[x]->parent->data);
		}
	}else{
		return NULL;
	}
}

struct NODE* Union_simple(int y, int x){
	struct NODE* xRoot;
	struct NODE* yRoot;
	xRoot = find_simple(x);
	if(xRoot == NULL){
		printf("ERROR ");
		return NULL;
	}
	yRoot = find_simple(y);
	if(yRoot == NULL){
		printf("ERROR ");
		return NULL;
	}
	xRoot->parent = yRoot;

	return yRoot;
}

//2. union rank
struct NODE* find_by_rank(int x){
	findSet2++;
	if(Type2[x] != NULL){
		if(Type2[x]->parent == Type2[x]){
			return Type2[x]->parent;
		}else{
			return find_by_rank(Type2[x]->parent->data);
		}
	}else{
		return NULL;
	}
}

struct NODE* Union_by_rank(int x, int y){
	struct NODE* xRoot;
	struct NODE* yRoot;

	xRoot = find_by_rank(x);
	if(xRoot == NULL){
		printf("ERROR ");
		return NULL;
	}
	yRoot = find_by_rank(y);
	if(xRoot == NULL){
		printf("ERROR ");
		return NULL;
	}
	if(xRoot == yRoot){
		//belong to same set
		return xRoot;
	}
	if(xRoot->rank < yRoot->rank){
		xRoot->parent = yRoot;
		return yRoot;
	}else if(yRoot->rank > yRoot->rank){
		yRoot->parent = xRoot;
		return xRoot;
	}else{
		yRoot->parent = xRoot;
		xRoot->rank++;
		return xRoot;
	}
}

//3. path compression
struct NODE* find_path_compression(int x){
	findSet3++;
	if(Type3[x] != NULL){
		if(Type3[x]->parent != Type3[x]){
			Type3[x]->parent = find_path_compression(Type3[x]->parent->data);
		}else{
			return Type3[x]->parent;
		}
	}else{
		return NULL;
	}
}

struct NODE* Union_path_compression(int y, int x){
	struct NODE* xRoot;
	struct NODE* yRoot;
	xRoot = find_path_compression(x);
	if(xRoot == NULL){
		printf("ERROR ");
		return NULL;
	}
	yRoot = find_path_compression(y);
	if(yRoot == NULL){
		printf("ERROR ");
		return NULL;
	}
	xRoot->parent = yRoot;
	return	yRoot;
}


//4. path compression with rank
struct NODE* find_path_rank(int x){
	findSet4++;
	if(Type4[x] != NULL){
		if(Type4[x]->parent != Type4[x]){
			Type4[x]->parent = find_path_rank(Type4[x]->parent->data);
		}else{
			return Type4[x]->parent;
		}
	}else{
		return NULL;
	}
}

struct NODE* Union_path_rank(int x, int y){
	struct NODE* xRoot;
	struct NODE* yRoot;

	xRoot = find_path_rank(x);
	if(xRoot == NULL){
		printf("ERROR\n");
		return NULL;
	}
	yRoot = find_path_rank(y);
	if(yRoot == NULL){
		printf("ERROR\n");
		return NULL;
	}
	if(xRoot == yRoot){
		//belong to same set
		return xRoot;
	}
	if(xRoot->rank < yRoot->rank){
		xRoot->parent = yRoot;
		return yRoot;
	}else if(xRoot->rank > yRoot->rank){
		yRoot->parent = xRoot;
		return xRoot;
	}else{
		yRoot->parent = xRoot;
		xRoot->rank++;
		return xRoot;
	}
}

int check_input(float input){
    int temp = (int) input;

    if(((float)temp) != input){
        printf("FLOATING POINT ERROR\n");
        return 0;
    }

    if(temp > 10000 && temp < 0){
        printf("INVALID INPUT\n");
        return 0;
    }

    return 1;

}


int main(){
	char choice;
	float E1, E2;
	int e1, e2;
	struct NODE* temp = (struct NODE*)malloc(sizeof(struct NODE));

	do{
		scanf(" %c", &choice);
		switch(choice){
			case 'm':
				scanf("%f", &E1);
				if(check_input(E1) == 0){
                    return -1;
				}
				e1 = E1;
				if(makeSet(e1) == 0){
                    return -1;
				}
				break;
			case 'f':
				scanf("%f", &E1);
				if(check_input(E1) == 0){
                    return -1;
				}
				e1 = E1;
				if((temp = find_simple(e1)) != NULL){
					printf("%d %d %d %d\n", temp->data, find_by_rank(e1)->data, find_path_compression(e1)->data, find_path_rank(e1)->data);
				}else{
					printf("NOT FOUND\n");
				}
				break;
			case 'u':
				scanf("%f", &E1);
				if(check_input(E1) == 0){
                    return -1;
				}
				e1 = E1;
				scanf("%f", &E2);
				if(check_input(E2) == 0){
                    return -1;
				}
				e2 = E2;
				if((temp = Union_simple(e1, e2)) != NULL){
					printf("%d ", temp->data);
				}
				if((temp = Union_by_rank(e1, e2)) != NULL){
					printf("%d ", temp->data);
				}
				if((temp = Union_path_compression(e1, e2)) != NULL){
					printf("%d ", temp->data);
				}
				if((temp = Union_path_rank(e1, e2)) != NULL){
					printf("%d\n", temp->data);
				}
				break;
			case 's':
				printf("%d %d %d %d\n", findSet1, findSet2, findSet3, findSet4);
				return 0;
			default:
				printf("Invalid Case\n");
				return -1;
		}
	}while(1);
	return 0;
}


