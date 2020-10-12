// Write a program to implement exclusive scan algorithm for addition operation and analyze the
// amount of work done and the number of steps taken by the algorithm

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
		printf("%d\n\n",psum[end]-psum[start-1]);
	}
}

void PerformQueries(int psum[],int n,int m){
	int start,end,i;
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
	
	int psum[n];
		
	/*// prefix sum array - 1st element is excluded
	printf("\nThe First element is excluded : \n");
	clock_t start_time1;
	start_time1 = clock();	
	
	psum[0] = 0;
	for(i=1;i<n;i++){
		psum[i] = psum[i-1]+a[i];
	}	
	PerformQueries(psum,n,m);
	
	clock_t total_time1 = clock() - start_time1;
	printf("The Time complexity  = %f seconds\n",(float)total_time1/CLOCKS_PER_SEC);	
	*/
	// prefix sum array - last element is excluded
	
	printf("\nThe Last element is excluded : \n");
	clock_t start_time2;
	start_time2 = clock();
	
	// identity element
	psum[0] = 0;
	for(i=1;i<n;i++){
		psum[i] = psum[i-1]+a[i-1];
	}	
	PerformQueries(psum,n,m);
	
	clock_t total_time2 = clock() - start_time2;
	printf("The Time complexity  = %f seconds\n",(float)total_time2/CLOCKS_PER_SEC);
	return 0;
}
