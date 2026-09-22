#include "compiler.h"
#include "parser.tab.h"
#include <ctype.h>

static const char *source = NULL;
static size_t pos = 0;

void setSource(const char *src) {
    source = src;
    pos = 0;
}

static void skipWhitespace(void) {
    while (source && isspace((unsigned char)source[pos])) {
        pos++;
    }
}

int yylex(void) {
    char buffer[256];
    size_t len = 0;

    if (!source) return 0;
    skipWhitespace();

    if (source[pos] == '\0') return 0;

    /* Identifier / keyword */
    if (isalpha((unsigned char)source[pos]) || source[pos] == '_') {
        while (isalnum((unsigned char)source[pos]) || source[pos] == '_') {
            if (len < sizeof(buffer) - 1) buffer[len++] = source[pos];
            pos++;
        }
        buffer[len] = '\0';

        if (strcmp(buffer, "int") == 0) return INT;

        if (len > MAX_IDENTIFIER_LENGTH) {
            fprintf(stderr,
                    "Lexical Error: identifier '%s' exceeds maximum length of %d characters.\n",
                    buffer, MAX_IDENTIFIER_LENGTH);
            return INVALID;
        }

        yylval.str = malloc(len + 1);
        if (!yylval.str) {
            fprintf(stderr, "Fatal Error: memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        memcpy(yylval.str, buffer, len + 1);
        return ID;
    }

    /* Integer constant */
    if (isdigit((unsigned char)source[pos])) {
        while (isdigit((unsigned char)source[pos])) {
            if (len < sizeof(buffer) - 1) buffer[len++] = source[pos];
            pos++;
        }
        buffer[len] = '\0';
        yylval.num = atoi(buffer);
        return NUMBER;
    }

    switch (source[pos]) {
        case '=': pos++; return ASSIGN;
        case '+': pos++; return PLUS;
        case '-': pos++; return MINUS;
        case '*': pos++; return TIMES;
        case '/': pos++; return DIVIDE;
        case '(': pos++; return LPAREN;
        case ')': pos++; return RPAREN;
        case ';': pos++; return SEMICOLON;
        default:
            fprintf(stderr, "Lexical Error: invalid character '%c'.\n", source[pos]);
            pos++;
            return INVALID;
    }
}
