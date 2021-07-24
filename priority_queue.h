
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

struct priority_queue {
    void **data;
    int    tail;
    int    size;
};
typedef struct priority_queue priority_queue;

priority_queue *priority_queue_new();
int             priority_queue_empty(priority_queue *h);
int             priority_queue_size(priority_queue *h);
int             priority_queue_tail(priority_queue *h);
void            priority_queue_insert(priority_queue *h, void *key);
void           *priority_queue_delmax(priority_queue *h);
priority_queue *priority_queue_free(priority_queue *h);
void            priority_queue_print(priority_queue *h);
#endif
