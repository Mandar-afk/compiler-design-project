#include "compiler.h"

static int isNumber(const char *s) {
    if (!s || *s == '\0') return 0;
    for (const char *p = s; *p; p++) {
        if (*p < '0' || *p > '9') return 0;
    }
    return 1;
}

static int calculate(int a, const char *op, int b, int *ok) {
    *ok = 1;
    if (strcmp(op, "+") == 0) return a + b;
    if (strcmp(op, "-") == 0) return a - b;
    if (strcmp(op, "*") == 0) return a * b;
    if (strcmp(op, "/") == 0) {
        if (b == 0) {
            *ok = 0;
            return 0;
        }
        return a / b;
    }
    *ok = 0;
    return 0;
}

void optimizeTAC(void) {
    printf("\nOPTIMIZED TAC\n");
    printf("------------------------\n");

    for (int i = 0; i < getTacCount(); i++) {
        const char *line = getTacLine(i);
        char result[32], left[32], op[8], right[32];

        if (sscanf(line, "%31s = %31s %7s %31s", result, left, op, right) == 4) {
            /* Constant folding */
            if (isNumber(left) && isNumber(right)) {
                int a = atoi(left), b = atoi(right), ok;
                int value = calculate(a, op, b, &ok);
                if (ok) {
                    char optimized[MAX_TAC_LINE];
                    snprintf(optimized, sizeof(optimized), "%s = %d", result, value);
                    setTacLine(i, optimized);
                }
            }

            /* Algebraic simplification */
            if (strcmp(op, "+") == 0 && strcmp(right, "0") == 0) {
                char optimized[MAX_TAC_LINE];
                snprintf(optimized, sizeof(optimized), "%s = %s", result, left);
                setTacLine(i, optimized);
            } else if (strcmp(op, "+") == 0 && strcmp(left, "0") == 0) {
                char optimized[MAX_TAC_LINE];
                snprintf(optimized, sizeof(optimized), "%s = %s", result, right);
                setTacLine(i, optimized);
            } else if (strcmp(op, "-") == 0 && strcmp(right, "0") == 0) {
                char optimized[MAX_TAC_LINE];
                snprintf(optimized, sizeof(optimized), "%s = %s", result, left);
                setTacLine(i, optimized);
            } else if (strcmp(op, "*") == 0 && strcmp(right, "1") == 0) {
                char optimized[MAX_TAC_LINE];
                snprintf(optimized, sizeof(optimized), "%s = %s", result, left);
                setTacLine(i, optimized);
            } else if (strcmp(op, "*") == 0 && strcmp(left, "1") == 0) {
                char optimized[MAX_TAC_LINE];
                snprintf(optimized, sizeof(optimized), "%s = %s", result, right);
                setTacLine(i, optimized);
            }
        }

        printf("%s\n", getTacLine(i));
    }
}
