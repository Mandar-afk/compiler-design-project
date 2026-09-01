#include "compiler.h"

extern char tac[MAX_TAC][100];
extern int tacCount;

int currentToken = 0;
int tempCount = 0;

void error(const char *message) {

    printf(
        "\nSyntax Error near '%s': %s\n",
        tokens[currentToken].lexeme,
        message
    );

    exit(1);
}

void match(TokenType expected) {

    if (tokens[currentToken].type == expected) {
        currentToken++;
    }

    else {
        error("Unexpected token");
    }
}

void newTemp(char *temp) {

    tempCount++;

    sprintf(temp, "t%d", tempCount);
}

/* Forward declarations */

void parseStatement();
void parseExpression(char *result);
void parseTerm(char *result);
void parseFactor(char *result);


/* Factor */

void parseFactor(char *result) {

    if (tokens[currentToken].type == TOKEN_NUMBER) {

        strcpy(result, tokens[currentToken].lexeme);

        currentToken++;
    }

    else if (tokens[currentToken].type == TOKEN_ID) {

        if (!isDeclared(tokens[currentToken].lexeme)) {

            printf(
                "\nSemantic Error: Variable '%s' not declared\n",
                tokens[currentToken].lexeme
            );

            exit(1);
        }

        strcpy(result, tokens[currentToken].lexeme);

        currentToken++;
    }

    else if (tokens[currentToken].type == TOKEN_LPAREN) {

        match(TOKEN_LPAREN);

        parseExpression(result);

        match(TOKEN_RPAREN);
    }

    else {
        error("Expected number, identifier or expression");
    }
}


/* Term handles * and / */

void parseTerm(char *result) {

    char left[50];
    char right[50];

    parseFactor(left);

    while (
        tokens[currentToken].type == TOKEN_MUL ||
        tokens[currentToken].type == TOKEN_DIV
    ) {

        char op;

        if (tokens[currentToken].type == TOKEN_MUL)
            op = '*';
        else
            op = '/';

        currentToken++;

        parseFactor(right);

        char temp[50];

        newTemp(temp);

        generateTAC(
            temp,
            left,
            op,
            right
        );

        strcpy(left, temp);
    }

    strcpy(result, left);
}


/* Expression handles + and - */

void parseExpression(char *result) {

    char left[50];
    char right[50];

    parseTerm(left);

    while (
        tokens[currentToken].type == TOKEN_PLUS ||
        tokens[currentToken].type == TOKEN_MINUS
    ) {

        char op;

        if (tokens[currentToken].type == TOKEN_PLUS)
            op = '+';
        else
            op = '-';

        currentToken++;

        parseTerm(right);

        char temp[50];

        newTemp(temp);

        generateTAC(
            temp,
            left,
            op,
            right
        );

        strcpy(left, temp);
    }

    strcpy(result, left);
}


/* Parse declaration */

void parseDeclaration() {

    match(TOKEN_INT);

    if (tokens[currentToken].type != TOKEN_ID) {
        error("Expected identifier");
    }

    char variable[50];

    strcpy(
        variable,
        tokens[currentToken].lexeme
    );

    currentToken++;

    match(TOKEN_SEMICOLON);

    declareVariable(variable);
}


/* Parse assignment */

void parseAssignment() {

    char variable[50];

    strcpy(
        variable,
        tokens[currentToken].lexeme
    );

    if (!isDeclared(variable)) {

        printf(
            "\nSemantic Error: Variable '%s' not declared\n",
            variable
        );

        exit(1);
    }

    match(TOKEN_ID);

    match(TOKEN_ASSIGN);

    char expressionResult[50];

    parseExpression(expressionResult);

    match(TOKEN_SEMICOLON);

    generateAssignment(
        variable,
        expressionResult
    );
}


/* Parse statement */

void parseStatement() {

    if (tokens[currentToken].type == TOKEN_INT) {

        parseDeclaration();
    }

    else if (tokens[currentToken].type == TOKEN_ID) {

        parseAssignment();
    }

    else {

        error("Expected declaration or assignment");
    }
}


/* Parse complete program */

void parseProgram() {

    currentToken = 0;
    tempCount = 0;

    resetSymbolTable();
    resetTAC();

    while (
        tokens[currentToken].type != TOKEN_EOF
    ) {

        parseStatement();
    }

    printf(
        "\nParsing completed successfully!\n"
    );
}