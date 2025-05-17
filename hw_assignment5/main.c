#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char * filename = argv[1];

    FILE * fp = fopen(filename, "rb+");

    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    rewind(fp);

    if (filesize <= 1) {
        fclose(fp);
        return 0;
    }

    long readPos = 1;
    long writePos = 0;
    int byte;

    while (readPos < filesize) {
        fseek(fp, readPos, SEEK_SET);
        byte = fgetc(fp);

        if (byte == EOF) {
            break;
        }

        fseek(fp, writePos, SEEK_SET);
        fputc(byte, fp);

        readPos += 2;
        writePos += 1;
    }

    if (ftruncate(fileno(fp), writePos) != 0) {
        perror("Error truncating file");
        fclose(fp);
        return 1;
    }

    fclose(fp);
    return 0;
}