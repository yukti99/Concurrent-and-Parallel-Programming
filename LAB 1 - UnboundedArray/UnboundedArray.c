// Unbounded Array

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#define DEFAULT_SIZE 8


int size = 0;
int capacity = DEFAULT_SIZE;
int *p;
void printArray(){
	printf("The array : \n");
	for(int i=0;i<size;i++){
		printf("%d ",p[i]);
	}
	printf("\n");
}
void Insert(int item){		
	p[size] = item;
	size++;
	if (size >= (capacity/4)*3 ){
		printf("Extending size!\n");
		capacity *= 2;
		// extending the space in memory when size becomes 75% of capacity
		p = (int*)realloc(p,sizeof(int)*capacity);
		for(int i=0;i<capacity;i++){
			printf("%d ",p[i]);
		}
		printf("\n");		
				
	}
	printf("size = %d\n",size);
	printf("capacity = %d\n",capacity);
}

void Modify(int index,int newItem){
	if (index >= capacity){
		printf("Sorry! Wrong Index\n");
		return ;
	}
	p[index] = newItem;
}
int getVal(int index){
	if (index >= size){
		printf("Sorry! wrong index\n");
		return INT_MAX;	
	}
	return p[index];
}
int findItem(int item){
	for(int i=0;i<size;i++){
		if (item == p[i])
			return i;
	}
	return -1;
}

void DeleteItem(int item){
	int idx = findItem(item);
	if (idx == -1){
		printf("Element not found in array!\n");
		return ;
	}	
	for(int i=idx;i<size;i++){
		p[i] = p[i+1];
	}
	printf("%d deleted successfully!\n",item);
	p[size-1] = 0;
	size--;
	if (size <= capacity/4){
		printf("Resizing to decrease size from %d to %d !\n",capacity,capacity/2);
		capacity /= 2;
		p = (int*)realloc(p,sizeof(int)*capacity);
		for(int i=0;i<capacity;i++){
			printf("%d ",p[i]);
		}
		printf("\n");	
	}
	printArray();
}
void randomAddidx(){
	srand(time(0));
	int x = rand()%size;
	int y = rand()%1000;
	printf("Inserting %d into the dynamic array at pos = %d!\n",y,x);	
	for(int i=size;i>x;i--){
		p[i] = p[i-1];
	}
	p[x] = y;
	size++;
	printArray();
	if (size >= (capacity/4)*3 ){
		printf("Extending size!\n");
		capacity *= 2;
		// extending the space in memory when size becomes 75% of capacity
		p = (int*)realloc(p,sizeof(int)*capacity);
		for(int i=0;i<capacity;i++){
			printf("%d ",p[i]);
		}
		printf("\n");		
				
	}	
}
void randomAdd(){
	srand(time(0));
	int x = rand()%1000;
	printf("Inserting %d into the dynamic array!\n",x);
	Insert(x);
}
void randomDelete(){
	if (size<1){
		printf("Array Empty!\n");
		return ;
	}
	srand(time(0));
	int x = rand()%size;
	printf("Deleting element at pos = %d !\n",x);
	DeleteItem(p[x]);
}	

int main(){	
	p = (int*)malloc(capacity*sizeof(int));
	if (p == NULL){
		printf("Error allocating the memory!\n");
		exit(0);
	}	
	int n,x,y,z,ch;
	while(1){
		printf("\nEnter what you want to do : \n");
		printf("1. Insert an element \n");
		printf("2. Modify an element \n");
		printf("3. Delete an element \n");
		printf("4. Get element at index\n");
		printf("5. Randomly add a number at the end\n");
		printf("6. Randomly add a number at random index\n");
		printf("7. Randomly delete a number\n");
		printf("8. Print the Unbounded array \n");		
		printf("9. Exit \n\n");	
		printf("Enter your choice : ");
		scanf("%d",&ch);
		printf("\n");
		switch(ch){
			case 1 :
				printf("Enter the element you want to Insert : ");
				scanf("%d",&x);
				Insert(x);
				break;
			case 2:
				printf("Enter the position you want to Modify : ");
				scanf("%d",&x);
				printf("Enter the new item : ");
				scanf("%d",&y);
				Modify(x,y);
				break;
			case 3:
				printf("Enter the element you want to Delete : ");
				scanf("%d",&x);
				DeleteItem(x);
				break;
			case 4:
				printf("Enter the index : ");
				scanf("%d",&x);
				printf("Value at %d index  = %d\n",x,getVal(x));
				break;
			case 5:
				randomAdd();
				break;
			case 6:
				randomAddidx();
				break;
			case 7:
				randomDelete();
				break;
			case 8:
				printArray();
				break;
			case 9:
				printf("Thank You! Bye\n");
				exit(0);
			default:
				printf("Wrong Input\n");
		
		}
	}
	return 0;
}
