#include<stdio.h>

struct student{
	int MARK;
	char NAME[50];
	char ROLLNO[10];
};

int partition(struct student *a, int upper, int lower){
	struct student temp;
	int key = a[upper - 1].MARK;
	int position = lower, j;
	for(j = lower; j < upper; ++j){
		if(a[j].MARK < key){
			temp = a[j];
			a[j] = a[position];
			a[position] = temp;
			position++;
		}
	}
	temp = a[upper - 1];
	a[upper - 1] = a[position];
	a[position] = temp;
	return position;
}

void QuickSort(struct student *a, int upper, int lower){
    int index;
    if(lower < upper){
        index = partition(a, upper, lower);
        QuickSort(a, index - 1, lower);
        QuickSort(a, upper, index + 1);
    }
    	
	
    return;
}

void printList(struct student *a, int length){
	int i = 0;
		
	for(i = length - 1; i >= 0; --i){
		printf("%s %s %d\n", a[i].ROLLNO, a[i].NAME, a[i].MARK);
	}
	return;
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
		scanf("%s%s%d", a[i].ROLLNO, a[i].NAME, &a[i].MARK);
	}
	
	QuickSort(a, n, 0);
	
	printList(a, n);
	return 0;
}