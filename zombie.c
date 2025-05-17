#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("Child process (PID %d) exiting...\n", getpid());
        exit(0); // Exits immediately
    } else {
        // Parent process
        printf("Parent process (PID %d), child PID: %d\n", getpid(), pid);
        printf("Child is now a zombie. Sleeping for 30 seconds...\n");
        sleep(30); // During this time, child is a zombie
        printf("Parent exiting without calling wait()\n");
    }

    return 0;
}
