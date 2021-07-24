
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#include "priority_queue.h"

priority_queue *priority_queue_new() {
    priority_queue *h = (priority_queue *)malloc(sizeof(priority_queue));
    h->data = malloc(sizeof(void *) * 10);
    h->tail = 0;
    h->size = 10;

    return h;
}

void priority_queue_exchange(priority_queue *h, int idx, int jdx) {
    void *key = h->data[idx];
    h->data[idx] = h->data[jdx];
    h->data[jdx] = key;
}

int priority_queue_empty(priority_queue *h) {
    return h->tail == 0;
}

int priority_queue_size(priority_queue *h) {
    return h->size;
}

int priority_queue_tail(priority_queue *h) {
    return h->tail;
}

int priority_queue_depth(priority_queue *h) {
    if (h->tail == 0) {
        return 0;
    }

    int depth = 1;
    int idx = h->tail;
    while (idx > 1) {
        depth++;
        idx = idx / 2;
    }

    return depth;
}

void priority_queue_swim(priority_queue *h, int idx) {
    while (idx > 1 && h->data[idx / 2] < h->data[idx]) {
        priority_queue_exchange(h, idx, idx / 2);
        idx = idx / 2;
    }
}

void priority_queue_sink(priority_queue *h, int idx) {
    while (idx * 2 <= h->tail) {
        int child = idx * 2;
        if (child < h->tail && h->data[child] < h->data[child + 1]) {
            child++;
        }
        if (h->data[idx] >= h->data[child]) {
            break;
        }
        priority_queue_exchange(h, idx, child);
        idx = child;
    }
}

void priority_queue_insert(priority_queue *h, void *key) {
    if (h->tail >= h->size - 1) {
        h->size = h->size * 2;
        h->data = realloc(h->data, h->size * sizeof(void *));
        if (h->data == NULL) {
            fprintf(stderr, "Failed to reallocate memory for priority_queue.\n");
            exit(1);
        }
    }
    h->data[++h->tail] = key;
    priority_queue_swim(h, h->tail);
}

void *priority_queue_next(priority_queue *h) {
    void *key = h->data[1];
    h->data[1] = h->data[h->tail];
    h->data[h->tail--] = 0;
    priority_queue_sink(h, 1);

    if (h->size > 10 && h->tail < (h->size / 4)) {
        h->size = h->size / 2;
        h->data = realloc(h->data, h->size * sizeof(void *));
        if (h->data == NULL) {
            fprintf(stderr, "Failed to reallocate memory for priority_queue.\n");
            exit(1);
        }
    }

    return key;
}

priority_queue *priority_queue_free(priority_queue *h) {
    free(h->data);
    free(h);

    return NULL;
}

void priority_queue_print_internal(priority_queue *h, int idx, int indent) {
    if (h->tail == 0) {
        printf("Priority_Queue is empty.\n");
    } else if (idx <= h->tail) {
        for (int i = 0; i < indent; i++) printf("  ");
        printf("%ld\n", h->data[idx]);
        priority_queue_print_internal(h, idx * 2, indent + 2);
        priority_queue_print_internal(h, (idx * 2) + 1, indent + 2);
    }
}

void priority_queue_print(priority_queue *h) {
    priority_queue_print_internal(h, 1, 0);
}
