// CPP Program to find sum of array 
#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h> 

// size of array 
#define MAX 8 

// maximum number of threads 
#define MAX_THREAD 4 

int a[] = {3,1,4,1,5,9,1,0}; 
int sum[4] = { 0 }; 
int part = 0; 
int prefixSum[8] = {};
int p=0;

void* sum_array(void* arg){
	// Each thread computes sum of 1/4th of array 
	int thread_part = part++; 	         
	int s = 0;
	for (int i = thread_part * (MAX / 4); i < (thread_part + 1) * (MAX / 4); i++){
		sum[thread_part] += a[i]; 
		s+=a[i];		
	}
	prefixSum[p++] = s;
	printf("s = %d\n",s);
	for(int j=0;j<8;j++){
			printf("%d ",prefixSum[j]);
		}
		printf("\n");		
} 


int main(){ 

	prefixSum[p++] = a[0];
	pthread_t threads[MAX_THREAD]; 

	// Creating 4 threads 
	for (int i = 0; i < MAX_THREAD; i++) 
		pthread_create(&threads[i], NULL, sum_array, (void*)NULL); 

	// joining 4 threads i.e. waiting for all 4 threads to complete 
	for (int i = 0; i < MAX_THREAD; i++) 
		pthread_join(threads[i], NULL);

	
	// adding sum of all 4 parts 
	int total_sum = 0; 
	for (int i = 0; i < MAX_THREAD; i++) 
		total_sum += sum[i]; 
	printf("The sum  = %d\n",total_sum);
	return 0; 
} 

