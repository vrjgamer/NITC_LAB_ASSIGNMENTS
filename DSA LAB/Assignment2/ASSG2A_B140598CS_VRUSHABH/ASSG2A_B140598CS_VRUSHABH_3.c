#include<stdio.h>
#include<stdlib.h>
#include<time.h>

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

int getMinPos(int *a, int length){
	int min = a[0], i, pos = 0;
	for(i = 0; i < length; ++i)
	{
		if((a[i] <= min) && (a[i] != -1)){
			pos = i;
			min = a[i];
		}
	}
	
	return pos;
}

void eightwayMerge(){
	int i, current = 0, j = 0, min = 0;
	char file[8][20], outputFileName[20];
	int a[8] = {0};

	FILE *f[8];
	FILE *output;	
	for(i = 1; i <= 8; ++i){
		printf("Writing File %d out of 8\n", i);
		sprintf(outputFileName, "8-part%d.txt", i);
		output = fopen(outputFileName, "w");
		for(j = 0; j < 8; j++){
		sprintf(file[j], "64-part%d.txt", j + current + 1);
		f[j] = fopen(file[j], "r");
		}
		current = current + 8;
		
		for(j = 0; j < 8; ++j){
			fread(&a[j], sizeof(int), 1, f[j]);

		}		

		while(!feof(f[0]) && !feof(f[1]) && !feof(f[2]) && !feof(f[3]) && !feof(f[4]) && !feof(f[5]) && !feof(f[6]) && !feof(f[7])){
			min = getMinPos(a, 8);
			fwrite(&a[min], sizeof(int), 1, output);
			//fprintf(output, "%d\n", a[min]);
			if(!feof(f[min])){
				fread(&a[min], sizeof(int), 1, f[min]);
			}else{
				a[min] = -1;
			}
		}
		
		for(j = 0; j < 8; ++j){
			fclose(f[j]);
			remove(file[j]);	
		}
		
		fclose(output);		
	}	
	
	return;
}

void fourwayMerge(){
	int i, current = 0, j = 0, min = 0;
	char file[4][20], outputFileName[20];
	int a[4] = {0};
	FILE *f[4];
	FILE *output;	
	for(i = 1; i <= 2; ++i){
		printf("Writing File %d out of 2\n", i);
		sprintf(outputFileName, "4-part%d.txt", i);
		output = fopen(outputFileName, "w");
		for(j = 0; j < 4; j++){
		sprintf(file[j], "8-part%d.txt", j + current + 1);
		f[j] = fopen(file[j], "r");
		}
		current = current + 4;
		
		for(j = 0; j < 4; ++j){
			fread(&a[j], sizeof(int), 1, f[j]);

		}		

		while(!feof(f[0]) && !feof(f[1]) && !feof(f[2]) && !feof(f[3])){
			min = getMinPos(a, 4);
			fwrite(&a[min], sizeof(int), 1, output);
			//fprintf(output, "%d\n", a[min]);
			if(!feof(f[min])){
				fread(&a[min], sizeof(int), 1, f[min]);
			}else{
				a[min] = -1;
			}
		}
		
		for(j = 0; j < 4; ++j){
			fclose(f[j]);
			remove(file[j]);	
		}
		
		fclose(output);		
	}	
	return;
}

void twowayMerge(){
	int i, current = 0, j = 0, min = 0;
	char file[2][20], outputFileName[20];
	int a[2] = {0};
	FILE *f[2];
	FILE *output;	
		printf("Writing File %d out of 1\n", 1);
		sprintf(outputFileName, "output.txt");
		output = fopen(outputFileName, "w");
		for(j = 0; j < 2; j++){
		sprintf(file[j], "4-part%d.txt", j + current + 1);
		f[j] = fopen(file[j], "r");
		}
		current = current + 2;
		
		for(j = 0; j < 2; ++j){
			fread(&a[j], sizeof(int), 1, f[j]);

		}		

		while(!feof(f[0]) && !feof(f[1])){
			min = getMinPos(a, 2);
			fwrite(&a[min], sizeof(int), 1, output);
			//fprintf(output, "%d\n", a[min]);
			if(!feof(f[min])){
				fread(&a[min], sizeof(int), 1, f[min]);
			}else{
				a[min] = -1;
			}
		}
		
		for(j = 0; j < 2; ++j){
			fclose(f[j]);
			remove(file[j]);
		}
		
		fclose(output);		
	
	return;
}

int main(){
	int i = 0, input,j, choice = 0, numbercount, k = 1, r = 0;
	int a[1000000];
	char fileName[15];
	int NumberLimit = (256 * 1000 * 1000) / sizeof(int);

	FILE *read;
	FILE *output;
	FILE *rFile;
	srand(time(NULL));
	
	do{
	   printf("ENTER your choice:\n1. Genetare Random Number File\n2. External Sort\n3. Exit\n=>");
	   scanf("%d", &choice);	
	   if(choice == 1){
			printf("Generating Random Number File...\n");
			rFile = fopen("Input.txt", "w+");
	
			while(k < NumberLimit){
			r = rand();
			fwrite(&r, sizeof(int), 1, rFile);
			k++;
			}
			fclose(rFile);

		}else if(choice == 2){

			

			read = fopen("Input.txt", "r");
			if(read == NULL){
				printf("Cannot Open the File!!\n");
				return -1;
			}

			printf("\n64-Way Merge\n---------------------------------------------------\n");
			for(i = 1; i <= 64; ++i){
				numbercount = 0;
				printf("writing File %d out of 64\n", i);
				while(!feof(read) && numbercount < 1000000){
					fread(&input, sizeof(int), 1, read);
					if(feof(read)){
						break;
					}	
					a[numbercount] = input;
					numbercount++;
				}
			MergeSort(a, numbercount - 1, 0);
 
			sprintf(fileName, "64-part%d.txt", i);
			output = fopen(fileName, "w");

        		fwrite(a, sizeof(int), numbercount, output);
			fclose(output);
			}
			printf("\n8-Way Merge\n---------------------------------------------------\n");
			eightwayMerge();
			printf("\n4-Way Merge\n---------------------------------------------------\n");
			fourwayMerge();
			printf("\n2-Way Merge\n---------------------------------------------------\n");
			twowayMerge();
			fclose(read);
			printf("Done!\n\n");
		}else if(choice == 3){
			choice = 3;
		}else{
			printf("Invalid Choice!!\n");
		}	
	
	}while(choice != 3);
	


	return 0;
}