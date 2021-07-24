
#include <stdio.h>
#include <stdlib.h>

#include "priority_queue.h"

int main(int argc, char *argv[]) {
    printf("Getting priority_queue...\n");
    priority_queue *h = priority_queue_new();
    printf("Have priority_queue...\n");

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
    printf("Priority Queue Size: %d\n", priority_queue_size(h));

    while (!priority_queue_empty(h)) {
        printf("%ld,", priority_queue_delmax(h));
    }
    printf("\n");
    printf("Priority Queue Size: %d\n", priority_queue_size(h));

    h = priority_queue_free(h);
    return EXIT_SUCCESS;
}
