#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <csignal>

#define SOCKET_PATH "/tmp/unix_socket_cpp"
#define BUFFER_SIZE 256

int server_fd;

void reverse_string(char * str) {
	int len = std::strlen(str);

	for (int i = 0; i < len / 2; i ++) {
		std::swap(str[i], str[len-i-1]);
	}
}

void cleanup (int) {
	close(server_fd);
	unlink(SOCKET_PATH);

	std::cout << "\nServer cleaned up and exited.\n";
	exit(0);
}

int main() {
	struct sockaddr_un addr;

	std::signal(SIGINT, cleanup);

	server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (server_fd == -1) {
		std::perror("socket error");
		return 1;
	}
	
	std::memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	std::strcpy(addr.sun_path, SOCKET_PATH);

	unlink(SOCKET_PATH);

	if (bind(server_fd, (struct sockaddr*) &addr, sizeof(addr)) == -1) {
		std::perror("bind error");
		return 1;
	}

	if (listen(server_fd, 5) == -1) {
		std::perror("listen error");
		return 1;
	}

	std::cout << "Server is listening at " << SOCKET_PATH << '\n';
	
	while (true) {
		int client_fd = accept(server_fd, nullptr, nullptr);
		if (client_fd == -1) {
			std::perror("accept error");
			return 1;
		}

		if (fork() == 0) {
			close(server_fd);

			char buffer[BUFFER_SIZE];
			std::memset(buffer, 0, BUFFER_SIZE);

			read(client_fd, buffer, BUFFER_SIZE);
			std::cout << "Received: " << buffer << '\n';

			reverse_string(buffer);
			write(client_fd, buffer, std::strlen(buffer));

			close(client_fd);
			return 0;
		} else {
			close(client_fd);
		}
	}
	return 0;
}
