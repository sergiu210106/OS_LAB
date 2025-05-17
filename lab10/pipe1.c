/**
 * One-Way Pipe Communication (Parent to Child)
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int pipefd[2]; // pipefd[0] - read end, pipefd[1] - write end
    pid_t pid;
    char message[] = "Hello from parent";
    char buffer[100];

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        // Child process
        close(pipefd[1]); // Close the write end

        // Read message from the pipe
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Child received message: %s\n", buffer);

        close(pipefd[0]); // Close the read end
    }
    else {
        // Parent process
        close(pipefd[0]); // Close the read end

        // Write message to the pipe
        write(pipefd[1], message, strlen(message) + 1); // +1 to include null terminator

        close(pipefd[1]); // Close the write end
	wait(0);
    }

    return 0;
}
