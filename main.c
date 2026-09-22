#include "compiler.h"

int yyparse(void);

int main(void) {
    /* Change only this string when testing another source program. */
    const char *sourceCode =
        "int a;"
        "int b;"
        "int result;"
        "a = 10;"
        "b = -5;"
        "result = +(a + b * 2) - -3;";

    printf("========================================\n");
    printf("       MINI COMPILER - C + BISON       \n");
    printf("========================================\n");
    printf("\nSOURCE PROGRAM\n");
    printf("------------------------\n%s\n", sourceCode);

    resetSymbolTable();
    resetTAC();
    setSource(sourceCode);

    printf("\nPARSING...\n");
    int parseResult = yyparse();

    if (parseResult != 0) {
        fprintf(stderr, "\nCompilation stopped: syntax error.\n");
        return 1;
    }

    if (hasSemanticError()) {
        fprintf(stderr, "\nCompilation stopped: semantic/lexical errors were detected.\n");
        return 1;
    }

    printf("\nParsing and semantic analysis successful.\n");
    printSymbolTable();
    printTAC();
    optimizeTAC();
    generateTargetCode();

    printf("\nCompilation completed successfully.\n");
    return 0;
}
