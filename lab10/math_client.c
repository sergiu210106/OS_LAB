#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define REQUEST_FIFO "request_fifo"
#define RESPONSE_FIFO "response_fifo"

int main() {
    char operation[100];
    char result[100];
    int req_fd, res_fd;

    // Create FIFOs if they don't exist
    mkfifo(REQUEST_FIFO, 0666);
    mkfifo(RESPONSE_FIFO, 0666);

    // Get input from user
    printf("Enter operation (e.g., ADD 3 5): ");
    fgets(operation, sizeof(operation), stdin);
    operation[strcspn(operation, "\n")] = '\0'; // Remove newline

    // Open request FIFO and write the operation
    req_fd = open(REQUEST_FIFO, O_WRONLY);
    write(req_fd, operation, strlen(operation) + 1);
    close(req_fd);

    // Open response FIFO and read the result
    res_fd = open(RESPONSE_FIFO, O_RDONLY);
    read(res_fd, result, sizeof(result));
    close(res_fd);

    printf("Result from server: %s\n", result);

    return 0;
}

