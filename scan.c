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
static bool unary = true;

static struct _keywords_ {
    const char* name;
    TokenType type;
} keyword_list [] = {
#include "keyword_list.h"
    {NULL, -1}
};
static const int num_keywords = (sizeof(keyword_list)/sizeof(struct _keywords_))-1;

// Simple binary search.
static int find_keyword(const char* word) {

    int low = 0, high = num_keywords-1;
    int mid = (low + high) / 2;
    char buf[64];

    // make it case-insensitive
    memset(buf, 0, sizeof(buf));
    for(int i = 0; word[i] != 0; i++)
        buf[i] = toupper(word[i]);

    // iterative binary search
    while(low <= high) {
        if (strcmp(keyword_list[mid].name, buf) == 0)
            return keyword_list[mid].type;
        else if (strcmp(keyword_list[mid].name, buf) < 0)
            low = mid + 1;
        else
            high = mid - 1;

        mid = (low + high) / 2;
    }

    return TOK_SYM;
}

// [a-zA-Z_][a-zA-Z_0-9]*
static Token* get_string() {

    while(true) {
        int ch = getChar();
        if((isalpha(ch) || ch == '_' || isdigit(ch))) {
            tok_buf[bidx++] = ch;
            consumeChar();
        }
        else
            break;
    }

    unary = false;
    int type = find_keyword(tok_buf);
    Token* tok = createToken(type);
    tok->data.str = _dup_str(tok_buf);
    tok->str = _dup_str(tok_buf);
    return tok;
}

static void get_num_2() {

    int ch = getChar();
    if(ch == '-' || ch == '+') {
        tok_buf[bidx++] = ch;
        consumeChar();
    }

    while(true) {
        ch = getChar();
        if(isdigit(ch)) {
            tok_buf[bidx++] = ch;
            consumeChar();
        }
        else
            break;
    }
}

static void get_num_1() {

    while(true) {
        int ch = getChar();
        if(isdigit(ch)) {
            tok_buf[bidx++] = ch;
            consumeChar();
        }
        else if(ch == 'e' || ch == 'E') {
            tok_buf[bidx++] = ch;
            consumeChar();
            get_num_2();
            break;
        }
        else
            break;
    }
}

// [0-9]*((\.[0-9]+)+([eE][-+]*[0-9]+)*)
static Token* get_number() {

    while(true) {
        int ch = getChar();
        if(isdigit(ch)) {
            tok_buf[bidx++] = ch;
            consumeChar();
        }
        else if(ch == '.') {
            tok_buf[bidx++] = ch;
            consumeChar();
            get_num_1();
            break;
        }
        else
            break;
    }

    unary = false;
    Token* tok = createToken(TOK_NUM);
    tok->data.num = strtod(tok_buf, NULL);
    tok->str = _dup_str(tok_buf);
    return tok;
}

// [+-*/%()^=]
static Token* get_oper() {

    int ch = getChar();
    switch(ch) {
        case '+':
            consumeChar();
            if(unary)
                return createToken(TOK_UPLUS);
            else {
                unary = true;
                return createToken(TOK_ADD);
            }
        case '-':
            consumeChar();
            if(unary)
                return createToken(TOK_UMINUS);
            else {
                unary = true;
                return createToken(TOK_SUB);
            }
        case '*':
            consumeChar();
            unary = true;
            return createToken(TOK_MUL);
        case '/':
            consumeChar();
            unary = true;
            return createToken(TOK_DIV);
        case '%':
            consumeChar();
            unary = true;
            return createToken(TOK_MOD);
        case '^':
            consumeChar();
            unary = true;
            return createToken(TOK_POW);
        case '(':
            consumeChar();
            unary = true;
            return createToken(TOK_OPAREN);
        case ')':
            consumeChar();
            unary = false;
            return createToken(TOK_CPAREN);
        case '<':
            consumeChar();
            unary = false;
            return createToken(TOK_EXPR);
        case '=':
            consumeChar();
            unary = false;
            return createToken(TOK_EQU);
        default:
            consumeChar();
            syntaxError("unknown operator: %c", ch);
            return createToken(TOK_ERROR);
            break;
    }
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

    printf("TOKEN: %s", tokTypeToStr(tok->type));
    switch(tok->type) {
        case TOK_NUM:
            printf(": \"%s\": %f\n", tok->str, tok->data.num);
            break;
        case TOK_SYM:
            printf(": \"%s\": %s\n", tok->str, tok->data.str);
            break;
        case TOK_ADD:
        case TOK_SUB:
        case TOK_MUL:
        case TOK_DIV:
        case TOK_MOD:
        case TOK_POW:
        case TOK_EQU:
        case TOK_EXPR:
        case TOK_UMINUS:
        case TOK_UPLUS:
        case TOK_OPAREN:
        case TOK_CPAREN:
        default:
            printf("\n");
            break;
    }
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
        (t == TOK_VERBO)? "VERBOSITY" :
        (t == TOK_LOAD)? "LOAD" :
        (t == TOK_SAVE)? "SAVE" :
        (t == TOK_SOLVE)? "SOLVE" :
        (t == TOK_EXPR)? "EXPR" :
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