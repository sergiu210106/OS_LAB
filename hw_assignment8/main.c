#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include <stdbool.h>

#define BUF_SIZE 1024

void replaceVowels(char * line) {
	for (int i = 0; i < strlen(line); i ++) {
		switch(line[i]) {
			case 'a': line[i] = '1'; break;
			case 'e': line[i] = '2'; break;
			case 'i': line[i] = '3'; break;
			case 'o': line[i] = '4'; break;
			case 'u': line[i] = '5'; break;
		}
	}
}

bool isAlphanumericLine(const char * line) {
	for (int i = 0; i < strlen(line); i++) {
		if (!isalnum(line[i]) && !isspace(line[i])) {
			return false;
		}
	}
	return true;
}

int main () {
	int pipe1to3[2], pipe3to2[2];
	pipe(pipe1to3);
	pipe(pipe3to2);

	pid_t pid1 = fork();
	if (pid1 == 0) {
		close(pipe1to3[0]);
		char buffer[BUF_SIZE];
		while(fgets(buffer, BUF_SIZE, stdin)) {
			write(pipe1to3[1], buffer, strlen(buffer));
		}
		close(pipe1to3[1]);
		exit(0);
	}

	pid_t pid2 = fork();
	if (pid2 == 0) {
		close(pipe3to2[1]);

		char buffer[BUF_SIZE];
		int n;

		while ((n = read(pipe3to2[0], buffer, BUF_SIZE)) > 0) {
			buffer[n] = '\0';
			replaceVowels(buffer);
			printf("%s", buffer);
		}

		close(pipe3to2[0]);
		exit(0);
	}

	close(pipe1to3[1]);
	close(pipe3to2[0]);

	char buffer[BUF_SIZE];
	int n;

	while ((n = read(pipe1to3[0], buffer, BUF_SIZE)) > 0) {
		buffer[n] = '\0';

		if (isAlphanumericLine(buffer)) {
			write(pipe3to2[1], buffer, strlen(buffer));
		}
	}

	close(pipe1to3[0]);
	close(pipe3to2[1]);

	return 0;
}

