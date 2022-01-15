
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"

/*
   void     put(key, value)
   value    get(key)
   void     delete(key)
   bool     contains(key)
   bool     is_empty()
   int      size()
   iterator keys()
*/

struct node {
    struct node *next;
    char        *key;
    int          value;
};

struct search_list {
    struct node *head;
};

struct search_list_iterator {
    char **list;
    char **curr;
};

struct node *node_new(char *key, int keylen, int value) {
    struct node *n = malloc(sizeof(struct node));
    if (n == NULL) {
        fprintf(stderr, "Failed to allocate memory for node! Exiting.\n");
        exit(1);
    }

    n->next = NULL;
    n->key = (char *)malloc(sizeof(char *) * keylen);
    strncpy(n->key, key, keylen);
    n->value = value;

    return n;
}

void node_free(struct node *n) {
    if (n != NULL) {
        if (n->key != NULL) {
            free(n->key);
        }
        free(n);
    }
}

struct search_list *list_new() {
    struct search_list *l = malloc(sizeof(struct search_list));
    if (l == NULL) {
        fprintf(stderr, "Failed to allocate memory for list! Exiting.\n");
        exit(1);
    }

    l->head = NULL;

    return l;
}

void list_free(struct search_list *l) {
    struct node *curr = l->head;
    while (curr != NULL) {
        l->head = l->head->next;
        node_free(curr);
        curr = l->head;
    }

    if (l != NULL) {
        free(l);
    }
}

void list_put(struct search_list *l, char *key, int keylen, int value) {
    struct node *n = l->head;
    while (n != NULL) {
        if (strcmp(n->key, key) == 0) {
            n->value = value;
            return;
        }
        n = n->next;
    }

    n = node_new(key, keylen, value);
    n->next = l->head;
    l->head = n;
}

int list_get(struct search_list *l, char *key) {
    struct node *n = l->head;
    while (n != NULL) {
        if (strcmp(n->key, key) == 0) {
            return n->value;
        }
        n = n->next;
    }

    return -1;
}

void list_delete(struct search_list *l, char *key) {
    struct node *n = l->head;
    if (strcmp(n->key, key) == 0) {
        l->head = l->head->next;
        node_free(n);
        return;
    }

    while (n->next != NULL) {
        if (strcmp(n->next->key, key) == 0) {
            struct node *t = n->next;
            n->next = n->next->next;
            node_free(t);
        }
    }
}

int list_contains(struct search_list *l, char *key) {
    struct node *n = l->head;
    while (n != NULL) {
        if (strcmp(n->key, key) == 0) {
            return 1;
        }
        n = n->next;
    }
    return 0;
}

int list_isempty(struct search_list *l) {
    return l->head == NULL;
}

int list_size(struct search_list *l) {
    int size = 0;
    struct node *n = l->head;
    while (n != NULL) {
        ++size;
        n = n->next;
    }

    return size;
}

void iterator_free(struct search_list_iterator *i) {
    if (i != NULL) {
        if (i->list != NULL) {
            char **ptr = i->list;
            while (*ptr != NULL) {
                free(*ptr);
                ptr++;
            }
        }
        free(i->list);
        free(i);
    }
}

struct search_list_iterator *list_keys(struct search_list *l) {
    struct search_list_iterator *i;

    i = (struct search_list_iterator *)malloc(sizeof(struct search_list_iterator));
    int size = list_size(l);
    i->list = (char **)calloc(sizeof(char *), size + 1);
    if (i->list == NULL) {
        fprintf(stderr, "Error allocating iterator: %s\n", strerror(errno));
        return NULL;
    }
    i->curr = i->list;

    struct node *n = l->head;
    char **ptr = i->list;
    while (n != NULL) {
        char *element = (char *)malloc(sizeof(char *) * strlen(n->key));
        if (element == NULL) {
            fprintf(stderr, "Error allocating key: %s\n", strerror(errno));
            iterator_free(i);
            return NULL;
        }
        strcpy(element, n->key);
        *ptr = element;
        ptr++;
        n = n->next;
    }
    *ptr = NULL;

    return i;
}

char *iterator_next(struct search_list_iterator *i) {
    if (i == NULL) {
        return NULL;
    }
    char *key = *(i->curr);
    i->curr++;
    return key;
}

int iterator_done(struct search_list_iterator *i) {
    if (i == NULL) {
        return 1;
    }
    char **ptr = i->curr;
    if (*ptr == NULL) {
        return 1;
    }

    return 0;
}

int word_adder(char *word, int wordlen, void *extra) {
    struct search_list *list = (struct search_list *)extra;

    struct node *n = list->head;
    while (n != NULL) {
        n = n->next;
    }
    if (list_contains(list, word)) {
        int count = list_get(list, word);
        list_put(list, word, wordlen, count + 1);
    } else {
        list_put(list, word, wordlen, 1);
    }

    return 0;
}
int main(int argc, char *argv[]) {
    struct search_list *list = list_new();
    char filename[256];

    if (argc == 2) {
      safe_filename(filename, argv[1], 255);
    } else {
      printf("Usage: %s <filename>\n", argv[0]);
      exit(EXIT_FAILURE);
    }

    read_words(filename, word_adder, list);

    struct search_list_iterator *iterator = list_keys(list);
    char most_common[256];
    int max_freq = 0;
    while (!iterator_done(iterator)) {
        char *key = iterator_next(iterator);
        int freq = list_get(list, key);
        if (freq > max_freq) {
            max_freq = freq;
            strncpy(most_common, key, 256);
        }
        printf("Key: %s = %d\n", key, freq);
    }
    iterator_free(iterator);

    printf("There were %d distinct words in the story.\n", list_size(list));
    printf("The most common word was '%s', with %d uses.\n", most_common, max_freq);
    list_free(list);
}
