#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 1024

int main() {
    int pipe12[2], pipe13[2], pipe14[2];

    pipe(pipe12);
    pipe(pipe13); 
    pipe(pipe14); 

    pid_t pid2 = fork();
    if (pid2 == 0) {
        close(pipe12[1]);
        dup2(pipe12[0], STDIN_FILENO); 
        close(pipe12[0]);
        printf("Process 2 (letters):\n");
        char line[MAX_LINE];
        while (fgets(line, MAX_LINE, stdin)) {
            printf("2: %s", line);
        }
        exit(0);
    }

    pid_t pid3 = fork();
    if (pid3 == 0) {
        close(pipe13[1]);
        dup2(pipe13[0], STDIN_FILENO);
        close(pipe13[0]);
        printf("Process 3 (digits):\n");
        char line[MAX_LINE];
        while (fgets(line, MAX_LINE, stdin)) {
            printf("3: %s", line);
        }
        exit(0);
    }

    pid_t pid4 = fork();
    if (pid4 == 0) {
        close(pipe14[1]);
        dup2(pipe14[0], STDIN_FILENO);
        close(pipe14[0]);
        printf("Process 4 (others):\n");
        char line[MAX_LINE];
        while (fgets(line, MAX_LINE, stdin)) {
            printf("4: %s", line);
        }
        exit(0);
    }

    close(pipe12[0]);
    close(pipe13[0]);
    close(pipe14[0]);

    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, stdin)) {
        if (isalpha(line[0])) {
            write(pipe12[1], line, strlen(line));
        } else if (isdigit(line[0])) {
            write(pipe13[1], line, strlen(line));
        } else {
            write(pipe14[1], line, strlen(line));
        }
    }

    close(pipe12[1]);
    close(pipe13[1]);
    close(pipe14[1]);

    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}
