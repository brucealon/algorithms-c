
#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

int main(int argc, char *argv[]) {
    printf("Getting heap...\n");
    heap *h = heap_new();
    printf("Have heap...\n");

    heap_insert(h, (void *)1);
    heap_insert(h, (void *)10);
    heap_insert(h, (void *)5);
    heap_insert(h, (void *)11);
    heap_insert(h, (void *)8);
    heap_insert(h, (void *)7);
    heap_insert(h, (void *)3);
    heap_insert(h, (void *)12);
    heap_insert(h, (void *)4);
    heap_insert(h, (void *)2);
    heap_insert(h, (void *)6);
    heap_insert(h, (void *)9);
    heap_print(h);
    printf("Priority Queue Size: %d\n", heap_size(h));

    while (!heap_empty(h)) {
        printf("%ld,", heap_delmin(h));
    }
    printf("\n");
    printf("Priority Queue Size: %d\n", heap_size(h));

    h = heap_free(h);
    return EXIT_SUCCESS;
}
