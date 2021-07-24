
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

stack *stack_new() {
    stack *s = (stack *)malloc(sizeof(stack));
    s->data = malloc(sizeof(void *) * 10);
    s->size = 10;
    s->tail = 0;
    return s;
}

void stack_push(stack *s, void *data) {
    if (s->tail >= s->size) {
        s->size = s->size * 2;
        s->data = realloc(s->data, s->size * sizeof(void *));
        if (s->data == NULL) {
            fprintf(stderr, "Failed to reallocate memory for stack.\n");
            exit(1);
        }
    }
    s->data[s->tail++] = data;
}

void *stack_pop(stack *s) {
    if (s->tail == 0) {
        fprintf(stderr, "Trying to pop from an empty stack.\n");
        return NULL;
    }
    
    if (s->size > 10 && s->tail <= (s->size / 4)) {
        s->size = s->size / 2;
        s->data = realloc(s->data, s->size * sizeof(void *));
        if (s->data == NULL) {
            fprintf(stderr, "Failed to reallocate memory for stack.\n");
            exit(1);
        }
    }
    return s->data[--s->tail];
}

int stack_empty(stack *s) {
    return (s->tail == 0);
}

stack *stack_delete(stack *s) {
    free(s->data);
    free(s);

    return NULL;
}
