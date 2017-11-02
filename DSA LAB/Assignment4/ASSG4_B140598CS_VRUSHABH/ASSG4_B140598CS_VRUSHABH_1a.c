#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int element_count;

struct hash_element{
	int key_field;
	struct hash_element* next;
};

struct HashTable{
	struct hash_element* head;
}H[100];

void initializeHT(int total){
 	int i = 0;
	for(i = 0; i < total; ++i){
		H[i].head = NULL;
	}
	element_count = total;
}

int getIndexFromHash(int total, int key){
	if(key >= 0){
	return (key % total);
	}else{
		return (total + (key % total)) % total ;
	}
}

int insert(int element){
	int index = getIndexFromHash(element_count, element);
	struct hash_element* newNode = (struct hash_element*)malloc(sizeof(struct hash_element));
	newNode->key_field = element;
	newNode->next = NULL;
	if(H[index].head == NULL){
		H[index].head = newNode;
	}else{
		newNode->next = H[index].head;
		H[index].head = newNode;
	}
	printf("%d\n",index);
	return 1;
}

void search(int element){
	int index = getIndexFromHash(element_count, element);
	struct hash_element* p = (struct hash_element*)malloc(sizeof(struct hash_element));
	p = H[index].head;
	while(p != NULL){
		if(p->key_field == element){
			printf("%d FOUND\n", index);
			return;
		}
		p = p->next;
	}
	printf("%d  NOT FOUND\n", index);
	return;
}

int CheckValid(char *read){
	int length = strlen(read), i = 0, value;	
	for(i = 0; i < length; i++){
		if(read[i] == '.'){
			printf("Invalid Input, Floating Point Number\n");
			return -1;		
		}
	}	
		
	if(strcmp(read, "2147483648") >= 0){
		printf("Invalid Input\n");
		return -1;	
	}else{
		return 1;
	}
}


int main(){
	int value, total_element;
	char choice;
	char read[100];
	scanf("%s", read);

	if(CheckValid(read) == 1){
		total_element = atoi(read);
		if(total_element < 0){
			printf("Invalid Input\n");
			return -1;
		}
	}else{
		return -1;
	}

	initializeHT(total_element);

	do{
		scanf(" %c", &choice);
		switch(choice){
			case 'i':
				scanf("%s", read);
				if(CheckValid(read) == 1){
					value = atoi(read);
					insert(value);
				}else{
					return -1;
				}
				break;
			case 'f':
				scanf("%s", read);
				if(CheckValid(read) == 1){
					value = atoi(read);

					search(value);
				}else{
					return -1;
				}
				break;
			case 's':
				choice = 's';
				return 0;
				break;
			default: 
				printf("Invalid Input\n\a");
				return -1;
		}
	}while(choice != 's');
	return 0;

}

