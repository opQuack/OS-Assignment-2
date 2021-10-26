```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

void *writers();
void *readers();

sem_t rw_lock;
sem_t count_lock;
int r_count = 0;

int main() {
    pthread_t writer, reader[5];

    int w = pthread_create(&writer, NULL, writers, NULL);
    for(int i=0; i<5; i++) {
        int r = pthread_create(&reader[i], NULL, readers, NULL);
    }

    pthread_join(writer, NULL);
    for(int i=0; i<5; i++) {
        int r = pthread_create(reader[i], NULL, readers, NULL);
    }

    return 0;
}

void *writers() {
    while(1) {
        // request the rw_lock
        sem_wait(&rw_lock);
        // start writing
        printf("Writer is writing.\n");
        sleep(5);
        // release the rw_lock because done writing.
        sem_post(&rw_lock);
    }
    
}

void *readers() {
    while(1) {
        // new reader comes in
        sem_wait(&count_lock);
        r_count++;
        printf("Readers : %d\n", r_count);
        // if first reader then wait to obtain rw_lock
        if(r_count == 1)
            sem_wait(&rw_lock);
        sem_post(&count_lock);

        // start reading
        printf("Reader is reading.\n");
        sleep(2);
        
        // done reading
        sem_wait(&count_lock);
        r_count--;
        // if all readers done then release rw_lock
        if(r_count == 0)
            sem_post(&rw_lock);
        sem_post(&count_lock);
    }
    
}
```
