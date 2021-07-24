
#include <stdio.h>
#include <stdlib.h>

#include "priority_queue.h"

int main(int argc, char *argv[]) {
    priority_queue *h = priority_queue_new();

    priority_queue_insert(h, (void *)1);
    priority_queue_insert(h, (void *)10);
    priority_queue_insert(h, (void *)5);
    priority_queue_insert(h, (void *)11);
    priority_queue_insert(h, (void *)8);
    priority_queue_insert(h, (void *)7);
    priority_queue_insert(h, (void *)3);
    priority_queue_insert(h, (void *)12);
    priority_queue_insert(h, (void *)4);
    priority_queue_insert(h, (void *)2);
    priority_queue_insert(h, (void *)6);
    priority_queue_insert(h, (void *)9);
    priority_queue_print(h);

    int previous = (int)priority_queue_next(h);
    int current = 0;
    while (!priority_queue_empty(h)) {
        current = (int)priority_queue_next(h);
        if (current > previous) {
            fprintf(stderr, "Priority Queue is not in order: %d > %d!\n", current, previous);
            return EXIT_FAILURE;
        }
        previous = current;
    }

    h = priority_queue_free(h);
    return EXIT_SUCCESS;
}
