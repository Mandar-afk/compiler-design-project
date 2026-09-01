#include "compiler.h"

int main() {

    const char *sourceCode =

        "int a; int b; int c; a = 10; b = 5; c = (a + b) * 2;";


    /* Stage 1 */

    lexicalAnalysis(sourceCode);

    printTokens();


    /* Stage 2 + 3 + 4 */

    parseProgram();

    printSymbolTable();

    printTAC();


    /* Stage 5 */

    optimizeTAC();


    /* Stage 6 */

    generateTargetCode();


    return 0;
}