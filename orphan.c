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
	else if(pid>0){
		printf("The parent process %d is running\n",getpid());
		printf("Parent process exiting ");
		exit(0);
	}
	else{
	printf("The child process is running: %d\n",pid);
	sleep(10);
	printf("The child process is still running after parent exited"); 

	}
	return 0;
}
//the parent process is running
//
