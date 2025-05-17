/**
* Producer-Consumer with Condition Variables
* Goal: Implement a bounded-buffer (circular queue) using threads, mutexes, and condition variables
* Instructions:
*  1. Create a buffer with a fixed size (e.g., 5 items).
*  2. Implement a producer thread that adds numbers to the buffer.
*  3. Implement a consumer thread that removes and prints numbers.
*  4. Use pthread_mutex_t and pthread_cond_t to synchronize access
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 10

// Shared buffer and control variables
int buffer[BUFFER_SIZE];
int count = 0;  // number of items in the buffer
int in = 0;     // index where the producer inserts the item
int out = 0;    // index where the consumer removes the item

// Mutex for synchronizing access to the buffer
pthread_mutex_t mutex;

// Condition variables
pthread_cond_t not_empty;  // signaled when buffer becomes non-empty
pthread_cond_t not_full;   // signaled when buffer has space

// Producer thread function
void* producer(void* arg) {
    for (int i = 1; i <= NUM_ITEMS; i++) {
        pthread_mutex_lock(&mutex);  // Lock mutex before accessing buffer

        // Wait while the buffer is full
        while (count == BUFFER_SIZE) {
            // pthread_cond_wait unlocks the mutex and waits for not_full signal
            pthread_cond_wait(&not_full, &mutex);
        }

        // Insert item into buffer
        buffer[in] = i;
        printf("Producer: produced %d\n", i);
        in = (in + 1) % BUFFER_SIZE;
        count++;

        // Signal that the buffer is not empty anymore
        pthread_cond_signal(&not_empty);

        pthread_mutex_unlock(&mutex);  // Unlock mutex after accessing buffer

        usleep(100000);  // simulate work (0.1 sec)
    }
    return NULL;
}

// Consumer thread function
void* consumer(void* arg) {
    for (int i = 1; i <= NUM_ITEMS; i++) {
        pthread_mutex_lock(&mutex);  // Lock mutex before accessing buffer

        // Wait while the buffer is empty
        while (count == 0) {
            // pthread_cond_wait unlocks the mutex and waits for not_empty signal
            pthread_cond_wait(&not_empty, &mutex);
        }

        // Remove item from buffer
        int item = buffer[out];
        printf("Consumer: consumed %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        count--;

        // Signal that the buffer has space again
        pthread_cond_signal(&not_full);

        pthread_mutex_unlock(&mutex);  // Unlock mutex after accessing buffer

        usleep(150000);  // simulate work (0.15 sec)
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize mutex and condition variables
    pthread_mutex_init(&mutex, NULL);

    // pthread_cond_init initializes a condition variable for signaling
    pthread_cond_init(&not_empty, NULL);
    pthread_cond_init(&not_full, NULL);

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for both threads to complete
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Cleanup: destroy mutex and condition variables
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_empty);
    pthread_cond_destroy(&not_full);

    return 0;
}

