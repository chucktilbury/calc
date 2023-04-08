
#include <stdbool.h>

#include "scan.h"
#include "errors.h"

static int precedence(TokenType type) {

    switch(type) {
        case TOK_ADD:
        case TOK_SUB:
            return 2;
        case TOK_MUL:
        case TOK_DIV:
        case TOK_MOD:
            return 3;
        case TOK_POW:
            return 4;
        case TOK_EQU:
        case TOK_EXPR:
            return 0;
        case TOK_UMINUS:
        case TOK_UPLUS:
            return 5;
        case TOK_OPAREN:
        case TOK_CPAREN:
            return 1;
        default:
            fatalError("the symbol %s is not a valid operator", tokTypeToStr(type));
            return -1;
    }
    fatalError("invalid operator while finding precedence %c (0x%02X)", type, type);
}

static bool is_unary(TokenType type) {

    if(type == TOK_UMINUS || type == TOK_UPLUS)
        return true;

    return false;
}

bool consumeExpr() {

    while(crntToken()->type != TOK_EOL) {
        printToken(crntToken());
        consumeToken();
    }

    return true; // return after evaluating the line
}