
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void fail(char *message) {
    fprintf(stderr, "%s: %s\n", message, strerror(errno));
    exit(1);
}

void fd_fail(char *filename, char *action) {
    fprintf(stderr, "Error %s %s: %s\n", action, filename, strerror(errno));
    exit(1);
}

int read_all_ints(char *filename, int **integers, int *length) {
    int initial_allocation = 1024;
    int bufflen = 4096;
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        fd_fail(filename, "opening");

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
                        if (*integers == NULL)
                            fail("Error during allocation");
                        *length = initial_allocation;
                    } else {
                        *integers = realloc(*integers, sizeof(int) * (*length) * 2);
                        if (*integers == NULL)
                            fail("Error during re-allocation");
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

void read_words(char *filename, int (*callback)(char *word, int wordlen, void *extra), void *extra) {
    int max_word_len = 64;
    int bufflen = 4096;
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        fd_fail(filename, "opening");

    char buffer[bufflen];
    int rlen = read(fd, buffer, bufflen);
    char word[max_word_len];
    int widx = 0;
    while (rlen > 0) {
        for (int bidx = 0; bidx < rlen; bidx++) {
            switch (buffer[bidx]) {
            case '\n':
            case '\r':
            case ' ':
            case '\t':
            case '\0':
            case '.':
            case ',':
            case ';':
            case ':':
            case '?':
            case '"':
                if (widx > 0) {
                    word[widx++] = '\0';
                    callback(word, widx, extra);
                    widx = 0;
                }
                break;
            default:
                word[widx++] = buffer[bidx];
                break;
            }

            if (widx >= (max_word_len - 1)) {
                word[widx++] = '\0';
                callback(word, widx, extra);
                widx = 0;
            }
        }

        rlen = read(fd, buffer, bufflen);
    }

    if (widx > 0) {
        word[widx++] = '\0';
        callback(word, widx, extra);
    }

    close(fd);
}

int safe_filename(char *dest, char *source, int length) {
    strncpy(dest, source, length);
    if (strlen(source) >= length) {
        dest[length - 1] = '\0';
    }

    return 0;
}
