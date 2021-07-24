
#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

int main(int argc, char *argv[]) {
    heap *h = heap_new();

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

    int previous = heap_next(h);
    int current = 0;
    while (!heap_empty(h)) {
        current = heap_next(h);
        if (current < previous) {
            fprintf(stderr, "Heap is not in order: %d < %d!\n", current, previous);
            return EXIT_FAILURE;
        }
        previous = current;
    }

    h = heap_free(h);
    return EXIT_SUCCESS;
}
