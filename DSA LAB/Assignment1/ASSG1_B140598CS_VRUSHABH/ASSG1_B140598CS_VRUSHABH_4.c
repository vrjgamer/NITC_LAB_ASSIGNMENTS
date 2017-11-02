#include<stdio.h>
#include<math.h>

int ValidateElement(int a[100][100],int n, int i,int j){
	if(i < 0 || j < 0 || i > n || j > n){
		return 0;
	}else{
		return a[i][j];
	}
}

int filterMatrix(int a[100][100], int n, int i, int j){

	int divide = 9,k=0,h =0;
    float sum =0;

	if((i == 0 && j == 0) || (i == (n - 1) && j == 0) || (i == 0 && j == (n - 1)) || (i == (n - 1) && j == (n - 1))){
		divide = 4;
	}else if( (j == 0) || (j == n-1) || (i == 0) || (i == n-1)){
		divide = 6;
	}

	for(h = i + 1; h >= i - 1 ; --h){
		for(k =j + 1; k >= j - 1; --k){
			sum += ValidateElement(a,n,h,k);
		}
	}

	return (int)(round(sum / divide));
}


int main(){
	int i = 0,j = 0,n;
    int m[100][100],a[100][100];

	scanf("%d",&n);

	for(i = 0;i < n; ++i){
		for(j = 0;j < n; ++j){
			scanf("%d",&m[i][j]);
		}
	}
    printf("\n");

	for(i = 0; i < n; ++i){
		for(j = 0;j < n; ++j){
			a[i][j] = filterMatrix(m,n,i,j);
            printf("%d\t",a[i][j]);
		}
        printf("\n");
	}

	return 0;
}
