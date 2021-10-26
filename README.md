```
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define SEATS_MAX 10

pthread_mutex_t mutex_seats = PTHREAD_MUTEX_INITIALIZER;
int waiting = 0;

void* barber();
void* customer();

int main(){
    pthread_t thread1,thread2;

    int stat1 = pthread_create(&thread1, NULL, &barber, NULL);
	int stat2 = pthread_create(&thread1, NULL, &customer, NULL);

	pthread_join( thread1, NULL);
   	pthread_join( thread2, NULL);

   	return 0;
}

void *barber(){
	while(1){
		// sleep if no customers
		if(waiting==0) continue;
		// enters critical section
		pthread_mutex_lock(&mutex_seats);
		// cut hair
		waiting = waiting-1;
		// exit critical section
		pthread_mutex_unlock(&mutex_seats);
	}
}

void* customer(){
	while(1){
		// longer than max => leave
		if(waiting==SEATS_MAX) continue;
		// enters critical section
		pthread_mutex_lock(&mutex_seats);
		// cut hair
		waiting = waiting+1;
		// exit critical section
		pthread_mutex_unlock(&mutex_seats);	
	}
}

```
