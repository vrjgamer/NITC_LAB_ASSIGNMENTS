#include<stdio.h>

int Merge(int *a, int top, int mid, int bottom){
	int b[top], count = 0;
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
			count++;
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
			count++;
			i++;
		}
	}
	for(i = bottom; i <= top; ++i){
		a[i] = b[i];
	}
	
	return count;
}



int SearchReversePair(int *a, int bottom, int top){
	int mid;
	if(bottom < top){
		mid = (top + bottom) / 2;
		return SearchReversePair(a, mid + 1, top) + SearchReversePair(a, bottom, mid) + Merge(a, top, mid, bottom);
	}
	return 0;

}



int main(){
	int i, n, result;
	int a[1000];
	scanf("%d", &n);

	if(n >= 2147483648 || n < 0){
		printf("Please Enter a Valid Input!!\n");
		return -1;
	}

	for(i = 0; i < n; ++i){
		scanf("%d", &a[i]);
	}
	
	printf("%d\n",SearchReversePair(a, 0, n - 1));
	
	return 0;
}







