#include "compiler.h"

static char symbolTable[MAX_SYMBOLS][MAX_IDENTIFIER_LENGTH + 1];
static int symbolCount = 0;
static int semanticError = 0;

void resetSymbolTable(void) {
    symbolCount = 0;
    semanticError = 0;
}

int isDeclared(const char *name) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i], name) == 0) return 1;
    }
    return 0;
}

int declareVariable(const char *name) {
    if (isDeclared(name)) {
        fprintf(stderr, "Semantic Error: variable '%s' is already declared.\n", name);
        semanticError = 1;
        return 0;
    }

    if (symbolCount >= MAX_SYMBOLS) {
        fprintf(stderr, "Semantic Error: symbol table limit reached.\n");
        semanticError = 1;
        return 0;
    }

    strncpy(symbolTable[symbolCount], name, MAX_IDENTIFIER_LENGTH);
    symbolTable[symbolCount][MAX_IDENTIFIER_LENGTH] = '\0';
    symbolCount++;
    return 1;
}

void setSemanticError(void) {
    semanticError = 1;
}

int hasSemanticError(void) {
    return semanticError;
}

void printSymbolTable(void) {
    printf("\nSYMBOL TABLE\n");
    printf("------------------------\n");
    if (symbolCount == 0) {
        printf("(empty)\n");
        return;
    }
    for (int i = 0; i < symbolCount; i++) {
        printf("%d. %s : int\n", i + 1, symbolTable[i]);
    }
}
