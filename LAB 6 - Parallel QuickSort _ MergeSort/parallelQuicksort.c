#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#define MIN_SIZE 5
#define ARRAY_SIZE 1000

struct thread_param {
	int low;
	int high;
	int *array;          
          
};
int partition(int a[],int l,int h){
		int pivot = a[l];
		int i=l,j=h,t=0;
		while(i<j){
			while(a[i]<=pivot)
				i++;
			while(a[j]>pivot)
				j--;
			if (i<j){
				// swap a[j] and a[i]
				int t = a[i];
				a[i] = a[j];
				a[j] = t;
						
			}
		}
		// swap pivot to its correct position at j
		int t1 = a[l];
		a[l] = a[j];
		a[j] = t1;
		// return partition position 
		return j;
}
void QuickSort(int a[],int l,int h){
		if (l<h){
			int pi = partition(a,l,h);
			QuickSort(a,l,pi-1);
			QuickSort(a,pi+1,h);
		}
}       
void *quick_sort_thread(void *arg){            
            struct thread_param param = *(struct thread_param*)arg;
            int i = param.low;
            int j = param.high;
            int *array = param.array;         
            
            if (j <= i) {   //Sub Array is empty or a single element
                return NULL;     
            }

            int mid = (i + j) / 2;
            if((j-i)<MIN_SIZE)    //check if array size falls bellow minimum size, if yes then sequential quick sort
              QuickSort(array,i, j);
            else {    
              printf("Splitting array  of size %d in thread \n", (j-i+1));
              int pi = partition(array,i,j);
              pthread_t tid1;
              struct thread_param arg1;
              arg1.low = i;
              arg1.high = pi-1;
              arg1.array = array;
              

              int ret1 = pthread_create(&tid1, NULL, quick_sort_thread, &arg1);
                 
              
              pthread_t tid2;
              struct thread_param arg2;
              arg2.low = pi+1;
              arg2.high = j;
              arg2.array = array;
              
              int ret2 = pthread_create(&tid2, NULL, quick_sort_thread, &arg2);
              
              pthread_join(tid1, NULL); 
              pthread_join(tid2, NULL);   
              }
             
              
}      
/* generate random numbers within the specified limit */
int generate_random_number(unsigned int lower_limit, unsigned int upper_limit) {        
	return lower_limit + rand() / (RAND_MAX / (upper_limit - lower_limit + 1) + 1);        
}
int main() {        
          int a[ARRAY_SIZE], i; 
                       
          // To find time complexity
		  clock_t start_time;
		  start_time = clock();  
         
        
          for (i = 0; i < ARRAY_SIZE; i ++) {
                a[i] = generate_random_number(1, 1000);
          }      
          printf("Original array:\n");                
          for (i = 0; i < ARRAY_SIZE; i++)
             printf("%d ", a[i]);
          printf("\n\n");
          
              
          pthread_t tid;

          struct thread_param arg;

          arg.low = 0;
          arg.high = ARRAY_SIZE - 1;
          arg.array = a; 
           
          int ret = pthread_create(&tid, NULL, quick_sort_thread, &arg);
          pthread_join(tid, NULL);       
          printf("\nSorted array:\n");                
          for (i = 0; i < ARRAY_SIZE; i++)
             printf("%d ", a[i]);
          printf("\n");
          
          clock_t total_time = clock() - start_time;
		  printf("\nThe Time complexity  = %f milliseconds\n",(float)total_time*1000/CLOCKS_PER_SEC);	
          return 0;
}
