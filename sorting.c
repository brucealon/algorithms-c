
#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <errno.h>
#include <string.h>

#include "input.h"
#include "output.h"
#include "sorting_basic.h"

int main(int argc, char *argv[]) {
    if (argc == 2) {
        int *allowlist = NULL;
        int length = 0;
        printf("Reading....\n");
        int result = read_all_ints(argv[1], &allowlist, &length);
        char buffer[32];
        printf("Sorting %s entries....\n", pint(length, buffer));
        result = heap_sort_integers(allowlist, length);
        if (is_sorted(allowlist, length)) {
            printf("The entries have been sorted.\n");
        } else {
            printf("There is no sorting here.\n");
        }
        free(allowlist);
    } else {
        printf("\nUsage: %s <filename>\n", argv[0]);
        printf("The file should contain integers, one per line.\n");

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
