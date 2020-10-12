#include <stdio.h>
#include <pthread.h> 
#include <stdlib.h>
#include <time.h> 


#define MAX 20

#define THREAD_MAX 4 

int a[MAX]; 
int part = 0; 
int low, mid, high;
int size=MAX;

int min(int a, int b){
    return a<b?a:b;
}

void* merge(void *arg) 
{
    int start=low;
    int midl=mid;
    int end=high;
    int start2 = midl + 1; 
    int flag=0;
    // If the direct merge is already sorted 
    if (a[mid] <= a[start2]) { 
        flag=1;
    } 
  
    // Two pointers to maintain start 
    // of both arrays to merge
    if(flag==0){ 
    while (start <= mid && start2 <= end) { 
  
        // If element 1 is in right place 
        if (a[start] <= a[start2]) { 
            start++; 
        } 
        else { 
            int value = a[start2]; 
            int index = start2; 
  
            // Shift all the elements between element 1 
            // element 2, right by 1. 
            while (index != start) { 
                a[index] = a[index - 1]; 
                index--; 
            } 
            a[start] = value; 
  
            // Update all the pointers 
            start++; 
            mid++; 
            start2++; 
        } 
    } }
}

// thread function for multi-threading 
void merge_sort() 
{ 
	// which part out of 4(THREAD_MAX) parts 
	pthread_t thread[size/2];

	// calculating low and high 
	int d;
	int j;
	for(d=1;d<size;d*=2){
	    j=0;
	    for(int i=0; i<size; i+=2*d){
	        low=i;
	        high=i+2*d-1;
	        mid=min(low + (high - low) / 2, size-1);
	        high=min(high, size-1);
	        pthread_create(&thread[j++], NULL, merge, NULL);
	        pthread_join(thread[j-1], NULL);
	    }
	   
	} 
} 


int main() 
{ 
	
	for (int i = 0; i < MAX; i++) 
		a[i] = rand() % 100; 
		
    for (int i = 0; i < MAX; i++) 
		printf("%d, ", a[i]); 
    printf("\n");

	clock_t t1, t2; 

	t1 = clock(); 
	merge_sort();

	t2 = clock(); 

	
	printf("Sorted array: \n"); 
	for (int i = 0; i < MAX; i++) 
		printf("%d, ", a[i]); 

	printf("\ntime taken: %ld\n", t2-t1);

	return 0; 
}

