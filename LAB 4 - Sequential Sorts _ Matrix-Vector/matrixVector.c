#include <stdio.h>
#include <stdlib.h>

// Sequential Matrix-Vector Multiplication
// Time Complexity - O(n^2)

int main(){

	// INPUT FOR MATRIX AND VECTOR
	int n,i,j,k;
	printf("Enter the size of matrix = ");
	scanf("%d",&n);
	int mat[n][n],v[n];
	printf("Enter the values of matrix : \n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			scanf("%d",&mat[i][j]);
		}
	}
	printf("Enter the values of vector : \n");
	for(i=0;i<n;i++){
		scanf("%d",&v[i]);
	}
	int Product[n];
	
	// SEQUENTIAL ALGORITHM	
	for(i=0;i<n;i++){
		Product[i] = 0;
		for(j=0;j<n;j++){
			Product[i] += mat[i][j] * v[j];
		}
	}
	
	printf("The Result Matrix : \n");
	for(i=0;i<n;i++){
		printf("%d ",Product[i]);
	}
	printf("\n");
	
	return 0;
}


