#ifndef _SCAN_H
#define _SCAN_H

typedef enum {
    // constructed tokens
    TOK_NUM,
    TOK_SYM,

    // Binary, left assoc operators
    TOK_ADD,
    TOK_SUB,
    TOK_MUL,
    TOK_DIV,
    TOK_MOD,
    TOK_POW,    // the '^' operator
    TOK_EQU,    // the '=' operator

    // Right assoc unary operators
    TOK_UMINUS, // sign switch to -
    TOK_UPLUS,  // only sign switch to +

    // Non-assoc and no precedence.
    TOK_OPAREN,
    TOK_CPAREN,

    // Right assoc unary functions with 1 parameter
    TOK_COS,
    TOK_SIN,
    TOK_TAN,
    TOK_ACOS,
    TOK_ASIN,
    TOK_ATAN,
    TOK_COSH,
    TOK_SINH,
    TOK_TANH,
    TOK_ACOSH,
    TOK_ASINH,
    TOK_ATANH,
    TOK_LOG,
    TOK_SQRT,
    TOK_CBRT,
    TOK_CEIL,
    TOK_FLOOR,
    TOK_ABS,

    TOK_EOL,
    TOK_EOF,

    TOK_HELP,
    TOK_QUIT,
    TOK_SYMS,
    TOK_PRINT,

    TOK_ERROR,
} TokenType;

typedef struct _token_ {
    TokenType type;
    const char* str;
    union {
        const char* str;
        double num;
    } data;
} Token;

Token* createToken(TokenType type);
void destroyToken(Token* tok);
Token* crntToken();
Token* consumeToken();
Token* expectToken(TokenType type);

void printToken(Token* tok);
const char* tokTypeToStr(TokenType t);

int getTokenLine();
int getTokenCol();
const char* getTokenFile();

TokenType getTokenType();
const char* getTokenStr();
const char* getTokenSym();
double getTokenNum();

#define TOKEN_IS_STR ((TOKEN_TYPE == TOK_SYM)? true: false)

#define TOKEN_IS_NUM ((TOKEN_TYPE == TOK_NUM)? true: false)

#define TOKEN_IS_OP ((TOKEN_TYPE == TOK_ADD)? true: \
                    (TOKEN_TYPE == TOK_SUB)? true: \
                    (TOKEN_TYPE == TOK_MUL)? true: \
                    (TOKEN_TYPE == TOK_DIV)? true: \
                    (TOKEN_TYPE == TOK_MOD)? true: \
                    (TOKEN_TYPE == TOK_POW)? true: \
                    (TOKEN_TYPE == TOK_EQU)? true: \
                    (TOKEN_TYPE == TOK_OPAREN)? true: \
                    (TOKEN_TYPE == TOK_CPAREN)? true: \
                    (TOKEN_TYPE == TOK_UMINUS)? true: \
                    (TOKEN_TYPE == TOK_UPLUS)? true: false)

#define TOKEN_IS_FUNC ((TOKEN_TYPE == TOK_COS)? true: \
                    (TOKEN_TYPE == TOK_SIN)? true: \
                    (TOKEN_TYPE == TOK_TAN)? true: \
                    (TOKEN_TYPE == TOK_ACOS)? true: \
                    (TOKEN_TYPE == TOK_ASIN)? true: \
                    (TOKEN_TYPE == TOK_ATAN)? true: \
                    (TOKEN_TYPE == TOK_COSH)? true: \
                    (TOKEN_TYPE == TOK_SINH)? true: \
                    (TOKEN_TYPE == TOK_TANH)? true: \
                    (TOKEN_TYPE == TOK_ACOSH)? true: \
                    (TOKEN_TYPE == TOK_ASINH)? true: \
                    (TOKEN_TYPE == TOK_ATANH)? true: \
                    (TOKEN_TYPE == TOK_LOG)? true: \
                    (TOKEN_TYPE == TOK_SQRT)? true: \
                    (TOKEN_TYPE == TOK_CBRT)? true: \
                    (TOKEN_TYPE == TOK_CEIL)? true: \
                    (TOKEN_TYPE == TOK_FLOOR)? true: \
                    (TOKEN_TYPE == TOK_ABS)? true: false)

#define TOKEN_IS_CMD ((TOKEN_TYPE == TOK_HELP)? true: \
                    (TOKEN_TYPE == TOK_QUIT)? true: \
                    (TOKEN_TYPE == TOK_SYMS)? true: \
                    (TOKEN_TYPE == TOK_PRINT)? true: false)

#define TOKEN_IS_EOL ((TOKEN_TYPE == TOK_EOL)? true: false)
#define TOKEN_IS_EOF ((TOKEN_TYPE == TOK_EOF)? true: false)

#define TOKEN_TYPE (crntToken()->type)
#define TOKEN_STR (crntToken()->str)
#define TOKEN_SYM (crntToken()->data.str)
#define TOKEN_NUM (crntToken()->data.num)
#define CONSUME _consume_token()

#endif /* _SCAN_H */
