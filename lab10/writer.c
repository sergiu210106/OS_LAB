/*
 * Communication Using Named Pipe (FIFO). Writer
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define FIFO_NAME "myfifo"

int main() {
    int fd;
    char message[100];

    // Create the named pipe (FIFO) if it does not exist
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo");
    }

    // Open the FIFO for writing
    fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Get input from user
    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove newline

    // Write the message to FIFO
    write(fd, message, strlen(message) + 1); // Include null terminator

    // Close the FIFO
    close(fd);

    return 0;
}

