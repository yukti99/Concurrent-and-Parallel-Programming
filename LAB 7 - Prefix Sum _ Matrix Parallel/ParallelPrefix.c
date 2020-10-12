#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#define n 8

struct thread_param {
     int sumval;
     int *array;
     int start;
};
 
struct thread_param targ[n];

// main function to calculate the prefix sum array parallely
void *prefixSum(void *arg) {
	struct thread_param param = *(struct thread_param*)arg;
    int sv = param.sumval;
    int s = param.start;
    int *array = param.array;  
    for(int i=0;i<=s;i++){    
    	sv+=array[i];    
    }    
    targ[s].sumval=sv;
}

int main(){
	int i,st,e;
	int a[] = {3,1,4,1,5,9,1,0};	
	printf("The Array : \n");
	for(i=0;i<n;i++){
		printf("%d ",a[i]);
	}        
	printf("\n");		
    pthread_t tid[n];  
  
    for(i=0; i<n;i++) {
        targ[i].sumval = 0;
        targ[i].start = i;
        targ[i].array = a;
        int rc = pthread_create(&tid[i], NULL,prefixSum, &targ[i]);
        if (rc){
            printf("ERROR!! Return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
   }
   printf("The prefix Sum of the Array : \n");
   for(i = 0; i<n;i++) {
       pthread_join(tid[i], NULL);
       printf("%d ",targ[i].sumval);
   }  
   printf("\nEnter the queries start and end positions : \n");       
   while(1){
      scanf("%d %d",&st,&e);
      if(st == 0)
      	printf("The Sum = %d\n",targ[e].sumval);
      else
      	printf("The Sum = %d\n",targ[e].sumval-targ[st-1].sumval);         
  }
        
            
}
