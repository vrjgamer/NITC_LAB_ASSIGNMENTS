#include<stdio.h>
#include<string.h>


void SelectionSort(char a[100][15], int n){
	int i, j, index;
	char temp[100];
	for(i = 0; i < n; ++i){
		index = i;
		for(j = i + 1; j < n; ++j){
			if(strcmp(a[j],a[index]) < 0){
				index = j;
			}
		}
		
		strcpy(temp, a[index]);
		strcpy(a[index], a[i]);
		strcpy(a[i], temp);
	}
	
	return;
}

void printList(char a[100][15], int length){
	int i;
	for(i= 0; i < length; ++i){
		printf("%s ", a[i]);
	}
	return;
}

int ValidateInput(char a[100][15], int n){
	int i, j;
	for(i = 0; i < n; ++i){
		if(strlen(a[i]) > 11){
			return 0;
		}
	}
	
	for(i = 0; i < n; ++i){
		for(j = 0; j < strlen(a[i]); ++j){
			if(a[i][j] >= 'A' && a[i][j] < 'Z'){
				return 0;
			}
		}
	}
	
	return 1;
}

int main(){
	int i, n;
	char a[100][15];
	scanf("%d", &n);
	if(n >= 2147483648 || n < 0){
		printf("Please Enter a Valid Input!!\n");
		return -1;
	}
	for(i = 0; i < n ; ++i){
		scanf("%s",a[i]);
	}
	if(ValidateInput(a, n) == 0){
		printf("Invalid Inputs Entered!!\n");
		return -1;
	}
	SelectionSort(a, n);
	printList(a, n);
	
	return 0;
}