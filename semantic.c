#include "compiler.h"

char symbolTable[MAX_SYMBOLS][MAX_LEXEME];
int symbolCount = 0;

void resetSymbolTable() {
    symbolCount = 0;
}

int isDeclared(const char *name) {

    for (int i = 0; i < symbolCount; i++) {

        if (strcmp(symbolTable[i], name) == 0) {
            return 1;
        }
    }

    return 0;
}

int declareVariable(const char *name) {

    if (isDeclared(name)) {

        printf("\nSemantic Error: Variable '%s' already declared\n", name);
        return 0;
    }

    strcpy(symbolTable[symbolCount], name);
    symbolCount++;

    return 1;
}

void printSymbolTable() {

    printf("\n===== SYMBOL TABLE =====\n");

    printf("Variable\tType\n");
    printf("----------------------\n");

    for (int i = 0; i < symbolCount; i++) {
        printf("%s\t\tint\n", symbolTable[i]);
    }
}