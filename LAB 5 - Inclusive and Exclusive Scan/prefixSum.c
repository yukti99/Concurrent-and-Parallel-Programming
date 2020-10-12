
// Write a C program to implement prefix sum algorithm to find the output of range sum queries and
// analyze the time complexity - O(n)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void prefixSum(int psum[],int n,int start,int end){
	printf("The prefix Sum = "); 
	if (start == 0){
		printf("%d\n\n",psum[end]);
	}
	else if (end >= n-1){
		printf("%d\n\n",psum[n-1]-psum[start-1]);
	}	
	else{
		printf("The prefix Sum = %d\n\n",psum[end]-psum[start-1]);
	}
}

int main(){
	int n,m,i;
	printf("Enter the number of elements in array = ");
	scanf("%d",&n);
	printf("Enter array Elements : \n");
	int a[n];
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	printf("Enter the number of queries = ");
	scanf("%d",&m);
	
	// To find time complexity
	clock_t start_time;
	start_time = clock();
	
	// prefix sum array
	int psum[n];
	psum[0] = a[0];
	for(i=1;i<n;i++){
		psum[i] = psum[i-1]+a[i];
	}
	int start,end;
	for(i=0;i<m;i++){
		x:printf("Query - %d\n",i+1);
		printf("Enter the starting index = ");
		scanf("%d",&start);
		printf("Enter the ending index = ");
		scanf("%d",&end);	
		if (start > end){
			printf("Invalid query!\n");
			goto x;
		}	
		prefixSum(psum,n,start,end);		
	}	
	clock_t total_time = clock() - start_time;
	printf("The Time complexity  = %f seconds\n",(float)total_time/CLOCKS_PER_SEC);	
	return 0;
}
