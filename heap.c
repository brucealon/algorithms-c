
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

heap *heap_new() {
    heap *h = (heap *)malloc(sizeof(heap));
    h->data = malloc(sizeof(void *) * 10);
    h->tail = 0;
    h->size = 10;

    return h;
}

void heap_exchange(heap *h, int idx, int jdx) {
    void *key = h->data[idx];
    h->data[idx] = h->data[jdx];
    h->data[jdx] = key;
}

int heap_empty(heap *h) {
    return h->tail == 0;
}

int heap_size(heap *h) {
    return h->size;
}

int heap_tail(heap *h) {
    return h->tail;
}

int heap_depth(heap *h) {
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

void heap_swim(heap *h, int idx) {
    while (idx > 1 && h->data[idx / 2] > h->data[idx]) {
        heap_exchange(h, idx, idx / 2);
        idx = idx / 2;
    }
}

void heap_sink(heap *h, int idx) {
    while (idx * 2 <= h->tail) {
        int child = idx * 2;
        if (child < h->tail && h->data[child] > h->data[child + 1]) {
            child++;
        }
        if (h->data[idx] <= h->data[child]) {
            break;
        }
        heap_exchange(h, idx, child);
        idx = child;
    }
}

void heap_insert(heap *h, void *key) {
    if (h->tail >= h->size - 1) {
        h->size = h->size * 2;
        h->data = realloc(h->data, h->size * sizeof(void *));
        if (h->data == NULL) {
            fprintf(stderr, "Failed to reallocate memory for heap.\n");
            exit(1);
        }
    }
    h->data[++h->tail] = key;
    heap_swim(h, h->tail);
}

void *heap_next(heap *h) {
    void *key = h->data[1];
    h->data[1] = h->data[h->tail];
    h->data[h->tail--] = 0;
    heap_sink(h, 1);

    if (h->size > 10 && h->tail < (h->size / 4)) {
        h->size = h->size / 2;
        h->data = realloc(h->data, h->size * sizeof(void *));
        if (h->data == NULL) {
            fprintf(stderr, "Failed to reallocate memory for heap.\n");
            exit(1);
        }
    }

    return key;
}

heap *heap_free(heap *h) {
    free(h->data);
    free(h);

    return NULL;
}

void heap_print_internal(heap *h, int idx, int indent) {
    if (h->tail == 0) {
        printf("Heap is empty.\n");
    } else if (idx <= h->tail) {
        for (int i = 0; i < indent; i++) printf("  ");
        printf("%ld\n", h->data[idx]);
        heap_print_internal(h, idx * 2, indent + 2);
        heap_print_internal(h, (idx * 2) + 1, indent + 2);
    }
}

void heap_print(heap *h) {
    heap_print_internal(h, 1, 0);
}
