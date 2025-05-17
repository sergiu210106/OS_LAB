#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 100
#define NUM_THREADS 4

int numbers[ARRAY_SIZE];
long total_sum = 0;

// mutex is used for synchronization
pthread_mutex_t sum_mutex;

// Each thread calculates the sum of its segment in
void* partial_sum(void* arg) {
    int index = *(int*)arg;
    free(arg); // Free allocated memory

    int start = index * (ARRAY_SIZE / NUM_THREADS);
    int end = start + (ARRAY_SIZE / NUM_THREADS);
    long local_sum = 0;

    for (int i = start; i < end; i++) {
        local_sum += numbers[i];
    }

    // Protect the global sum with a mutex
    pthread_mutex_lock(&sum_mutex);
    total_sum += local_sum; // semafor pentru threaduri
    pthread_mutex_unlock(&sum_mutex);

    return NULL;
}

int main() {
    // Initialize the array with values 1 to 100
    for (int i = 0; i < ARRAY_SIZE; i++) {
        numbers[i] = i + 1;
    }

    pthread_t threads[NUM_THREADS];
    // initialize the mutex
    pthread_mutex_init(&sum_mutex, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        int* index = malloc(sizeof(int));
        if (index == NULL) {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
        *index = i;

        if (pthread_create(&threads[i], NULL, partial_sum, index) != 0) {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }
    // wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    // clear the mutex
    pthread_mutex_destroy(&sum_mutex);

    printf("Total sum = %ld\n", total_sum);
    return 0;
}

