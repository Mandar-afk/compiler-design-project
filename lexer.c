#include "compiler.h"

Token tokens[MAX_TOKENS];
int tokenCount = 0;

void addToken(TokenType type, const char *lexeme) {
    tokens[tokenCount].type = type;
    strcpy(tokens[tokenCount].lexeme, lexeme);
    tokenCount++;
}

void lexicalAnalysis(const char *source) {

    tokenCount = 0;
    int i = 0;

    while (source[i] != '\0') {

        if (isspace(source[i])) {
            i++;
            continue;
        }

        if (isalpha(source[i]) || source[i] == '_') {

            char word[MAX_LEXEME];
            int j = 0;

            while (isalnum(source[i]) || source[i] == '_') {
                word[j++] = source[i++];
            }

            word[j] = '\0';

            if (strcmp(word, "int") == 0)
                addToken(TOKEN_INT, word);
            else
                addToken(TOKEN_ID, word);

            continue;
        }

        if (isdigit(source[i])) {

            char number[MAX_LEXEME];
            int j = 0;

            while (isdigit(source[i])) {
                number[j++] = source[i++];
            }

            number[j] = '\0';

            addToken(TOKEN_NUMBER, number);
            continue;
        }

        char temp[2] = {source[i], '\0'};

        switch (source[i]) {

            case '=':
                addToken(TOKEN_ASSIGN, temp);
                break;

            case '+':
                addToken(TOKEN_PLUS, temp);
                break;

            case '-':
                addToken(TOKEN_MINUS, temp);
                break;

            case '*':
                addToken(TOKEN_MUL, temp);
                break;

            case '/':
                addToken(TOKEN_DIV, temp);
                break;

            case '(':
                addToken(TOKEN_LPAREN, temp);
                break;

            case ')':
                addToken(TOKEN_RPAREN, temp);
                break;

            case ';':
                addToken(TOKEN_SEMICOLON, temp);
                break;

            default:
                addToken(TOKEN_INVALID, temp);
        }

        i++;
    }

    addToken(TOKEN_EOF, "EOF");
}

const char* tokenName(TokenType type) {

    switch (type) {

        case TOKEN_INT: return "INT";
        case TOKEN_ID: return "ID";
        case TOKEN_NUMBER: return "NUMBER";
        case TOKEN_ASSIGN: return "ASSIGN";
        case TOKEN_PLUS: return "PLUS";
        case TOKEN_MINUS: return "MINUS";
        case TOKEN_MUL: return "MUL";
        case TOKEN_DIV: return "DIV";
        case TOKEN_LPAREN: return "LPAREN";
        case TOKEN_RPAREN: return "RPAREN";
        case TOKEN_SEMICOLON: return "SEMICOLON";
        case TOKEN_EOF: return "EOF";
        default: return "INVALID";
    }
}

void printTokens() {

    printf("\n===== TOKENS =====\n");

    for (int i = 0; i < tokenCount; i++) {
        printf("%-12s : %s\n",
               tokenName(tokens[i].type),
               tokens[i].lexeme);
    }
}