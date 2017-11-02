#include<stdio.h>


void Merge(int *a, int top, int mid, int bottom){
	int b[top];
	int i, j, h, k;
	i = bottom;
	h = bottom;
	j = mid + 1;

	while((h <= mid) && (j <= top)){
		if(a[h] <= a[j]){
			b[i] = a[h];
			h++;
		}else{
			b[i] = a[j];
			j++;
		}
		i++;
	}
	if(h > mid){
		for(k = j; k <= top; ++k){
			b[i] = a[k];
			i++;
		}
	}else{
		for(k = h; k <= mid; ++k){
			b[i] = a[k];
			i++;
		}
	}
	for(i = bottom; i <= top; ++i){
		a[i] = b[i];
	}
	
	return;
}


void MergeSort(int *a,int top, int bottom){
	int mid;
	if(bottom < top){
		mid = (top + bottom) / 2;
		MergeSort(a, top, mid + 1);
		MergeSort(a, mid, bottom);
		
		Merge(a, top, mid, bottom);
	}
	
	return;
}

int main(){
	int n, i = 0;
	int a[10000];
	
	FILE *pFile = fopen("NUMBERS.txt", "r");
	FILE *pOutput = fopen("OUTPUT.txt", "w");
	
	while(!feof(pFile)){
		if(i >= 10000){
			printf("Number of entries is out of range!!");
			return -1;
		}
		fscanf(pFile,"%d", &a[i]);
		if(feof(pFile)){
			break;
		}
		i++;
		
	}
	n = i;
	
	MergeSort(a, n - 1, 0);
	
	for(i = 0; i < n; ++i){
		fprintf(pOutput, "%d\n", a[i]);
	}
	
	return 0;
}

