#include<stdio.h>

struct student{
	int MARK;
	char NAME[50];
	char ROLLNO[10];
};

void sortAtRadix(struct student *a, int n, int position){
	struct student output[n];
	int i, count[256] = {0};
	
	for(i = 0; i < n; ++i){
		count[a[i].ROLLNO[position]]++;
	}
	
	for(i = 1; i < 256; ++i){
		count[i] = count[i] + count[i - 1]; 
	}

	for(i = n - 1; i >= 0; --i){
		output[count[a[i].ROLLNO[position]]-1] = a[i];
		count[a[i].ROLLNO[position]]--;
	}
	
	for(i = 0; i < n; ++i){
		a[i] = output[i];
	}
	return;
}

void RadixSort(struct student *a, int n){
	int i;
	for(i = 8; i >= 0; --i){
		sortAtRadix(a, n, i);
	}
}


void printList(struct student *a, int length){
    int i=0;
	
	for(i = 0; i < length; ++i){
		printf("%s %s %d\n", a[i].ROLLNO, a[i].NAME, a[i].MARK);
	}
	return;
}

int CheckRollno(struct student *a, int n){
	int i = 0, currentLen, j = 0;
	
	for(i = 0; i < n; ++i){
		currentLen = 0;
		j = 0;
		while(a[i].ROLLNO[j] != '\0'){
			currentLen++;
			j++;
		}
		if(currentLen > 9){
			return 0;
		}
	}
	
	return 1;
	
}
int main(){
	struct student a[100];
	int n, i;
	
	scanf("%d", &n);
	
	if(n >= 2147483647 || n < 0){
		printf("Please Enter a Valid Input!!\n");
		return -1;
	}
	
	for(i = 0; i < n; ++i){
		scanf("%s %s %d", a[i].ROLLNO, a[i].NAME, &a[i].MARK);
	}
	
	if(CheckRollno(a, n)==0){
		printf("Invalid Roll number!!\n");
		return -1;
	}
	
    RadixSort(a, n);
	
	printList(a, n);
	return 0;
}