
#ifndef BASIC_SORTING_FUNCTIONS_H
#define BASIC_SORTING_FUNCTIONS_H

int median_of_3(char *a, int i, int j, int k);
int index_of(int a[], int length, int key);
int is_sorted(int *integers, int length);

int insertion_sort_integers(int *integers, int length);
int selection_sort_integers(int *integers, int length);
int shell_sort_integers(int *integers, int length);
int merge_sort_integers(int *integers, int length);
int quick_sort_integers(int *integers, int length);
int heap_sort_integers(int *integers, int length);

#endif
