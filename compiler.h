#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 500
#define MAX_LEXEME 50
#define MAX_SYMBOLS 100
#define MAX_TAC 200

typedef enum {
    TOKEN_INT,
    TOKEN_ID,
    TOKEN_NUMBER,
    TOKEN_ASSIGN,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_SEMICOLON,
    TOKEN_EOF,
    TOKEN_INVALID
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[MAX_LEXEME];
} Token;

/* Lexer */
extern Token tokens[MAX_TOKENS];
extern int tokenCount;

void lexicalAnalysis(const char *source);
void printTokens();

/* Parser */
void parseProgram();

/* Semantic Analyzer */
void resetSymbolTable();
int declareVariable(const char *name);
int isDeclared(const char *name);
void printSymbolTable();

/* TAC */
void resetTAC();
void generateTAC(const char *result, const char *left, char op, const char *right);
void generateAssignment(const char *result, const char *value);
void printTAC();

/* Optimizer */
void optimizeTAC();

/* Target Code */
void generateTargetCode();

#endif