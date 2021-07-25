
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int median_of_3(char *a, int i, int j, int k) {
    return a[i] < a[j] ?
        (a[j] < a[k] ? j : (a[i] < a[k] ? k : i)) :
        (a[k] < a[j] ? j : (a[k] < a[i] ? k : i));
}

int index_of(int a[], int length, int key) {
    int lo = 0;
    int hi = length - 1;
    int mid = 0;

    while (lo <= hi) {
        mid = lo + ((hi - lo) / 2);
        if (key < a[mid])
            hi = mid - 1;
        else if (key > a[mid])
            lo = mid + 1;
        else
            return mid;
    }

    return -1;
}

int is_sorted(int *integers, int length) {
    for (int i = 1; i < length; i++) {
        if (integers[i - 1] > integers[i])
            return 0;
    }

    return 1;
}

int insertion_sort_integers(int *integers, int length) {
    int n = length;
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && integers[j] < integers[j - 1]; j--) {
            int t = integers[j];
            integers[j] = integers[j - 1];
            integers[j - 1] = t;
        }
    }

    return 0;
}

int selection_sort_integers(int *integers, int length) {
    for (int i = 0; i < length; i++) {
        int min = i;
        for (int j = i + 1; j < length; j++) {
            if (integers[j] < integers[min])
                min = j;
        }
        int t = integers[i];
        integers[i] = integers[min];
        integers[min] = t;
    }

    return 0;
}

int shell_sort_integers(int *integers, int length) {
    int n = length;
    int h = 1;
    while (h < n/3)
        h = 3*h + 1;
    while (h >= 1) {
        for (int i = h; i < n; i++) {
            for (int j = i; j >= h && integers[j] < integers[j - h]; j -= h) {
                int t = integers[j];
                integers[j] = integers[j - h];
                integers[j - h] = t;
            }
        }
        h = h/3;
    }

    return 0;
}

int merge(int *integers, int *buffer, int low, int middle, int high) {
    int l = low;
    int h = middle + 1;

    for (int k = low; k <= high; k++)
        buffer[k] = integers[k];

    for (int k = low; k <= high; k++) {
        if      (l > middle)            integers[k] = buffer[h++];
        else if (h > high)              integers[k] = buffer[l++];
        else if (buffer[h] < buffer[l]) integers[k] = buffer[h++];
        else                            integers[k] = buffer[l++];
    }

    return 0;
}

int merge_sort_internal(int *integers, int *buffer, int low, int high) {
    if (low < high) {
        int middle = (low + high) / 2;
        merge_sort_internal(integers, buffer, low, middle);
        merge_sort_internal(integers, buffer, middle + 1, high);
        merge(integers, buffer, low, middle, high);
    }

    return 0;
}

int merge_sort_integers(int *integers, int length) {
    int *buffer = (int *)malloc(sizeof(int) * length);
    if (buffer == NULL) {
        fprintf(stderr, "Failed to allocate memory: %s\n", strerror(errno));
        exit(1);
    }
    int result = merge_sort_internal(integers, buffer, 0, length - 1);
    free(buffer);

    return result;
}

int quick_sort_partition(int *integers, int low, int high) {
    int pivot = integers[high];
    int idx = low;
    for (int jdx = low; jdx <= high; jdx++) {
        if (integers[jdx] < pivot) {
            int temp = integers[idx];
            integers[idx] = integers[jdx];
            integers[jdx] = temp;
            idx++;
        }
    }
    int temp = integers[idx];
    integers[idx] = integers[high];
    integers[high] = temp;

    return idx;
}

void quick_sort_internal(int *integers, int low, int high) {
    if (low < high) {
        int p = quick_sort_partition(integers, low, high);
        quick_sort_internal(integers, low, p - 1);
        quick_sort_internal(integers, p + 1, high);
    }
}

int quick_sort_integers(int *integers, int length) {
    quick_sort_internal(integers, 0, length - 1);

    return 0;
}

void heap_exchange(int *integers, int idx, int jdx) {
    int key = integers[idx];
    integers[idx] = integers[jdx];
    integers[jdx] = key;
}

void heap_sink(int *integers, int idx, int last) {
    while ((idx * 2) < last) {
        int child = idx * 2;
        if (child < (last - 1) && integers[child] < integers[child + 1]) child++;
        if (integers[idx] >= integers[child]) break;
        heap_exchange(integers, idx, child);
        idx = child;
    }
}

int heap_sort_integers(int *integers, int length) {
    for (int idx = length / 2; idx >= 0; idx--) {
        heap_sink(integers, idx, length - 1);
    }
    int idx = length - 1;
    while (idx > 0) {
        heap_exchange(integers, 0, idx--);
        heap_sink(integers, 0, idx);
    }
}
