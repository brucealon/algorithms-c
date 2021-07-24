
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

struct testcase {
    char *evaluation;
    int   result;
};
typedef struct testcase testcase;

bool is_number(char value) {
    if (value >= 48 && value <= 57)
        return true;
    return false;
}

bool is_operand(char value) {
    if (value == '+' || value == '*')
        return true;
    return false;
}

int evaluate(char *evaluation) {
    char opstack[strlen(evaluation)];
    int opptr = 0;
    int numstack[strlen(evaluation)];
    int numptr = 0;
    
    for (int idx = 0; evaluation[idx] != 0; ++idx) {
        if (is_number(evaluation[idx]))
        {
            numstack[numptr++] = evaluation[idx] - 48;
        }
        else if (is_operand(evaluation[idx]))
        {
            opstack[opptr++] = evaluation[idx];
        }
        else if (evaluation[idx] == ')')
        {
            int num1 = numstack[--numptr];
            int num2 = numstack[--numptr];
            char op = opstack[--opptr];
            if (op == '+')
            {
                numstack[numptr++] = num1 + num2;
            }
            else if (op == '*')
            {
                numstack[numptr++] = num1 * num2;
            }
        }
    }

    return numstack[0];
}

void run_tests(testcase tests[], int numtests) {
    testcase test;
    for (int idx = 0; idx < numtests; ++idx) {
        test = tests[idx];
        int result = evaluate(test.evaluation);
        if (result == test.result) {
            printf("SUCCESS: %s = %d\n", test.evaluation, test.result);
        } else {
            printf("FAILURE: %s: %d != %d\n", test.evaluation, result, test.result);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        char *evalstring = argv[1];
        printf("Evaluating: %s\n", evalstring);
    } else {
        testcase tests[] = {
                           {"(1 + ((2 + 3) * (4 * 5)))", 101},
                           {"((5 * (4 + (3 * 2))) * 1)", 50},
                           {"((5 * (4 + (3 * 2))) * 0)", 0},
                           {"(((2 + 1) + (2 + 3)) * 6)", 48},
        };
        run_tests(tests, sizeof(tests) / sizeof(testcase));
    }
}
