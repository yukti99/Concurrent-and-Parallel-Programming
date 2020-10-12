#include <bits/stdc++.h>
using namespace std;


// QuickSort


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
			swap(a[i],a[j]);		
		}
	}
	// swap pivot to its correct position at j
	swap(a[l],a[j]);
	// return partition position 
	return j;
}

int partition2(int a[],int l,int h){
	int pivot = a[h];
	int i=l,j=h-1,t=0;
	while(i<j){
		while(a[i]>pivot)
			i++;
		while(a[j]<=pivot)
			j--;
		if (i<j){
			// swap a[j] and a[i]
			swap(a[i],a[j]);		
		}
	}
	// swap pivot to its correct position at j
	swap(a[h],a[j]);
	// return partition position 
	return j;
}

void QuickSort(int a[],int l,int h){
	int j;
	if (l<h){
		j = partition2(a,l,h);
		QuickSort(a,l,j-1);
		QuickSort(a,j+1,h);
	}
}

int main(){
	//int a[]= {11,13,7,12,16,9,24,5,10,3,-1,7,0,22,57};
	int a[] = {5,4,3,2,1,0};
	int n = sizeof(a)/sizeof(a[0]);
	cout<<"Before Sorting : "<<endl;
	for(auto i:a)
		cout<<i<<" ";
	cout<<endl;
	QuickSort(a,0,n-1);
	cout<<"After Sorting : "<<endl;
	for(auto i:a)
		cout<<i<<" ";
	cout<<endl;
	return 0;
}
