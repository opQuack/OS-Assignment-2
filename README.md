```
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <unistd.h>

#define N 5
#define M 3
// n processes -> m resources

// semaphores
sem_t access_table;
sem_t safety_performed[N];
sem_t perform[N];

// safety algorithm matrix
int available[3] = {3, 3, 2};
int max_resources[N][M] = {0};
int needs[N][M] = {0};
int allocations[N][M] = {0};

void *process(void* _id);
void deadlock_detect();
bool check(int i);

int main() {
    int i;
    int ids[N] = {0};
    pthread_t threads[N];
    
    // initialise the semaphores
    sem_init(&access_table, 0, 1);
    
    // alocate ids and initialise safety performed.
    for(i=0; i<N; i++) { 
        ids[i] = i; 
        sem_init(&safety_performed[i], 0, 1);
        sem_wait(&safety_performed[i]);
        sem_init(&perform[i], 0, 1);
        sem_wait(&perform[i]);
    }
    
    // create the processes.
    for(i=0; i<N; i++) {
        // processes starting to execute.
        int t = pthread_create(&threads[i], NULL, process, (void*) &ids[i]);
    }

    // deadlock detection algorithm
    deadlock_detect();

    // create the processes.
    for(i=0; i<N; i++) { pthread_join(threads[i], NULL); }

    return 0;
}

void *process(void* _id) {
    int j, id = *(int*) _id;
    int max_resource[M], allocated[M];

    // get resource allocation
    for(j=0; j<M; j++) {
        max_resource[j] = rand()%10;
        allocated[j] = rand()%max_resource[j];
    }

    // one process at a time can access the table.
    sem_wait(&access_table);
    for(int j=0; j<M; j++) {
        max_resources[id][j] = max_resource[j];
        allocations[id][j] = allocated[j];
        needs[id][j] = max_resource[j] - allocated[j];
    }

    // release access to table and allow to perform deadlock detection
    sem_post(&access_table);
    sem_post(&perform[id]);

    // waiting for safety algorithm to allow.
    sem_wait(&safety_performed[id]);
    printf("Performing process %d\n", id);
    // relieve resources
    for(int j=0; j<M; j++) {
        available[j] += allocations[id][j];
    }
}

void deadlock_detect() {
    
    // wait for processes to be allocated before performing this
    for(int x=0; x<N; x++)
        sem_wait(&perform[x]);

    int i, j;
    bool finished[N] = {false};
    bool deadlock;
    
    // perform all functions.
    for(i=0; i<N; i++) {
        deadlock = true;
        for(j=0; j<N; j++) {
            // check if this process qualifies
            if(!finished[j] && check(j)){
                // safe. Perform this function.
                deadlock = false;
                finished[j] = true;
                sem_post(&safety_performed[j]);
                sleep(3);
            }
        }
        // no process qualified.
        if(deadlock) {
            printf("System is deadlocked.\n");
            exit(0);
        }
    }

}

bool check(int i) {
    // check if this process can be executed.
    bool res = true;
    for(int k=0; k<M; k++) {
        if(needs[i][k] >= available[k]) { res = false; break; }
    }
    return res;
}
```
