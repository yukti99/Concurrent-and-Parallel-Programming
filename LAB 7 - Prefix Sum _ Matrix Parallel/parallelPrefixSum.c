#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>


int factor=1;
int size;

int logn(int value){
	int ans=0;
	while(value/2>0){
		value/=2;
		ans+=1;
	}
	return ans;
}

void* parallelPrefixSum(void *arg){
	int i;
	int *output = (int *)arg;
	for(i=size-1; i-factor>=0; i--)
		output[i]+=output[i-factor];
	factor*=2;	
}


int main(){
	int i;
	printf("Enter size of array: ");
	scanf("%d", &size);
	
	int array[size];
	int max_threads= logn(size)+1;
	int output[size];
	printf("enter elements of array\n");
	for(i=0; i<size; i++){
		scanf("%d", &array[i]);
		output[i]=array[i];
	}
	pthread_t thread[max_threads];
	for(i=0; i<max_threads; i++){
		pthread_create(&thread[i], NULL,parallelPrefixSum, (void *)output);
	}
	for(i=0; i<max_threads; i++)
		pthread_join(thread[i], NULL);
		
		
	for(i=0; i<size; i++) 
		printf("%d ", output[i]);
	return 0;
}
