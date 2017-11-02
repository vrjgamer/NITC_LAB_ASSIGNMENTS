#include<stdio.h>
#include<stdlib.h>

struct student{
	char STUDENT_ID[50];
	char STUDENT_NAME[50];
	char STUDENT_MARK[10];
}; 


void getstudBelowThirty(char *fileName){

	struct student stud;
	long marks;
	
	FILE *pFile = fopen(fileName, "r");
	if(pFile == NULL){
		printf("Error in opening Records!!\n");
		return;
	}
	
	while(!feof(pFile)){
		fread(&stud,sizeof(stud),1,pFile);

		if(stud.STUDENT_MARK[0] != 'I'&& stud.STUDENT_MARK[0] != 'A'){
			marks = strtol(stud.STUDENT_MARK,NULL,10);
			if(marks < 30){
				printf("%s\n",stud.STUDENT_NAME);		
			}
		}
	}
	
	fclose(pFile);
	return;
}

void getstudInsufficient(char *fileName){
	struct student stud;
	
	int i = 0;
	
	FILE *pFile = fopen(fileName, "r");
	if(pFile == NULL){
		printf("Error in opening Records!!\n");
		return ;
	}
	

	while(!feof(pFile)){
		fread(&stud,sizeof(stud),1,pFile);
		if(stud.STUDENT_MARK[0] == 'I'){
			printf("%s\n",stud.STUDENT_NAME);	
		}
		++i;
	}


	fclose(pFile);
	return;
}


void printAllInOrder(char *fileName){
	
	struct student stud;
	
	FILE *pFile = fopen(fileName, "r");
	if(pFile == NULL){
		printf("Error in opening Records!!\n");
		return ;
	}

	printf("    Student_ID      Student_Name        Mark\n---------------------------------------------------------\n");
	
	while(!feof(pFile)){
		fread(&stud,sizeof(stud),1,pFile);
		if(feof(pFile)){
			break;		
		}
		printf("\t%s \t%s \t\t%s\n",stud.STUDENT_ID,stud.STUDENT_NAME,stud.STUDENT_MARK);
	}
	fclose(pFile);
	return;
}



int main(int argc,char *argv){
	int i, j,choice = 0;
	struct student newStudent;

	if(argc == 0){
		printf("No Arguments Passed To main Function From Terminal.\n");
		return -1;	
	}

	char *fileName = argv[1];
	
	FILE *pFile;
	
	do{
		printf("\nMENU\n1. Add student details\n2. Display the names of students who obtained less than 30 marks\n3. Display the names of students who have insufficient attendance\n4. Display all the records in the file\n5. Exit\n\nEnter Your Choice: ");
		scanf("%d",&choice);

		switch (choice){
			case 1:{
				pFile = fopen(fileName,"a+");
	
				if(pFile == NULL){
					printf("Error in opening Records!!\n");
					return -1;
				}
				printf("Enter Name, ID, Mark: \n");
				scanf("%s%s%s",newStudent.STUDENT_NAME,newStudent.STUDENT_ID,newStudent.STUDENT_MARK);

				fwrite(&newStudent,sizeof(newStudent),1,pFile);

				fclose(pFile);
				break;
				}
			case 2: {
				getstudBelowThirty(fileName);
				break;
				}
			case 3:{
				getstudInsufficient(fileName);
				break;
				}
			case 4:{
				printAllInOrder(fileName);
				break;
				}
			case 5:{
				choice = 5;
				break;
				}
			default:{
				printf("Invalid Choice!!\n");
				}
		}		

	}while(choice != 5);
		

	return 0;
}

