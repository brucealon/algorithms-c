
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "output.h"
#include "sorting_basic.h"

int test_median_of_3() {
    int failures = 0;
    struct test {
        char array[3];
        int result;
        int index;
    };
    struct test tests[] = {
                           { {1, 2, 3}, 2, 1 },
                           { {3, 2, 1}, 2, 1 },
                           { {3, 1, 2}, 2, 2 },
                           { {2, 1, 3}, 2, 0 },
                           { {1, 3, 2}, 2, 2 },
                           { {2, 3, 1}, 2, 0 },
                           { {3, 3, 2}, 3, 1 },
                           { {2, 3, 3}, 3, 2 },
                           { {3, 3, 3}, 3, 0 },
    };
    int length = sizeof(tests) / sizeof(struct test);
    printf("\nHave %d tests for median_of_3.\n", length);
    for (int idx = 0; idx < length; idx++) {
        struct test test = tests[idx];
        int r = median_of_3(test.array, 0, 1, 2);
        if (r == test.index && test.array[r] == test.result) {
            printf("Success: %d at %d.\n", test.array[r], r);
        } else {
            printf("Failure: median of %d, %d, %d should be %d at %d, got %d at %d.\n",
                   test.array[0], test.array[1], test.array[2], test.result, test.index, test.array[r], r);
            ++failures;
        }
    }

    return failures;
}

int test_index_of() {
    int failures = 0;
    int array[20] = {1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21};
    struct test {
        int key;
        int result;
    };
    struct test tests[] = {
                           { 10,  8 },
                           { 15, 13 },
                           {  3,  2 },
                           { 25, -1 },
                           {  9, -1 },
                           { -5, -1 },
    };
    int length = sizeof(tests) / sizeof(struct test);
    printf("\nHave %d tests for index_of.\n", length);
    for (int idx = 0; idx < length; idx++) {
        struct test test = tests[idx];
        int r = index_of(array, sizeof(array) / sizeof(int), test.key);
        if (r == test.result) {
            if (test.result == -1) {
                printf("Success: %d is not in the array.\n", test.key);
            } else {
                printf("Success: found %d at %d.\n", test.key, r);
            }
        } else {
            printf("Failure: searching for %d, %d should have been %d.\n", test.key, r, test.result);
            ++failures;
        }
    }

    return failures;
}

int test_sort(int (*sorter)(int *, int), char *name) {
    char *ints_file = "data/smallW.txt";
    int *integers = NULL;
    int length = 0;
    char pretty_length[32];
    int failure = 0;

    read_all_ints(ints_file, &integers, &length);
    sorter(integers, length);
    pint(length, pretty_length);

    if (is_sorted(integers, length)) {
        printf("Success: %s ably sorted %s integers.\n", name, pretty_length);
    } else {
        printf("Failure: %s is unable to sort %s integers.\n", name, pretty_length);
        failure = 1;
    }
    free(integers);
    return failure;
}

int run_tests() {
    int failures = 0;
    int tests = 0;

    failures += test_median_of_3(); tests++;
    failures += test_index_of(); tests++;
    printf("\n");
    failures += test_sort(selection_sort_integers, "selection_sort"); tests++;
    failures += test_sort(insertion_sort_integers, "insertion_sort"); tests++;
    failures += test_sort(shell_sort_integers, "shell_sort"); tests++;
    failures += test_sort(merge_sort_integers, "merge_sort"); tests++;
    failures += test_sort(quick_sort_integers, "quick_sort"); tests++;
    failures += test_sort(heap_sort_integers, "heap_sort"); tests++;
    printf("\n");

    printf("\nGot %d total failures from %d tests.\n", failures, tests);

    if (failures > 0)
        exit(failures);
    else
        return 0;
}

int main(int argc, char *argv[]) {
    run_tests();
    return EXIT_SUCCESS;
}
