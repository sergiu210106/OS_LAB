/**
 * Simulate a Bank Account with Multiple Clients
 * Goal: Simulate multiple clients withdrawing and depositing money using proper synchronization.
 * Instructions:
 * 1. Create a shared bank account with a starting balance of 1000.
 * 2. Launch 3 deposit threads and 3 withdrawal threads.
 * 3. Each deposit thread deposits 100 ten times.
 * 4. Each withdrawal thread withdraws 50 twenty times.
 * 5. Protect the shared balance with a mutex.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_DEPOSITORS 3
#define NUM_WITHDRAWERS 3
#define DEPOSIT_AMOUNT 100
#define WITHDRAW_AMOUNT 50
#define DEPOSIT_COUNT 10
#define WITHDRAW_COUNT 20

long balance = 1000;  // Shared bank account balance

pthread_mutex_t balance_mutex;
pthread_cond_t sufficient_funds;  // Used to prevent overdraft

void* depositor(void* arg) {
    for (int i = 0; i < DEPOSIT_COUNT; i++) {
        pthread_mutex_lock(&balance_mutex);

        balance += DEPOSIT_AMOUNT;
        printf("Depositor thread %ld: deposited %d, new balance = %ld\n",
               (long)pthread_self(), DEPOSIT_AMOUNT, balance);

        pthread_cond_signal(&sufficient_funds);  // Signal waiting withdrawers
        pthread_mutex_unlock(&balance_mutex);

        usleep(100000);  // simulate delay
    }
    return NULL;
}

void* withdrawer(void* arg) {
    for (int i = 0; i < WITHDRAW_COUNT; i++) {
        pthread_mutex_lock(&balance_mutex);

        // Wait until balance is sufficient
        while (balance < WITHDRAW_AMOUNT) {
            printf("Withdrawer thread %ld: waiting for sufficient funds...\n", (long)pthread_self());
            pthread_cond_wait(&sufficient_funds, &balance_mutex);
        }

        balance -= WITHDRAW_AMOUNT;
        printf("Withdrawer thread %ld: withdrew %d, new balance = %ld\n",
               (long)pthread_self(), WITHDRAW_AMOUNT, balance);

        pthread_mutex_unlock(&balance_mutex);

        usleep(120000);  // simulate delay
    }
    return NULL;
}

int main() {
    pthread_t depositors[NUM_DEPOSITORS], withdrawers[NUM_WITHDRAWERS];

    pthread_mutex_init(&balance_mutex, NULL);
    pthread_cond_init(&sufficient_funds, NULL);

    // Create depositor threads
    for (int i = 0; i < NUM_DEPOSITORS; i++) {
        if (pthread_create(&depositors[i], NULL, depositor, NULL) != 0) {
            perror("Failed to create depositor thread");
            exit(EXIT_FAILURE);
        }
    }

    // Create withdrawer threads
    for (int i = 0; i < NUM_WITHDRAWERS; i++) {
        if (pthread_create(&withdrawers[i], NULL, withdrawer, NULL) != 0) {
            perror("Failed to create withdrawer thread");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_DEPOSITORS; i++) {
        pthread_join(depositors[i], NULL);
    }
    for (int i = 0; i < NUM_WITHDRAWERS; i++) {
        pthread_join(withdrawers[i], NULL);
    }

    pthread_mutex_destroy(&balance_mutex);
    pthread_cond_destroy(&sufficient_funds);

    printf("Final account balance: %ld\n", balance);
    return 0;
}

