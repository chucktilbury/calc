
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

static bool is_right_assoc(TokenType type) {

    if(type == TOK_UMINUS || type == TOK_UPLUS || type == TOK_EQU)
        return true;

    return false;
}

/*
 * SYM = expression -- save the expression result in the SYM
 * SYM < expression -- save the expression in the SYM
 * expression -- print the result of the expression
 * SYM -- print the value of the SYM (expr or value)
 */
bool consumeExpr() {
is_right_assoc(0);
precedence(0);
    return false;
}