#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define NUM_PHILOS0PHERS 5

sem_t forks[NUM_PHILOS0PHERS];
pthread_t philosophers[NUM_PHILOS0PHERS];

void* dine(void* arg){
    int id=*(int*)arg;
        printf("The philosopher %d is thinking\n",id);
        sem_wait(&forks[id]);
        sem_wait(&forks[(id+1)%(NUM_PHILOS0PHERS)]);
        
        printf("The philosopher is eating!\n");
        
        sem_post(&forks[id]);
        sem_post(&forks[(id+1)%(NUM_PHILOS0PHERS)]);
    
    return NULL;
}

int main(){
    int philosopher[NUM_PHILOS0PHERS];
    for(int i=0;i<NUM_PHILOS0PHERS;i++){
        sem_init(&forks[i],0,1);
        philosopher[i]=i;
    }
    
    for(int i=0;i<NUM_PHILOS0PHERS;i++){
        pthread_create(&philosophers[i],NULL,dine,&philosopher[i]);
    }
    
    for(int i=0;i<NUM_PHILOS0PHERS;i++){
        pthread_join(philosophers[i],NULL);
    }
    
    for(int i=0;i<NUM_PHILOS0PHERS;i++){
        sem_destroy(&forks[i]);
    }
}
