#include "compiler.h"

char tac[MAX_TAC][100];
int tacCount = 0;

void resetTAC() {
    tacCount = 0;
}

void generateTAC(
    const char *result,
    const char *left,
    char op,
    const char *right
) {

    sprintf(
        tac[tacCount],
        "%s = %s %c %s",
        result,
        left,
        op,
        right
    );

    tacCount++;
}

void generateAssignment(
    const char *result,
    const char *value
) {

    sprintf(
        tac[tacCount],
        "%s = %s",
        result,
        value
    );

    tacCount++;
}

void printTAC() {

    printf("\n===== THREE ADDRESS CODE =====\n");

    for (int i = 0; i < tacCount; i++) {
        printf("%s\n", tac[i]);
    }
}