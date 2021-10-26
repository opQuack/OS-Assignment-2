```
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// structure of the item
struct item {
	int id;
};

struct storage {
	struct item items[100];
	int front, back;
};

// global variables
int count = 0;
struct storage store;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void *producer();
void *consumer();

int main(){
	// setup store
	store.front = store.back = 0;
	pthread_t thread1, thread2;

	// execute producer thread1 and consumer on thread2
	int stat1 = pthread_create(&thread1, NULL, &producer, NULL);
	int stat2 = pthread_create(&thread1, NULL, &consumer, NULL);

	pthread_join( thread1, NULL);
   	pthread_join( thread2, NULL);

   	return 0;
}

// pointer to producer function
void *producer() {
	while(1) {
		// produce a new item
		count++;
		struct item i; i.id = count;

		// store is full.
		while((store.front+1)%100==store.back);

		// add the new item
		pthread_mutex_lock(&mutex1);
		store.front = (store.front+1)%100;
		store.items[store.front] = i;
		printf("Produced item %d at %d\n", count, store.front);
		pthread_mutex_unlock(&mutex1);
	}
}

// pointer to consumer function
void *consumer() {
	while(1) {
		// store is empty
		while(store.front==store.back);

		// consume an item
		pthread_mutex_lock(&mutex1);
		struct item i = store.items[store.back];
		printf("Consumed item at %d\n", store.back);
		store.back = (store.back+1)%100;
		pthread_mutex_unlock(&mutex1);
	}
}
```
