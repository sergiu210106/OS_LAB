#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    FILE *f1;
    FILE *f2;

    f1 = popen("ls -l", "r");
    if (f1 == NULL) {
        perror("popen ls -l");
        exit(EXIT_FAILURE);
    }

    f2 = popen("sort", "w");
    if (f2 == NULL) {
        perror("popen sort");
        pclose(f1);
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), f1)) {
        fprintf(f2, "%s", line);
    }

    pclose(f1);
    pclose(f2);

    return 0;
}
