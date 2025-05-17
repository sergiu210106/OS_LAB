/**
 * Bidirectional Pipe Communication
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int pipe1[2]; // Parent to Child
    int pipe2[2]; // Child to Parent
    pid_t pid;
    int number = 5;
    int result;

    // Create both pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the process
    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        // Child process

        // Close unused ends
        close(pipe1[1]); // Close write end of pipe1
        close(pipe2[0]); // Close read end of pipe2

        // Read number from parent
        read(pipe1[0], &number, sizeof(number));
        printf("Child received number: %d\n", number);

        // Compute square
        result = number * number;

        // Send result back to parent
        write(pipe2[1], &result, sizeof(result));

        // Close used ends
        close(pipe1[0]);
        close(pipe2[1]);
    }
    else {
        // Parent process

        // Close unused ends
        close(pipe1[0]); // Close read end of pipe1
        close(pipe2[1]); // Close write end of pipe2

        // Send number to child
        printf("Parent sent number: %d\n", number);
        write(pipe1[1], &number, sizeof(number));

        // Read result from child
        read(pipe2[0], &result, sizeof(result));
        printf("Parent received result: %d\n", result);

        // Close used ends
        close(pipe1[1]);
        close(pipe2[0]);
    }
    wait(0);
    return 0;
}

