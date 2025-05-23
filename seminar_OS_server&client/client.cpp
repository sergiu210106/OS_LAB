#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/unix_socket_cpp"
#define BUFFER_SIZE 256

int main () {
    int client_fd;
    struct sockaddr_un addr;
    char buffer[BUFFER_SIZE];

    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_fd == -1) {
        std::perror("socket error");
        return 1;
    }

    std::memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    std::strcpy(addr.sun_path, SOCKET_PATH);

    // connect
    if (connect(client_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        std::perror("connect error");
        return 1;
    }

    std::cout << "Enter message to send: ";
    std::cin.getline(buffer, BUFFER_SIZE);

    write(client_fd, buffer, std::strlen(buffer));

    std::memset(buffer, 0, BUFFER_SIZE);
    read(client_fd, buffer, BUFFER_SIZE);

    std::cout << "Reversed from server: " << buffer << '\n';

    close (client_fd);

    return 0;
}