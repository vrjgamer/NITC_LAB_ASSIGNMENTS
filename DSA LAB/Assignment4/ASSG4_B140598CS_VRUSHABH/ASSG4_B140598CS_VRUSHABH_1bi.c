#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int total_element;

struct HT{
	int value;
	int used;
};

void initializeHT(int total){
	total_element = total;
}

int hashingindex(int key, int total, int probe){
	if(key > 0){
		return (((key % total) + probe) % total);
	}else{
		return (total + (((key % total) + probe) % total));
	}
}

int insert(struct HT* HashTable, int element){
	int probe = 0,index = hashingindex(element, total_element, probe);
	
	while((HashTable[index].used != 0) && probe < total_element){
		index = hashingindex(element, total_element, ++probe);
	}
	
	if(probe == total_element){
		printf("CANNOT INSERT\n");
		return -1;
	}else{
		HashTable[index].value = element;
		HashTable[index].used = 1;
		printf("%d\n", index);
		return 1;
	}	
}

int search(struct HT* HashTable, int element){
	int probe = 0,index = hashingindex(element, total_element, probe);

	while((HashTable[index].value != element) && probe < total_element && (HashTable[index].used != 0)){
		printf("%d ", index);
		index = hashingindex(element, total_element, ++probe);
	}
	
	if(probe == total_element || (HashTable[index].used == 0)){
		printf("%d NOT FOUND\n", index);
		return -1;
	}else{
		printf("%d FOUND\n", index);
		return 1;
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
		
	if(strcmp(read, "2147483648") >= 0){
		printf("Invalid Input\n");
		return -1;	
	}else{
		return 1;
	}
}

int main(){
	int value, total, i;
	char choice;
	struct HT *HashTable;
	char read[100];
	scanf("%s", read);
	if(CheckValid(read) == 1){
		total = atoi(read);
		if(total < 0){
			printf("Invalid Input\n");
			return -1;
		}
	}else{
		return -1;
	}
	
	HashTable = (struct HT*)malloc(total * sizeof(struct HT));
	
	for(i = 0; i < total; ++i){
		HashTable[i].used = 0;
	}

	initializeHT(total);
	
	do{
		scanf(" %c", &choice);
		switch(choice){
			case 'i':
				scanf("%s", read);
				if(CheckValid(read) == 1){
					value = atoi(read);
					insert(HashTable, value);
				}else{
					return -1;
				}
				
				break;
			case 'f':
				scanf("%s", read);
				if(CheckValid(read) == 1){
					value = atoi(read);
					search(HashTable, value);
				}else{
					return -1;
				}
				break;
			case 's':
				choice = 's';
				return 0;
				break;
			default: 
				printf("invalid operator\n\a");
				return -1;
		}
	}while(choice != 's');
	
	return 0;
}

