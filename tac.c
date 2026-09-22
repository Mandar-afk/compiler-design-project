#include "compiler.h"

static char tac[MAX_TAC][MAX_TAC_LINE];
static int tacCount = 0;
static int tempCount = 0;

void resetTAC(void) {
    tacCount = 0;
    tempCount = 0;
}

char *generateTAC(const char *left, const char *op, const char *right) {
    if (tacCount >= MAX_TAC) {
        fprintf(stderr, "TAC Error: maximum TAC instruction count exceeded.\n");
        setSemanticError();
        return NULL;
    }

    tempCount++;
    char *result = malloc(32);
    if (!result) {
        fprintf(stderr, "TAC Error: memory allocation failed.\n");
        setSemanticError();
        return NULL;
    }
    snprintf(result, 32, "t%d", tempCount);
    snprintf(tac[tacCount], MAX_TAC_LINE, "%s = %s %s %s",
             result, left, op, right);
    tacCount++;
    return result;
}

void generateAssignment(const char *name, const char *value) {
    if (tacCount >= MAX_TAC) {
        fprintf(stderr, "TAC Error: maximum TAC instruction count exceeded.\n");
        setSemanticError();
        return;
    }
    snprintf(tac[tacCount], MAX_TAC_LINE, "%s = %s", name, value);
    tacCount++;
}

void printTAC(void) {
    printf("\nTHREE ADDRESS CODE (TAC)\n");
    printf("------------------------\n");
    if (tacCount == 0) {
        printf("(empty)\n");
        return;
    }
    for (int i = 0; i < tacCount; i++) {
        printf("%s\n", tac[i]);
    }
}

int getTacCount(void) {
    return tacCount;
}

const char *getTacLine(int index) {
    if (index < 0 || index >= tacCount) return NULL;
    return tac[index];
}

void setTacLine(int index, const char *line) {
    if (index < 0 || index >= tacCount) return;
    strncpy(tac[index], line, MAX_TAC_LINE - 1);
    tac[index][MAX_TAC_LINE - 1] = '\0';
}
