
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

int main(int argc, char *argv[]) {
    queue *q = queue_new();
    if (q == NULL) {
        fprintf(stderr, "Failed to allocation memory for queue.\n");
        exit(1);
    }

    for (long i = 1; i < 201; i++) {
        printf("Push: %ld\n", i);
        queue_push(q, (void *)i);
    }

    while (!queue_empty(q)) {
        long i = (long)queue_pop(q);
        printf("Pop: %ld\n", i);
    }
    queue_push(q, (void *)1);
    printf("Queue Size: %d\n", q->size);
    printf("Queue Head: %d\n", q->head);
    printf("Queue Tail: %d\n", q->tail);
    printf("Queue Threshhold: %d\n", q->threshhold);
    
    q = queue_delete(q);
}
