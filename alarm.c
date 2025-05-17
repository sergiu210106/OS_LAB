#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Signal handler for SIGALRM
void handle_alarm(int sig) {
    printf("Received signal %d (SIGALRM): 3 seconds passed!\n", sig);

    // Reset alarm for another 3 seconds
    alarm(3);
}

int main() {
    // Register the signal handler
    signal(SIGALRM, handle_alarm);

    // Set the initial alarm
    alarm(3);

    printf("Starting 3-second repeating timer. Press Ctrl+C to stop.\n");

    // Infinite loop to keep the program running
    while (1) {
        pause(); // Wait for the next signal
    }

    return 0;
}
