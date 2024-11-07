#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define NUM_THREADS 5
void* thread_function(void* arg){
	long tid=(long)arg;
	printf("Thread %ld is executing to say Hello world\n",tid);
	sleep(3);//simulate some work
	printf("Thread %ld finished execution\n",tid);
	return NULL;
}
int main(){
	pthread_t threads[NUM_THREADS];
	long t;
	int rc;
	for(t=0;t<NUM_THREADS;t++){
		rc=pthread_create(&threads[t],NULL,thread_function,(void*)t);
		if(rc==-1){
		perror("could not create thread");
		exit(1);
		}
	}
	for(t=0;t<NUM_THREADS;t++){
		pthread_join(threads[t],NULL);
	}
	printf("All threads executed!\n");
	return 0;
}
