#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Size of the buffer

int buffer[BUFFER_SIZE];  // Shared buffer array
int in = 0, out = 0;      // 'in' is the index for the next produced item, 'out' for the next consumed item

sem_t empty, full;        // Semaphores to track empty and full                          slots in the buffer
pthread_mutex_t mutex;    // Mutex to protect access to the                                       buffer

// Producer function
void* producer(void* arg) 
{
    for (int i = 0; i < 10; i++)   // Produces 10 items
    {
        sleep(rand() % 2);    // Random sleep to simulate                          production time
        
        sem_wait(&empty);    // Wait if buffer is full (empty                            slots are 0)
        pthread_mutex_lock(&mutex);  // Lock the buffer to                         ensure mutual exclusion

        buffer[in] = i;    // Produce an item and place it in                  the buffer at index 'in'
        printf("Producer produced: %d\n", buffer[in]);

        in = (in + 1) % BUFFER_SIZE;    // Move to the next                     position in the circular buffer

        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&full);  // Signal that a new item is available (increment full slots)
    }
    return NULL;
}

// Consumer function
void* consumer(void* arg) 
{
    for (int i = 0; i < 10; i++) // Consumes 10 items
    {
        sleep(rand() % 2); // Random sleep to simulate consumption time
        
        sem_wait(&full); // Wait if buffer is empty (full slots are 0)
        pthread_mutex_lock(&mutex); // Lock the buffer for exclusive access

        int item = buffer[out];  // Consume the item at index 'out'
        printf("Consumer consumed: %d\n", item);

        out = (out + 1) % BUFFER_SIZE; // Move to the next position in the circular buffer

        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&empty); // Signal that a slot is now empty (increment empty slots)
    }
    return NULL;
}

int main() 
{
    pthread_t prod, cons; // Thread identifiers for producer and consumer

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // 'empty' starts with                        BUFFER_SIZE (all slots empty)
    sem_init(&full, 0, 0);            // 'full' starts with 0                            (no items produced yet)

    pthread_mutex_init(&mutex, NULL); // Initialize mutex

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for producer and consumer to finish
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
