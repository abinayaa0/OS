#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(){
	pid_t pid=fork();
	if(pid<0){
		perror("The child process could not be created\n");
		exit(1);
	}
	else if(pid==0){
	printf("The child process is running: %d\n",pid);
	exit(1); //exits immediately leaving the parent as zombie since it does not call wait.
	}
	else{
		printf("The parent %d created a child process %d\n",getpid(),pid);
	printf("The parent is sleeping. Check ps command");
		sleep(10);
		
		//open another terminal and type ps aux during sleep 
		printf("The parent process is exiting\n");
	}
	return 0;
}
