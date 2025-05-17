#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

void* print_hello(void* arg) {
    int thread_num = *(int*)arg;
    pthread_t tid = pthread_self();
    printf("Hello from thread %d (pthread ID: %lu)\n", thread_num, (unsigned long)tid);
    free(arg); // Free memory allocated in main
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        int* thread_num = malloc(sizeof(int));
        if (thread_num == NULL) {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
        *thread_num = i + 1;

        if (pthread_create(&threads[i], NULL, print_hello, thread_num) != 0) {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
	// ensures the main thread waits for all child threads to finish.
        pthread_join(threads[i], NULL);
    }

    return 0;
}

