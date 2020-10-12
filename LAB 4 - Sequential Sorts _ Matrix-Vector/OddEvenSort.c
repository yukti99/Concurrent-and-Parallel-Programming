// ODD EVEN TRANSPOSITION SORTING ALGORITM - SEQUENTIAL APPROACH
// Time Complexity: O(n^2)
// Space : O(1)

#include <stdio.h>
#include <stdlib.h>

void swap(int *a,int *b){
	int t = *a;
	*a = *b;
	*b = t;
}

// This is a variation of bubble-sort
// bubble sort of odd elements in odd phase and even elements in even phase
void OddEvenSort(int a[],int n){
	int SortedArray = 0,i,j;
	while(!SortedArray){
		SortedArray = 1;
		// even phase
		for(i=0;i<n-1;i+=2){			
			if (a[i+1] < a[i]){
				swap(&a[i],&a[i+1]);
				SortedArray = 0;
			}		
		}
		// odd phase
		for(i=1;i<n-1;i+=2){			
			if (a[i+1] < a[i]){
				swap(&a[i],&a[i+1]);
				SortedArray = 0;
			}		
		}
	}

}

int main(){
	int n,i,j,k;
	printf("Enter the size of the array to sort = ");
	scanf("%d",&n);
	int a[n];
	printf("Enter the values of the array : \n");
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	OddEvenSort(a,n);
	printf("The Sorted Array:\n");
	for(i=0;i<n;i++){
		printf("%d ",a[i]);
	}
	printf("\n");		
	
	return 0;
}
