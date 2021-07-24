
#ifndef STACK_H
#define STACK_H

struct stack {
    void **data;
    int size;
    int tail;
};
typedef struct stack stack;

stack *stack_new();
void   stack_push(stack *s, void *data);
void  *stack_pop(stack *s);
int    stack_empty(stack *s);
stack *stack_delete(stack *s);

#endif
