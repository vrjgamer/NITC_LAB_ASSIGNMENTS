#include<stdio.h>
#include<string.h>

int checkAnagram(char str1[],char str2[]){
	
	int i=0,j=0;
	int freq[256] = {0}; 
	
	for(i =0; i < strlen(str1); ++i){
		freq[str1[i]]++;
	}
	
	for (i=0; i < strlen(str2); ++i){
		freq[str2[i]]--;
	}

	for(i=0; i < 256; i++){
		if(freq[i] !=0){
			return 0;		
		}		
	}

	return 1;
}

int main(){
	char string1[50],string2[50];
	int check = 0;
	printf("Enter str1: ");
	scanf("%s",string1);
	
	printf("Enter str2: ");
	scanf("%s",string2);

	if(strlen(string1) == strlen(string2)){
		check = checkAnagram(string1,string2);
	}else {
		check = 0;	
	}	

	if(check != 1){
		printf("NO\n");
	}else {
		printf("YES\n");		
	}

return 0;
}