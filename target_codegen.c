#include "compiler.h"

void generateTargetCode(void) {
    printf("\nTARGET CODE\n");
    printf("------------------------\n");

    for (int i = 0; i < getTacCount(); i++) {
        const char *line = getTacLine(i);
        char result[32], left[32], op[8], right[32];

        if (sscanf(line, "%31s = %31s %7s %31s", result, left, op, right) == 4) {
            printf("LOAD R0, %s\n", left);
            if (strcmp(op, "+") == 0) printf("ADD R0, %s\n", right);
            else if (strcmp(op, "-") == 0) printf("SUB R0, %s\n", right);
            else if (strcmp(op, "*") == 0) printf("MUL R0, %s\n", right);
            else if (strcmp(op, "/") == 0) printf("DIV R0, %s\n", right);
            printf("STORE %s, R0\n", result);
        } else if (sscanf(line, "%31s = %31s", result, left) == 2) {
            printf("MOV %s, %s\n", result, left);
        }
    }
}
