#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function
void handle_sigint(int sig) {
    printf("\nCaught signal %d (SIGINT). Exiting gracefully...\n", sig);
    // exit(0);
}

int main() {
    // Register signal handler for SIGINT
    signal(SIGINT, handle_sigint);

    printf("Press Ctrl+C to trigger SIGINT...\n");

    // Infinite loop to keep the program running
    while (1) {
        printf("Working...\n");
        sleep(1); // Wait for 1 second
    }

    return 0;
}
