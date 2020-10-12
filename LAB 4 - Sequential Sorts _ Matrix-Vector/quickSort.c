#include <stdio.h>
#include <stdlib.h>

// Quick Sort Algorithm

// Average Case Complexity - O(nlogn)
// Best case Complexity    - O(nlogn)
// Worst Case Complexity   - O(n^2) when array is sorted
// In-place sorting (only recursive calls stored on system stack)
// Not a Stable sort


void swap(int *a,int *b){
	int t = *a;
	*a = *b;
	*b = t;
}

int Partition(int a[],int l,int h){
	// pivot is taken as the last element
	int pivot = a[h];
	int i = l-1,j;
	for(j=i+1;j<=h-1;j++){
		if (a[j] < pivot){
			i++;
			swap(&a[j],&a[i]);
			
		} 
	}
	swap(&a[h],&a[i+1]);
	return i+1;
}
void QuickSort(int a[],int l,int h){
	if (l<h){
		// parition Index
		int pI = Partition(a,l,h);
		// left partition
		QuickSort(a,l,pI-1);
		// right partition
		QuickSort(a,pI+1,h);
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
	QuickSort(a,0,n-1);
	printf("The Sorted Array:\n");
	for(i=0;i<n;i++){
		printf("%d ",a[i]);
	}
	printf("\n");		
	
	return 0;
}
