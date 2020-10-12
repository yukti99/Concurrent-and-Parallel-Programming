#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#define MIN_SIZE 5
#define ARRAY_SIZE 1000

// PARALLEL MERGE SORT 1 : CREATING ALL THREADS IN MAIN

struct thread_param {
	int low;
	int high;
	int *array;          
          
};
void merge(int i,int j,int a[]){
	int mid = (i+j)/2;
    int n1 = mid-i+1;
    int n2 = j-mid;
    int left[n1],right[n2];
    int x=0,y=0,z=i,p;
    for(p=0;p<n1;p++){
        left[p] = a[p+i];
    }
    for(p=0;p<n2;p++){
        right[p] = a[p+mid+1];
    }
    while(x<n1  && y<n2){
        if (left[x] <= right[y]){
        	a[z++] = left[x++];
        }else{
        	a[z++] = right[y++];
        }
    }
    while(x<n1){
        a[z++] = left[x++];
    }
    while(y<n2){
        a[z++] = right[y++];
    }   
}
// function to sort the subarray a[i .. j] of the array a[]      
void merge_sort(int i, int j, int a[]) {     
	 if (j > i){
	 	 int mid = (i + j) / 2;  
         if(j-i < MIN_SIZE){
		    merge_sort(i, mid, a);     // sort the left sub-array recursively
		    merge_sort(mid + 1, j, a); // sort the right sub-array recursively
		  }
		  merge(i,j,a);
     }     
          
}
void *merge_sort_thread(void *arg){    
            struct thread_param param = *(struct thread_param*)arg;
            int i = param.low;
            int j = param.high;
            int *array = param.array;
            
            
            if (j <= i) {   //Sub Array is empty or a single element
                return NULL;     
            }

            int mid = (i + j) / 2;
            if((j-i)<MIN_SIZE)    //check if array size falls bellow minimum size, if yes then sequential merge sort
              merge_sort(i, j, array);
            else {    //array size is larger hence, can be sorted using two threads
              printf("Splitting array  of size %d in thread \n", (j-i+1));
              pthread_t tid1;
              struct thread_param arg1;
              arg1.low = i;
              arg1.high = mid;
              arg1.array = array;
              

              int ret1 = pthread_create(&tid1, NULL, merge_sort_thread, &arg1);
                 
              
              pthread_t tid2;
              struct thread_param arg2;
              arg2.low = mid+1;
              arg2.high = j;
              arg2.array = array;
              
              int ret2 = pthread_create(&tid2, NULL, merge_sort_thread, &arg2);
              pthread_join(tid1, NULL); 
              pthread_join(tid2, NULL);   
              }
             
              merge(i,j,array);
}      
/* generate random numbers within the specified limit */
int generate_random_number(unsigned int lower_limit, unsigned int upper_limit){        
	return lower_limit + rand() / (RAND_MAX / (upper_limit - lower_limit + 1) + 1);        
}

int main(){        
          int a[ARRAY_SIZE], i; 
          int n_threads = ARRAY_SIZE/MIN_SIZE;
              
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
               
		  // creating an array of threads
          pthread_t tid[n_threads];
          struct thread_param arg[n_threads];

          //Create mutiple threads
          for(i = 0; i<n_threads;i++) {   
                 
            arg[i].low = i*MIN_SIZE ;
            arg[i].high =((i+1)* MIN_SIZE) - 1;
            arg[i].array = a;
            
            int rc = pthread_create(&tid[i], NULL, merge_sort_thread, &arg[i]);
            if (rc){
              printf("ERROR; return code from pthread_create() is %d\n", rc);
              exit(-1);
            }
          }
          
          for(i = 0; i<n_threads;i++) {
             pthread_join(tid[i], NULL);
             int mid;
             int j;
		     for(int i = 0; i < n_threads; i++) {
		        int high = ((i+1)* MIN_SIZE) - 1;
		        if(i==0)
		          	mid = high/2;
		        merge(0,high, a);
		        mid = high;
		     }
		     if(ARRAY_SIZE % MIN_SIZE > 0) {
		        int low = ARRAY_SIZE - (n_threads*MIN_SIZE);
		        int high = ARRAY_SIZE - 1;
		        merge_sort(low, high, a);
		        mid = low;       //Sort remaining array
		        merge(0,high,a);
		     }

          printf("The Sorted array:\n");
           for (i = 0; i < ARRAY_SIZE; i++)
             printf("%d ", a[i]);
          printf("\n");
          
             
          clock_t total_time = clock() - start_time;
		  printf("\nThe Time complexity  = %f milliseconds\n",(float)total_time*1000/CLOCKS_PER_SEC);	
          return 0;
      }
}
