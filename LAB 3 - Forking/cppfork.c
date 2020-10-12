#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h> 

int count=0;
int r = 0,w = 0;

void ReadWrite(FILE *fp){
	int pid2,pid3;
	int pid1 = fork();
	r++;
	if (pid1 == 0 ){
		printf("Child process 1 read operation  %d (Id : %d) [count = %d]\n",r,getpid(),count);
		sleep(2);
	}		
	else{
		pid2 = fork();
		if (pid2 == 0){
			printf("Child process 2 read operation  %d (Id : %d) [count = %d]\n",r,getpid(),count);
			sleep(5);
		}
		else{
			pid3 = fork();
			if (pid3 == 0){
				printf("Child process 3 read operation  %d (Id : %d) [count = %d]\n",r,getpid(),count);
				sleep(8);
			}
			else{
				printf("Parent process read operation %d (Id : %d) [count = %d]\n",r,getpid(),count);
				// waits for its children
				wait(NULL);
			}
		}
	}
	fp = fopen("forkoutput.txt","a+");
	fseek(fp, 0, SEEK_END);
	fscanf(fp,"%d",&count);	
	// incrementing count
	count++;
	// writing
	fseek(fp, 0, SEEK_END);
	fprintf(fp,"%d ",count);
	w++;
	if (pid1 == 0){
		printf("Child process 1 write operation  %d (Id : %d) [count = %d]\n",w,getpid(),count);
		//sleep(2);
	}
	else{
		if (pid2 == 0){
			printf("Child process 2 write operation  %d (Id : %d) [count = %d]\n",w,getpid(),count);
			//sleep(5);
		}
		else{
			if (pid3 == 0){
				printf("Child process 3 write operation  %d (Id : %d) [count = %d]\n",w,getpid(),count);
				//sleep(8);
			}
			else{
				printf("Parent process write operation %d (Id : %d) [count = %d]\n",w,getpid(),count);
				wait(NULL);
			}
		}		
		
	}
	fclose(fp);
}
int main(){
	FILE *fp;
	for(int i=1;i<=4;i++){
		ReadWrite(fp);
	}	
	return 0;
}
