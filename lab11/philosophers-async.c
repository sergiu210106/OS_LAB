/**
 * C implementation of the Dining Philosophers Problem using the asymmetric strategy to avoid deadlock
 * Even-numbered philosophers pick up the left fork first, then the right.
 * Odd-numbered philosophers pick up the right fork first, then the left.
 * This simple strategy breaks the circular wait condition and avoids deadlock.
 *
 * Each fork is protected by a mutex.
 * No deadlock occurs because philosophers don’t all follow the same locking order.
 * Simulates thinking and eating time using usleep() with randomness.
 *
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];

void think(int id) {
    printf("Philosopher %d is thinking...\n", id);
    usleep(rand() % 1000000); // simulate random thinking time
}

void eat(int id) {
    printf("Philosopher %d is eating...\n", id);
    usleep(rand() % 1000000); // simulate random eating time
}

void* philosopher(void* arg) {
    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        think(id);

        if (id % 2 == 0) {
            // Even: pick up left first, then right
            pthread_mutex_lock(&forks[left]);
            pthread_mutex_lock(&forks[right]);
        } else {
            // Odd: pick up right first, then left
            pthread_mutex_lock(&forks[right]);
            pthread_mutex_lock(&forks[left]);
        }

        eat(id);

        // Put down forks
        pthread_mutex_unlock(&forks[left]);
        pthread_mutex_unlock(&forks[right]);
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    srand(time(NULL)); // seed randomness

    // Initialize all fork mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create a thread for each philosopher
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        if (pthread_create(&threads[i], NULL, philosopher, &ids[i]) != 0) {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads (optional in this case, as they loop infinitely)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Cleanup (won't be reached in this infinite-loop example)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}

