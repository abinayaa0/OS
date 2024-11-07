#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
int main(){
	key_t key=1234;
	size_t size=2028;
	int shmid=shmget(key,size,IPC_CREAT|0666);
	if(shmid==-1){
		perror("Could not create a shared memory");
		return 1;

	}
	else{
	char* shm_address=(char*)shmat(shmid,NULL,0);
	if(shm_address==(char*)-1){
		perror("Could not attach shared memory segment to process");
		return 1;
	}
	else{
		char* data=(char*)shm_address;
		printf("The data from the shm address is: %s\n",data);

	}
	}
	return 0;
}  //this is reading from shm
//to write into shm:
//pass the message and strncpy it giving size as limit.
//now print shmaddress
