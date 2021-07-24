
#ifndef QUEUE_H
#define QUEUE_H

struct queue {
    void **data;
    int size;
    int threshhold;
    int head;
    int tail;
};
typedef struct queue queue;

queue *queue_new();
void   queue_push(queue *q, void *data);
void  *queue_pop(queue *q);
int    queue_empty(queue *q);
queue *queue_delete(queue *q);

#endif
