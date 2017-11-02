#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct NODE{
    int data;
    struct NODE *next;
} *GRAPH[10000];

struct node{
	struct NODE* data;
	struct node* next;
};

struct queue{
	struct node* head;
	struct node* tail;
};

int isEmpty_Q(struct queue* Q){
	if(Q->tail == NULL){
		return 1;
	}else {
		return 0;
	}
}

void printList(struct NODE* L){
    if(L != NULL){
        struct NODE* p = L->next;

        while(p != NULL){
           // printf(" %d ", p->data);
            p = p->next;
        }
    }
    return;
}

void enqueue(struct queue* Q, struct NODE* e){

	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->data = e;
	temp->next = NULL;

	if(isEmpty_Q(Q) == 1){
		Q->head = temp;
		Q->tail = temp;
	}else{
		Q->tail->next = temp;
		Q->tail = temp;
	}
	return;
}

struct NODE* dequeue(struct queue* Q){

	struct node* out = (struct node*)malloc(sizeof(struct node));
	if(isEmpty_Q(Q) == 1){
		return NULL;
	}else{
		out = Q->head;
		Q->head = Q->head->next;
		if(Q->tail == out){
			Q->tail = Q->tail->next;
		}
		return out->data;
	}
}


int checked[10000], found = 0;

int CreateGraph(int length){
    int i = 0;

    for(i = 0; i < length; ++i){
        struct NODE *link = (struct NODE*)malloc(sizeof(struct NODE));
        link->data = i;
        link->next = NULL;
        GRAPH[i] = link;
        checked[i] = 0;
        if(linkListTohead(i) == -1){
                return -1;
        }
    }
    return 1;
}

int linkListTohead(int index){
    int i = 0, initializer_list = 0, temp = 0;
    char c;
    struct NODE* pre = (struct NODE*)malloc(sizeof(struct NODE));
    pre = GRAPH[index];
    do{
        c = fgetc(stdin);
        if(initializer_list == 0 && c == '\n'){
            return 1;
        }
        initializer_list = 1;
        if(c == ' ' || c == '\n'){
            struct NODE* k = (struct NODE*)malloc(sizeof(struct NODE));
            k->data = temp;
            k->next = NULL;
            pre->next = k;
            pre = k;
            temp = 0;
        }else if(c >= '0' && c <= '9'){
            temp = (temp * 10) + (((int)c) - 48);
        }else{
            printf("INVALID INPUT\n");
            return -1;
        }
    }while(c != '\n');
}

void initialize_check(){
    int i = 0;
    found = 0;
    for(i =0 ; i < 10000; i++){
        checked[i] = 0;
    }
}

void Do_DFS(int start_index, int key){

    struct NODE* current_element = GRAPH[start_index];
    if(current_element == NULL){
        return;
    }
    if(found == 0){
        printf("%d ", current_element->data);
    }
    checked[current_element->data] = 1;

    while(current_element != NULL){
        if(current_element->data == key){
                found = 1;
                return;
        }
        current_element = current_element->next;
        if(current_element != NULL && checked[current_element->data] == 0){
            Do_DFS(current_element->data, key);
        }
    }
    return;
}

void Do_BFS(int start_index, int key){
    struct NODE* current_element;
    int probe = 1;
    //queue initialized
    struct queue *Q = (struct queue*)malloc(sizeof(struct queue));
    Q->head = NULL;
    Q->tail = NULL;


    initialize_check();
    current_element = GRAPH[start_index];

    enqueue(Q, current_element);
    printf("%d ", current_element->data);
    while(isEmpty_Q(Q) == 0){
        current_element = dequeue(Q);
        if(probe == 1)
            checked[current_element->data] = 1;
        probe = 0;
        struct NODE* crrRoot = (struct NODE*)malloc(sizeof(struct NODE));
        crrRoot = GRAPH[current_element->data];
        while(crrRoot != NULL){
            if(checked[crrRoot->data] == 0){
                    enqueue(Q, crrRoot);
                    checked[crrRoot->data] = 1;
                    printf("%d ", crrRoot->data);
            }
            if(crrRoot->data == key){
                    return;
            }
            crrRoot = crrRoot->next;
        }

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
    int n, x, y;
    char choice[10];
    float N, X, Y;

    scanf("%f",&N);
    fgetc(stdin);
    if((check_input(N) == 0 ) || N == 0){
        if(N == 0){
            printf("INVALID INPUT\n");
        }
        return -1;
    }
    n = (int) N;
    if(CreateGraph(n) == -1){
        return -1;
    }

    do{
        scanf("%s", choice);
        if(strcmp("dfs", choice) == 0){
            initialize_check();
            scanf("%f", &X);
            if(check_input(X) == 0){
                return -1;
            }
            x = (int)X;
            if(x > n-1){
                printf("INVALID INPUT\n");
                return -1;
            }
            scanf("%f", &Y);
            if(check_input(Y) == 0){
                return -1;
            }
            y = (int) Y;
            if(y > n-1){
                printf("INVALID INPUT\n");
                return -1;
            }
            Do_DFS(x, y);
            printf("\n");
        }else if(strcmp("bfs", choice) == 0){
            initialize_check();
            scanf("%f", &X);
            if(check_input(X) == 0){
                return -1;
            }
            x = (int)X;
            if(x > n-1){
                printf("INVALID INPUT\n");
                return -1;
            }
            scanf("%f", &Y);
            if(check_input(Y) == 0){
                return -1;
            }
            y = (int) Y;
            if(y > n-1){
                printf("INVALID INPUT\n");
                return -1;
            }
            Do_BFS(x, y);
            printf("\n");
        }else if(strcmp("stp", choice) == 0){
            return 0;
        }else{
            printf("INVALID INPUT\n");
            return -1;
        }
    }while(1);


    return 0;
}




