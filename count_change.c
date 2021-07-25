
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct stack_node {
    struct stack_node *next;
    int amount;
    int coins;
};
typedef struct stack_node stack_node;

struct stack {
    stack_node *head;
    stack_node *recycle;
    short allow_recycle;
};
typedef struct stack stack;

stack_node *stack_node_new(int amount, int coins) {
    stack_node *n = (stack_node *)malloc(sizeof(stack_node));
    if (n == NULL) {
        fprintf(stderr, "Failed to allocate memory for stack_node!\n");
        exit(1);  /* DEBUG add error message */
    }
    n->next = NULL;
    n->amount = amount;
    n->coins = coins;

    return n;
}

void stack_node_delete(stack_node *n) {
    free(n);
}

stack *stack_new(short allow_recycle) {
    stack *s = (stack *)malloc(sizeof(stack));
    if (s == NULL) {
        fprintf(stderr, "Failed to allocate memory for stack!\n");
        exit(1);  /* DEBUG add error message */
    }
    s = (stack *)s;
    s->head = NULL;
    s->recycle = NULL;
    s->allow_recycle = allow_recycle;

    return s;
}

void stack_delete_nodes(stack_node *n) {
    stack_node *next;
    while (n != NULL) {
        next = n->next;
        stack_node_delete(n);
        n = next;
    }
}

void stack_delete(stack *s) {
    stack_node *curr = s->head;
    stack_node *next;

    stack_delete_nodes(s->head);
    stack_delete_nodes(s->recycle);
    free(s);
}

int stack_len(stack *s) {
    stack_node *p = s->head;
    int count = 0;

    while (p != NULL) {
        count++;
        p = p->next;
    }

    return count;
}

void stack_push(stack *s, int amount, int coins) {
    if (s->allow_recycle && s->recycle != NULL) {
        stack_node *n = s->recycle;
        s->recycle = s->recycle->next;
        n->next = s->head;
        n->amount = amount;
        n->coins = coins;
        s->head = n;
    } else {
        stack_node *n = stack_node_new(amount, coins);
        n->next = s->head;
        s->head = n;
    }
}

int stack_pop(stack *s, int *amount, int *coins) {
    int error = 1;
    stack_node *p = NULL;

    p = s->head;
    if (p != NULL) {
        s->head = p->next;
        *amount = p->amount;
        *coins = p->coins;
        if (s->allow_recycle) {
            p->next = s->recycle;
            s->recycle = p;
        } else {
            stack_node_delete(p);
        }
        error = 0;
    }

    return error;
}

int stack_is_empty(stack *s) {
    return s->head == NULL ? 1 : 0;
}

void print_stack_nodes(stack_node *node) {
    stack_node *p = node;
    while (p != NULL) {
        printf("n%s", p->next == NULL ? "" : "->");
        p = p->next;
    }
    printf("\n");
}

void print_stack(stack *s) {
    stack_node *p = NULL;

    if (s == NULL) {
        printf("The stack is empty.\n");
    } else {
        print_stack_nodes(s->head);
    }
}

void count_change_stack(int coins[], int numcoins, int amount) {
    printf("MallocStack: Find how many ways we can make change for %d cents with %d different coins.\n", amount, numcoins);
    stack *workload = stack_new(1);
    int a, c;
    int error;
    int total = 0;

    stack_push(workload, amount, numcoins - 1);
    while (!stack_is_empty(workload)) {
        error = stack_pop(workload, &a, &c);
        if (error == 0) {
            if (a == 0) {
                total++;
            } else if (a > 0 && c >= 0) {
                stack_push(workload, a, c - 1);
                stack_push(workload, a - coins[c], c);
            }
        }
    }
    stack_delete(workload);

    printf("There are %d ways to make change.\n", total);
}

int cc_inner(int coins[], int coinsidx, int amount) {
    if (amount == 0) {
        return 1;
    } else if (coinsidx < 0 || amount < 0) {
        return 0;
    } else {
        return cc_inner(coins, coinsidx, amount - coins[coinsidx]) + cc_inner(coins, coinsidx - 1, amount);
    }
}

void count_change_recur(int coins[], int numcoins, int amount) {
    printf("Recursion: Find how many ways we can make change for %d cents with %d different coins.\n", amount, numcoins);
    int total = cc_inner(coins, numcoins - 1, amount);
    printf("There are %d ways to make change.\n", total);
}

void count_change_arrstack(int coins[], int numcoins, int amount) {
    printf("ArrayStack: Find how many ways we can make change for %d cents with %d different coins.\n", amount, numcoins);
    int total = 0;
    int stackptr = 0;
    int c, a;
    int *arrstack = NULL;
    arrstack = (int*)alloca(sizeof(int) * ((amount * 2) + 2));
    if (arrstack == NULL) {
        fprintf(stderr, "Failed to allocate memory for array stack!\n");
        exit(1);  /* DEBUG add error message */
    }
    arrstack[stackptr++] = numcoins - 1;
    arrstack[stackptr++] = amount;
    while (stackptr > 0) {
        a = arrstack[--stackptr];
        c = arrstack[--stackptr];
        if (a == 0) {
            total++;
        } else if (a > 0 && c >= 0) {
            arrstack[stackptr++] = c - 1;
            arrstack[stackptr++] = a;
            arrstack[stackptr++] = c;
            arrstack[stackptr++] = a - coins[c];
        }
    }

    printf("There are %d ways to make change.\n", total);
}

void run_function(void (*worker)(int[], int, int), int coins[], int numcoins, int amount) {
    clock_t start, end;
    start = clock();
    worker(coins, numcoins, amount);
    end = clock();
    printf("Function took %f seconds.\n", ((double)end - start) / CLOCKS_PER_SEC);
}

int main(int argc, char **argv) {
    int change = 0;
    int function = 0;
    int coin_types[] = {1, 5, 10, 25, 50};

    /* ./count_change <stack|recursion|array> <cents> */
    if (argc == 3) {
        if (strncmp("stack", argv[1], 5) == 0) {
            function = 0;
        } else if (strncmp("recursion", argv[1], 9) == 0) {
            function = 1;
        } else if (strncmp("array", argv[1], 5) == 0) {
            function = 2;
        }
        change = atoi(argv[2]);
    }
    /* ./count_change <cents> */
    if (argc == 2) {
        change = atoi(argv[1]);
    }
    if (change < 1) {
        change = 100;
    }

    switch (function) {
    case 0:
        run_function(count_change_stack, coin_types, 5, change);
        break;
    case 1:
        run_function(count_change_recur, coin_types, 5, change);
        break;
    case 2:
        run_function(count_change_arrstack, coin_types, 5, change);
        break;
    default:
        printf("Do not know how to do %d\n", argv[1]);
    }
}
