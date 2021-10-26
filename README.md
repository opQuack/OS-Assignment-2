```
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>


void *philoshoper();

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
bool chopsticks[5] = {false,false,false,false,false};

int main() {
    pthread_t threads[5];
    int ids[5] = {1,2,3,4,5};

    for(int i=0; i<5; i++) {
        int t = pthread_create(&threads[i], NULL, philoshoper, (void*) &ids[i]);
    }

    for(int i=0; i<5; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

void *philoshoper(void *_id) {
    int id = *(int*) _id;
    while(1) {
        // wait till chopsticks are free
        while(chopsticks[id]==true || chopsticks[(id+1)%5]==true);
        // start eating
        pthread_mutex_lock(&mutex);
        chopsticks[id] = chopsticks[(id+1)%5] = true;
        pthread_mutex_unlock(&mutex);
        sleep(2);

        printf("Philosopher %d is eating.\n", id);
        // stop eating and start thinking
        pthread_mutex_lock(&mutex);
        chopsticks[id] = chopsticks[(id+1)%5] = false;
        pthread_mutex_unlock(&mutex);
        printf("Philosopher %d is thinking.\n", id);
        sleep(5);
    }
}









```
