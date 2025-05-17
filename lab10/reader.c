/**
 * Communication Using Named Pipe (FIFO). Reader.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "myfifo"

int main() {
    int fd;
    char buffer[100];

    // Open the FIFO for reading
    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Read from the FIFO
    read(fd, buffer, sizeof(buffer));
    printf("Received from FIFO: %s\n", buffer);

    // Close and remove the FIFO
    close(fd);
    unlink(FIFO_NAME); // Clean up

    return 0;
}

