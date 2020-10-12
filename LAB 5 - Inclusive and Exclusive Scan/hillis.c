// Write a program to implement hillis steele inclusive scan
// algorithm for addition operation and analyze the amount of work done and the number of steps taken
// by each of these algorithms
// based on inclusive scan
// Time - O(nlogn)


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

int main(){
	int n,m,i,j,k,l;
	printf("Enter the number of elements in array = ");
	scanf("%d",&n);
	printf("Enter array Elements : \n");
	int a[n];
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);

	// To find time complexity
	clock_t start_time;
	start_time = clock();
	
	// Hillis Steele
	
	int steps = log(n)/log(2);
	printf("steps (logn) = %d\n",steps);
	int mat[steps][n];
	memset(mat,0,sizeof(mat));
	for(i=0;i<n;i++){
		mat[0][i] = a[i];
	}
	
	for(i=1;i<=steps;i++){		
		int gap = pow(2,i-1);
		printf("gap = %d\n",gap);
		for(k=0;k<n;k++){
			mat[i][k] = mat[i-1][k];
		} 
		for(j=gap;j<=n;j++){
			mat[i][j] = mat[i-1][j] + mat[i-1][j-gap];
		}
		// printing each step
		for(k=0;k<n;k++){
				printf("%d\t",mat[i][k]);
		}
		printf("\n");
		
	}
	clock_t total_time = clock() - start_time;
	printf("\nThe Time complexity  = %f milliseconds\n",(float)total_time*1000/CLOCKS_PER_SEC);	
	return 0;
}

/*
gcc -o  hillis hillis.c -lm
./hillis
*/
