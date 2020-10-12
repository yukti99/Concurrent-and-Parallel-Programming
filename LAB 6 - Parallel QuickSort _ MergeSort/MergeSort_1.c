
        #include <stdio.h>
        #include <stdlib.h>
        #include <pthread.h>

        #define MIN_SIZE 5

        #define ARRAY_SIZE 1000

        struct thread_param {
          int low;
          int high;
          int *array;
        };

        /*void merge(int i, int j, int a[]) {

            int mid = (i + j) / 2;
            int left = i;       // left points to the beginning of the left sub-array
            int right = mid + 1;        // right points to the beginning of the right sub-array
            int k;      // loop counter
            int size = (j-i)+1;
            int aux[size];

            // we loop from i to j to fill each element of the final merged array
            for (k = 0; k < size; k++) {
                if (left == mid + 1) {      // left pointer has reached the limit
                    aux[k] = a[right];
                    right++;
                } else if (right == j + 1) {        // right pointer has reached the limit
                    aux[k] = a[left];
                    left++;
                } else if (a[left] < a[right]) {        // pointer left points to smaller element
                    aux[k] = a[left];
                    left++;
                } else {        // pointer right points to smaller element
                    aux[k] = a[right];
                    right++;
                }
            }
            int t = 0;
            for (k = i; k <= j; k++) {      // copy the elements from aux[] to a[]
                a[k] = aux[t++];
            }

        }*/

        
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
          if (j <= i) {   //Sub Array is empty or a single element
              return;     
          }         
          int mid = (i + j) / 2;
          if(j-i<MIN_SIZE){
            merge_sort(i, mid, a);     // sort the left sub-array recursively
            merge_sort(mid + 1, j, a); // sort the right sub-array recursively
          }
          merge(i,j,a);
      }





        void *merge_sort_thread(void *arg) {

            //access thread parameters
            struct thread_param param = *(struct thread_param*)arg;
            int i = param.low;
            int j = param.high;
            int *array = param.array;
            
            
            if (j <= i) {   //Sub Array is empty or a single element
                return NULL;     
            }

            int mid = (i + j) / 2;
            if((j-i)<MIN_SIZE)    //check if array size falls bellow minimum size
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
        int generate_random_number(unsigned int lower_limit, unsigned int upper_limit) {
            
            return lower_limit + rand() / (RAND_MAX / (upper_limit - lower_limit + 1) + 1);
        }

        int main() {
          int a[ARRAY_SIZE], i;
          
          time_t t;
          srand((unsigned) time(&t));

         /* initialize array with random numbers */
            for (i = 0; i < ARRAY_SIZE; i ++) {
                a[i] = generate_random_number(1, 1000);
            }
          
          pthread_t tid;

          struct thread_param arg;

          arg.low = 0;
          arg.high = ARRAY_SIZE - 1;
          arg.array = a;     



          int ret = pthread_create(&tid, NULL, merge_sort_thread, &arg);

          pthread_join(tid, NULL);
         
          printf("Printing the sorted array:\n");
         
          for (i = 0; i < ARRAY_SIZE; i++)
             printf("%d ", a[i]);
         printf("\n");
          return 0;
        }
        
        
        
        /*
        
        void merge(int low, int mid, int high) 
{ 
    int* left = new int[mid - low + 1]; 
    int* right = new int[high - mid]; 
  
    // n1 is size of left part and n2 is size 
    // of right part 
    int n1 = mid - low + 1, n2 = high - mid, i, j; 
  
    // storing values in left part 
    for (i = 0; i < n1; i++) 
        left[i] = a[i + low]; 
  
    // storing values in right part 
    for (i = 0; i < n2; i++) 
        right[i] = a[i + mid + 1]; 
  
    int k = low; 
    i = j = 0; 
  
    // merge left and right in ascending order 
    while (i < n1 && j < n2) { 
        if (left[i] <= right[j]) 
            a[k++] = left[i++]; 
        else
            a[k++] = right[j++]; 
    } 
  
    // insert remaining values from left 
    while (i < n1) { 
        a[k++] = left[i++]; 
    } 
  
    // insert remaining values from right 
    while (j < n2) { 
        a[k++] = right[j++]; 
    } 
} 
  
// merge sort function 
void merge_sort(int low, int high,int a[]) 
{ 
    // calculating mid point of array 
    int mid = low + (high - low) / 2; 
    if (low < high) { 
  
        // calling first half 
        merge_sort(low, mid); 
  
        // calling second half 
        merge_sort(mid + 1, high); 
  
        // merging the two halves 
        merge(low, mid, high); 
    } 
} 
  
        */
        
