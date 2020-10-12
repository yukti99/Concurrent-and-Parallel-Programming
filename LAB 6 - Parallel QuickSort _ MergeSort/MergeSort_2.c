
        #include <stdio.h>
        #include <stdlib.h>
        #include <pthread.h>

        #define MIN_SIZE 2

        #define ARRAY_SIZE 10

        struct thread_param {
          int low;
          int high;
          int *array;
        };

        void merge(int i, int mid, int j, int a[]) {

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

        }

      // function to sort the subarray a[i .. j] of the array a[]
      void merge_sort(int i, int j, int a[]) {
          if (j <= i) {   //Sub Array is empty or a single element
              return;     
          }
         
          int mid = (i + j) / 2;
          if((j-i)<MIN_SIZE){
            merge_sort(i, mid, a);     // sort the left sub-array recursively
            merge_sort(mid + 1, j, a); // sort the right sub-array recursively
          }
          merge(i,mid,j,a);
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
              pthread_join(tid1, NULL);    
              
              pthread_t tid2;
              struct thread_param arg2;
              arg2.low = mid+1;
              arg2.high = j;
              arg2.array = array;
              

              int ret2 = pthread_create(&tid2, NULL, merge_sort_thread, &arg2);
              pthread_join(tid2, NULL);   
        }
             
          merge(i,mid,j,array);
      }
       
    

        /* generate random numbers within the specified limit */
        int generate_random_number(unsigned int lower_limit, unsigned int upper_limit) {
            
            return lower_limit + rand() / (RAND_MAX / (upper_limit - lower_limit + 1) + 1);
        }

        int main() {
          int a[ARRAY_SIZE], i;
          
          time_t t;
          srand((unsigned) time(&t));
          int n_threds = ARRAY_SIZE/MIN_SIZE;

         /* initialize array with random numbers */
            for (i = 0; i < ARRAY_SIZE; i ++) {
                a[i] = generate_random_number(1, 100);
            }
          
          pthread_t tid[n_threds];

          struct thread_param arg[n_threds];

          //Create mutiple threads

          for(i = 0; i<n_threds;i++) {
            arg[i].low = i*MIN_SIZE ;
            arg[i].high =((i+1)* MIN_SIZE) - 1;
            arg[i].array = a;
            int rc = pthread_create(&tid[i], NULL, merge_sort_thread, &arg[i]);
            if (rc){
              printf("ERROR; return code from pthread_create() is %d\n", rc);
             exit(-1);
            }
          }
          for(i = 0; i<n_threds;i++) {
             pthread_join(tid[i], NULL);
            int mid;
            int j;
          for(int i = 0; i < n_threds; i++) {
            
            int high = ((i+1)* MIN_SIZE) - 1;
            if(i==0)
              mid = high/2;
            merge(0, mid,high, a);
            mid = high;
          }

    

          if(ARRAY_SIZE%MIN_SIZE>0) {
            

            int low = ARRAY_SIZE - (n_threds*MIN_SIZE);
            int high = ARRAY_SIZE - 1;
            merge_sort(low, high, a);
            mid = low;       //Sort remaining array
            merge(0,mid, high,a);
          }
          
          printf("Printing the sorted array:\n");
      
          for (i = 0; i < ARRAY_SIZE; i++)
             printf("%d\n", a[i]);
         return 0;
      }
    }
      
