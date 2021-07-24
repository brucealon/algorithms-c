
#ifndef HEAP_H
#define HEAP_H

struct heap {
    void **data;
    int    tail;
    int    size;
};
typedef struct heap heap;

heap *heap_new();
int   heap_empty(heap *h);
int   heap_size(heap *h);
int   heap_tail(heap *h);
void  heap_insert(heap *h, void *key);
void *heap_delmin(heap *h);
heap *heap_free(heap *h);
void  heap_print(heap *h);
#endif
