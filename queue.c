
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

queue *queue_new() {
    queue *q = (queue *)malloc(sizeof(queue));
    if (q == NULL) {
        fprintf(stderr, "Failed to allocate memory for queue.\n");
        exit(1);
    }
    q->size = 10;
    q->head = 0;
    q->tail = 0;
    q->threshhold = q->size / 4;
    q->data = malloc(q->size * sizeof(void *));
    if (q->data == NULL) {
        fprintf(stderr, "Failed to allocate memory for queue data.\n");
        exit(1);
    }

    return q;
}

void queue_push(queue *q, void *data) {
    if (q->tail >= q->size) {
        q->size = q->size * 2;
        q->threshhold = q->size / 4;
        q->data = realloc(q->data, q->size * sizeof(void *));
        if (q->data == NULL) {
            fprintf(stderr, "Failed to reallocate memory for queue data.\n");
            exit(1);
        }
    } else if (q->head == q->tail && q->head > 0) {
        q->head = 0;
        q->tail = 0;
    }
    q->data[q->tail++] = data;
}

void *queue_pop(queue *q) {
    if (q->head == q->tail) {
        fprintf(stderr, "Trying to pop from an empty queue.\n");
        return NULL;
    }
    
    if (q->size > 10 && q->head > 0 && (q->tail - q->head) <= q->threshhold) {
        q->size = q->size / 2;
        int i = 0;
        for (int j = q->head; j <= q->tail; j++) {
            q->data[i++] = q->data[j];
        }
        q->head = 0;
        q->tail = i - 1;
        q->threshhold = q->size / 4;
        q->data = realloc(q->data, q->size * sizeof(void *));
        if (q->data == NULL) {
            fprintf(stderr, "Failed to reallocate memory for queue data.\n");
            exit(1);
        }
    }
    return q->data[q->head++];
}

int queue_empty(queue *q) {
    return q->head == q->tail;
}

queue *queue_delete(queue *q) {
    free(q->data);
    free(q);
    
    return NULL;
}

