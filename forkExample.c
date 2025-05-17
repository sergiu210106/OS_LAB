/* fork_1.c
Create a child process using fork()
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int a = 5;
	int pid = fork();

	if (pid == -1) {
		perror("fork() error \n");
		exit(EXIT_FAILURE);
	}

	if (pid == 0) {
		printf("a is %d\n", a);
		printf("[In CHILD] My PID is %d. My parent is %d.\n", getpid(), getppid());
	       	sleep(30);
		exit(EXIT_SUCCESS);
	}

	else {
		printf("[In parent] My PID is %d. My child PID is %d.\n", getpid(), pid);
		int status;
		wait(&status);
	}

	return 0;
}
