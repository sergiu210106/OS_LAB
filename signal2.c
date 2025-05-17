#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

// Signal handler for the parent process
void handle_sigusr1(int sig) {
    printf("Parent received signal %d (SIGUSR1) from child.\n", sig);
}

int main() {
    pid_t pid;

    // Set up signal handler in the parent
    signal(SIGUSR1, handle_sigusr1);

    pid = fork(); // Create child process

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("Child: sleeping for 2 seconds...\n");
        sleep(2); // Let parent get ready
        printf("Child: sending SIGUSR1 to parent (PID %d)\n", getppid());
        kill(getppid(), SIGUSR1); // Send signal to parent
        exit(0);
    } else {
        // Parent process
        printf("Parent: waiting for signal from child (PID %d)...\n", pid);
        pause(); // Wait for signal
        printf("Parent: done.\n");
    }

    return 0;
}
