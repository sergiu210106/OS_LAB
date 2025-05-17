#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define REQUEST_FIFO "request_fifo"
#define RESPONSE_FIFO "response_fifo"

int main() {
    char buffer[100], response[100];
    char op[10];
    int a, b, res;
    int req_fd, res_fd;

    // Create FIFOs if they don't exist
    mkfifo(REQUEST_FIFO, 0666);
    mkfifo(RESPONSE_FIFO, 0666);

    printf("Math server is running...\n");

    while (1) {
        // Open request FIFO for reading
        req_fd = open(REQUEST_FIFO, O_RDONLY);
        read(req_fd, buffer, sizeof(buffer));
        close(req_fd);

        printf("Received: %s\n", buffer);

        // Parse the operation
        if (sscanf(buffer, "%s %d %d", op, &a, &b) != 3) {
            snprintf(response, sizeof(response), "Invalid input format");
        } else {
            if (strcmp(op, "ADD") == 0)
                res = a + b;
            else if (strcmp(op, "SUB") == 0)
                res = a - b;
            else if (strcmp(op, "MUL") == 0)
                res = a * b;
            else if (strcmp(op, "DIV") == 0) {
                if (b == 0)
                    snprintf(response, sizeof(response), "Error: Divide by zero");
                else
                    res = a / b;
            } else {
                snprintf(response, sizeof(response), "Unknown operation");
            }

            if (strncmp(response, "Error", 5) != 0 && strncmp(response, "Unknown", 7) != 0 && strncmp(response, "Invalid", 7) != 0) {
                snprintf(response, sizeof(response), "%d", res);
            }
        }

        // Send response
        res_fd = open(RESPONSE_FIFO, O_WRONLY);
        write(res_fd, response, strlen(response) + 1);
        close(res_fd);
    }

    return 0;
}

