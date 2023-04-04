#ifndef _VALUE_H
#define _VALUE_H

#include "scan.h"

typedef enum {
    VAL_OPERATOR,
    VAL_NUMBER,
    VAL_SYMBOL,
    VAL_EXPRESSION,
    VAL_COMMAND,
} ValueType;

typedef struct {
    ValueType type;
    union {
        Token* tok;
        void* expr;
    } data;
} Value;

Value* createValue(ValueType type, Token* tok);
void destroyValue(Value* val);


#endif /* _VALUE_H */

