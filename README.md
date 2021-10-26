```
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
// for the sleep function
#include <unistd.h>
#include <pthread.h>
#define THINKERS 5

sem_t hungry;
sem_t chopsticks[5];
void *philosopher(void *_id);

int main() {
    int i, ids[5] = {1,2,3,4,5};
    pthread_t philosophers[THINKERS];

    // allows atmost 4 people to be hungry.
    sem_init(&hungry, 0, 4);
    // initialise chopsticks as 
    for(i=0; i<5; i++){
        sem_init(&chopsticks[i], 0, 1);
    }
    // executing the threads
    for(i=0; i<5; i++){
        pthread_create(&philosophers[i], NULL, philosopher, (void*)&ids[i]);
    }

    for(i=0; i<5; i++){
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}

void *philosopher(void *_id) {
    // obtain philosopher's id
    int id = *(int*) _id;
    while(1){
        // check if four philosopher's already hngry.
        sem_wait(&hungry);
        // obtain chopsticks
        sem_wait(&chopsticks[id]);
        sem_wait(&chopsticks[(id+1)%5]);

        // start eating.
        sleep(2);
        printf("Philosopher %d is eating...\n", id);

        // done eating
        sem_post(&chopsticks[id]);
        sem_post(&chopsticks[(id+1)%5]);
        sem_post(&hungry);
        printf("Philosopher %d thinking...\n", id);
        sleep(5);
    }
    
}
```
