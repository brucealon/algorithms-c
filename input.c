
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int read_all_ints(char *filename, int **integers, int *length) {
    int initial_allocation = 1024;
    int bufflen = 4096;
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Failed to open %s: %s\n", filename, strerror(errno));
        exit(1);
    }

    char buffer[bufflen];
    int rlen = read(fd, buffer, bufflen);
    char in[16];
    int inidx = 0;
    int intidx = 0;
    while (rlen > 0) {
        for (int bidx = 0; bidx < rlen; bidx++) {
            if (buffer[bidx] == '\n') {
                in[inidx] = '\0';
                if (intidx >= *length) {
                    if (*length == 0) {
                        *integers = malloc(sizeof(int) * initial_allocation);
                        if (*integers == NULL) {
                            fprintf(stderr, "Error during allocation: %s\n", strerror(errno));
                            exit(1);
                        }
                        *length = initial_allocation;
                    } else {
                        *integers = realloc(*integers, sizeof(int) * (*length) * 2);
                        if (*integers == NULL) {
                            fprintf(stderr, "Error during allocation: %s\n", strerror(errno));
                            exit(1);
                        }
                        *length = (*length) * 2;
                    }
                }
                (*integers)[intidx++] = atoi(in);
                inidx = 0;
            } else {
                in[inidx++] = buffer[bidx];
            }
        }
        rlen = read(fd, buffer, bufflen);
    }
    *length = intidx;

    close(fd);
    return intidx;
}

