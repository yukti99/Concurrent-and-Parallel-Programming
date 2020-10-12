#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX 4
#define MAX_THREAD 4
int matA[MAX][MAX]; 
int matB[MAX][MAX]; 
int matC[MAX][MAX]; 
int steps = 0; 
void* Multiply(void* arg){ 
	int c = steps++; 	
	for (int i=c*MAX/4;i <(c + 1)*MAX/4;i++){
		for (int j=0;j<MAX;j++){ 
			for(int k=0; k<MAX;k++){
				matC[i][j] += matA[i][k] * matB[k][j]; 
			}
		}
	}
}
int main(){ 
	for (int i = 0; i < MAX; i++) { 
		for (int j = 0; j < MAX; j++) { 
			matA[i][j] = rand() % 10; 
			matB[i][j] = rand() % 10; 
		} 
	} 
	printf("Matrix 1 : \n"); 
	for (int i = 0; i < MAX; i++) { 
		for (int j = 0; j < MAX; j++) 
			printf("%d\t",matA[i][j]);;		 
		printf("\n");
	}
	printf("\n"); 
	printf("Matrix 2 : \n"); 
	for (int i = 0; i < MAX; i++) { 
		for (int j = 0; j < MAX; j++) 
			printf("%d\t",matB[i][j]);;		 
		printf("\n");
	}
	printf("\n"); 
	pthread_t threads[MAX_THREAD];	
	for (int i=0;i<MAX_THREAD;i++) { 
		int* p; 
		pthread_create(&threads[i], NULL,Multiply, (void*)(p)); 
	} 	
	for (int i=0; i<MAX_THREAD;i++) 
		pthread_join(threads[i], NULL);
				
	printf("Multiplication of matrices \n"); 
	for (int i = 0; i < MAX; i++) { 
		for (int j = 0; j < MAX; j++) 
			printf("%d\t",matC[i][j]);;		 
		printf("\n");
	}
	printf("\n"); 
	return 0; 
} 

