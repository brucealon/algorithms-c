
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"


int main(int argc, char *argv[]) {
    stack *s = stack_new();
    if (s == NULL) {
        fprintf(stderr, "Failed to allocate memory for stack.\n");
        exit(1);
    }

    for (unsigned long i = 1; i <= 25; i++) {
        printf("Push: %2ld\n", i);
        stack_push(s, (void *)i);
    }

    while (!stack_empty(s)) {
        unsigned long i = (unsigned long)stack_pop(s);
        printf("Pop:  %2ld\n", i);
    }

    s = stack_delete(s);
}

