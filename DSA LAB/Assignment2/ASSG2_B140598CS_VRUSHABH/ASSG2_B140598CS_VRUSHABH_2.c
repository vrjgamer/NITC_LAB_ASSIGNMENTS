#include<stdio.h>

void getOccurrence(int a[100][100], int n, int m, int k){
	int i, j, count = 0;
	
	for(i = 0 ; i < n; ++i){
		for(j = 0; j < m; ++j){
			if(a[i][j] == k){
				printf("%d  %d\n", i + 1, j + 1);
				count++;
			}
		}
	}
	if(count == 0){
		printf("NOT_FOUND\n");
	}
	return;
}


int main(){
	int i, j, n, m, k;
	int a[100][100];
	
	scanf("%d %d", &n, &m);
	
	if(n >= 2147483648 || m >= 2147483648 || n < 0 || m < 0){
		printf("Please Enter a Valid Input!!\n");
		return -1;
	}
	
	for(i = 0; i < n; ++i){
		for(j = 0; j < m; ++j){
			scanf("%d", &a[i][j]);
		}
	}
	
	scanf("%d", &k);
	
	getOccurrence(a,n,m,k);
	
	return 0;
}