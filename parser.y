%{
#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"

int yylex(void);
void yyerror(const char *s);
%}

%union {
    int num;
    char *str;
}

%token INT
%token <str> ID
%token <num> NUMBER
%token ASSIGN PLUS MINUS TIMES DIVIDE LPAREN RPAREN SEMICOLON INVALID

%type <str> expression term unary factor

%start program

%%

program
    : statement_list
    ;

statement_list
    : statement_list statement
    | /* empty */
    ;

statement
    : declaration
    | assignment
    ;

declaration
    : INT ID SEMICOLON
      {
          if (declareVariable($2))
              printf("Declaration: int %s\n", $2);
          free($2);
      }
    ;

assignment
    : ID ASSIGN expression SEMICOLON
      {
          if (!isDeclared($1)) {
              fprintf(stderr, "Semantic Error: variable '%s' used before declaration.\n", $1);
              setSemanticError();
          } else if ($3 != NULL) {
              generateAssignment($1, $3);
          }
          free($1);
          free($3);
      }
    ;

expression
    : expression PLUS term
      {
          $$ = generateTAC($1, "+", $3);
          free($1);
          free($3);
      }
    | expression MINUS term
      {
          $$ = generateTAC($1, "-", $3);
          free($1);
          free($3);
      }
    | term
      {
          $$ = $1;
      }
    ;

term
    : term TIMES unary
      {
          $$ = generateTAC($1, "*", $3);
          free($1);
          free($3);
      }
    | term DIVIDE unary
      {
          $$ = generateTAC($1, "/", $3);
          free($1);
          free($3);
      }
    | unary
      {
          $$ = $1;
      }
    ;

/* Unary + and - have higher precedence than * and /. */
unary
    : PLUS unary
      {
          /* Unary plus does not change the value. */
          $$ = $2;
      }
    | MINUS unary
      {
          /* Unary minus is represented as 0 - operand. */
          $$ = generateTAC("0", "-", $2);
          free($2);
      }
    | factor
      {
          $$ = $1;
      }
    ;

factor
    : ID
      {
          if (!isDeclared($1)) {
              fprintf(stderr, "Semantic Error: variable '%s' used before declaration.\n", $1);
              setSemanticError();
          }
          $$ = $1;
      }
    | NUMBER
      {
          $$ = malloc(32);
          if (!$$) {
              fprintf(stderr, "Fatal Error: memory allocation failed.\n");
              exit(EXIT_FAILURE);
          }
          snprintf($$, 32, "%d", $1);
      }
    | LPAREN expression RPAREN
      {
          $$ = $2;
      }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
}
