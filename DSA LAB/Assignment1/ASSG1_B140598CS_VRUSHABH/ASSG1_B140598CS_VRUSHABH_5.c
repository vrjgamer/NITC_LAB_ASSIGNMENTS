#include<stdio.h> 
#include<stdlib.h>

void Add(float a,float b){
	printf("%f\n",a+b);	
	return ;
}


void Subtract(float a, float b){
	printf("%f\n",a-b);	
	return ;
}

void Multiply(float a,float b){
	printf("%f\n",a*b);	
	return ;
}

void Division(float a,float b){
	printf("%f\n",a/b);	
	return ;
}


int main(){

	float a,b,result;
	int choice=0;
	void (*add)(float,float) = &Add;
	void (*sub)(float,float) = &Subtract;
	void (*mul)(float,float) = &Multiply;
	void (*div)(float,float) = &Division;
	printf("Enter the Numbers: ");	
	scanf("%f%f",&a,&b);


	do{
		printf("\nMENU\n1. Add\n2. Subtract\n3. Multiply\n4. Divide\n5. Exit\n");
		printf("\nEnter the Choice: ");
		scanf("%d",&choice);

		switch(choice){
			case 1:{
				(*add)(a,b);	
				break;
			}
			case 2:{
				(*sub)(a,b);
                                break;
                        }
			case 3:{
                                (*mul)(a,b);
                                break;
                        }
			case 4:{
				if(b !=0){
	                               (*div)(a,b);
				}else{
			 		printf("Not Valid, 2nd Number is Zero.\n");
				}
                                break;
                        }
			case 5:{
				choice = 5;
				break;
			}
			default:{
				printf("Operation Not Available!\n");
			}

		}
	}while(choice != 5);

	return 0;
}
