#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IDENTIFIER_LENGTH 20
#define MAX_SYMBOLS 100
#define MAX_TAC 200
#define MAX_TAC_LINE 120
#define MAX_SOURCE_LENGTH 5000

/* Semantic analysis */
void resetSymbolTable(void);
int declareVariable(const char *name);
int isDeclared(const char *name);
void printSymbolTable(void);
int hasSemanticError(void);
void setSemanticError(void);

/* Three Address Code */
void resetTAC(void);
char *generateTAC(const char *left, const char *op, const char *right);
void generateAssignment(const char *name, const char *value);
void printTAC(void);
int getTacCount(void);
const char *getTacLine(int index);
void setTacLine(int index, const char *line);

/* Optimization and target code */
void optimizeTAC(void);
void generateTargetCode(void);

/* Lexer input */
void setSource(const char *source);

#endif
