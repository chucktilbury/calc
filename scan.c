#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "scan.h"
#include "memory.h"
#include "errors.h"
#include "fileio.h"

static char tok_buf[1024];
static int bidx = 0;
static Token* _crnt_;

// [a-zA-Z_][a-zA-Z_0-9]*
static Token* get_string() {

    Token* tok = createToken(TOK_SYM);

    int ch = getChar();
    while(true) {
        ch = consumeChar();
        if((isalpha(ch) || ch == '_' || isdigit(ch)))
            tok_buf[bidx++] = ch;
        else
            break;
    }

    tok->data.str = _dup_str(tok_buf);
    tok->str = _dup_str(tok_buf);
    return tok;
}

// [0-9]*((\.[0-9]+)+([eE][-+]*[0-9]+)*)
static Token* get_number() {

    Token* tok = createToken(TOK_NUM);

    int ch = getChar();
    while(true) {
        ch = consumeChar();
        if(isdigit(ch))
            tok_buf[bidx++] = ch;
        else
            break;
    }

    tok->data.num = strtod(tok_buf, NULL);
    tok->str = _dup_str(tok_buf);
    return tok;
}

// [+-*/%()^=]
static Token* get_oper() {

    return NULL;
}

Token* consumeToken() {

    Token* tok;

    memset(tok_buf, 0, sizeof(tok_buf));
    bidx = 0;

    while(isspace(getChar()))
        consumeChar();

    int ch = getChar();
    if(ch == END_OF_LINE || ch == 0) {
        consumeChar(); // consume the EOL
        tok = createToken(TOK_EOL);
    }
    else if(isalpha(ch) || ch == '_')
        tok = get_string();
    else if(isdigit(ch))
        tok = get_number();
    else
        tok = get_oper();

    _crnt_ = tok;
    return _crnt_;
}

Token* createToken(TokenType t) {

    Token* ptr = _alloc_obj(struct _token_);
    ptr->type = t;

    return ptr;
}

void destroyToken(Token* tok) {

    if(tok != NULL) {
        _free(tok->str);
        _free(tok);
    }
}

Token* crntToken() {

    return _crnt_;
}

Token* expectToken(TokenType t) {

    if(_crnt_->type != t) {
        syntaxError("expected %s but got %s",
                    tokTypeToStr(t), tokTypeToStr(_crnt_->type));
        return createToken(TOK_ERROR);
    }

    return _crnt_;
}

void printToken(Token* tok) {

    printf("TOKEN: %s: %s\n", tokTypeToStr(tok->type), tok->str);
}

const char* tokTypeToStr(TokenType t) {

    return ((t == TOK_NUM)? "NUM" :
        (t == TOK_SYM)? "SYM" :
        (t == TOK_ADD)? "ADD" :
        (t == TOK_SUB)? "SUB" :
        (t == TOK_MUL)? "MUL" :
        (t == TOK_DIV)? "DIV" :
        (t == TOK_MOD)? "MOD" :
        (t == TOK_POW)? "POW" :
        (t == TOK_EQU)? "EQU" :
        (t == TOK_UMINUS)? "UMINUS" :
        (t == TOK_UPLUS)? "UPLUS" :
        (t == TOK_OPAREN)? "OPAREN" :
        (t == TOK_CPAREN)? "CPAREN" :
        (t == TOK_COS)? "COS" :
        (t == TOK_SIN)? "SIN" :
        (t == TOK_TAN)? "TAN" :
        (t == TOK_ACOS)? "ACOS" :
        (t == TOK_ASIN)? "ASIN" :
        (t == TOK_ATAN)? "ATAN" :
        (t == TOK_COSH)? "COSH" :
        (t == TOK_SINH)? "SINH" :
        (t == TOK_TANH)? "TANH" :
        (t == TOK_ACOSH)? "ACOSH" :
        (t == TOK_ASINH)? "ASINH" :
        (t == TOK_ATANH)? "ATANH" :
        (t == TOK_LOG)? "LOG" :
        (t == TOK_SQRT)? "SQRT" :
        (t == TOK_CBRT)? "CBRT" :
        (t == TOK_CEIL)? "CEIL" :
        (t == TOK_FLOOR)? "FLOOR" :
        (t == TOK_ABS)? "ABS" :
        (t == TOK_EOL)? "EOL" :
        (t == TOK_EOF)? "EOF" :
        (t == TOK_HELP)? "HELP" :
        (t == TOK_QUIT)? "QUIT" :
        (t == TOK_SYMS)? "SYMS" :
        (t == TOK_PRINT)? "PRINT" :
        (t == TOK_ERROR)? "ERROR" : "UNKNOWN");
}

int getTokenLine() {

    return getLine();
}

int getTokenCol() {

    return getCol();
}

const char* getTokenFile() {

    return getFname();
}

TokenType getTokenType() {

    return _crnt_->type;
}

const char* getTokenStr() {

    return _crnt_->str;
}

const char* getTokenSym() {

    return _crnt_->data.str;
}

double getTokenNum() {

    return _crnt_->data.num;
}