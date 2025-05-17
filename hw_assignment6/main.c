#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>

#include <unistd.h>
#include <fcntl.h>

int computeSum (int arr[], int left, int right) {
    if (left == right) {
        return arr[left];
    }

    int mid = left + (right-left)/2;

    int pipefd1[2], pipefd2[2];
    pipe(pipefd1);
    pipe(pipefd2);

    pid_t pid1 = fork();

    if (pid1 == 0) {
        int sum1 = computeSum(arr, left, mid);

        write(pipefd1[1], &sum1, sizeof(int));
        close(pipefd1[0]);
        close(pipefd1[1]);

        exit(0);
    }

    pid_t pid2 = fork();

    if (pid2 == 0) {
        int sum2 = computeSum(arr, mid+1, right);

        write(pipefd2[1], &sum2, sizeof(int));
        close(pipefd2[0]);
        close(pipefd2[1]);

        exit(0);
    }

    int sum1, sum2;

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    read(pipefd1[0], &sum1, sizeof(int));
    read(pipefd2[0], &sum2, sizeof(int));

    close(pipefd1[0]);
    close(pipefd1[1]);
    close(pipefd2[0]);
    close(pipefd2[1]);

    return sum1 + sum2;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};

    int sum = computeSum(arr, 0, 8-1);

    printf("Sum of array = %d\n", sum);

    return 0;
}
/*
sergiu@Sergiu:~$ cd lab_os
sergiu@Sergiu:~/lab_os$ cd hw_assignment6
sergiu@Sergiu:~/lab_os/hw_assignment6$ gcc -o app main.c
sergiu@Sergiu:~/lab_os/hw_assignment6$ ./app
Sum of array = 36
*/