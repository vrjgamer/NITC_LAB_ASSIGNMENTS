#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
	int n;
	char read[100];
	scanf("%s", read);

	if(CheckValid(read) == 1){
		n = atoi(read);
	}else{
		return -1;
	}
	
	return 0;
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