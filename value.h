#ifndef _VALUE_H
#define _VALUE_H

#include "scan.h"
#include "errors.h"
#include "ptrlst.h"

typedef List ValueLst;

#define createValueLst()        (ValueLst)createList()
#define addValueLst(lst, v)     addList((List)(lst), (void*)(v))
#define getValueLst(lst, i)     (Value*)getList((List)(lst), (i))
#define resetValueLst(lst)      resetList((List)lst)
#define iterateValueLst(lst)    (Value*)iterateList((List)lst)

typedef enum {
    VAL_OPERATOR,
    VAL_NUMBER,
    VAL_VARIABLE,
    VAL_EXPRESSION,
} ValueType;

typedef struct {
    ValueType type;
    Token* tok;
    bool is_assigned;
    union {
        void* expr;
        double num;
    } data;
} Value;

Value* createValue(ValueType type, Token* tok);
void destroyValue(Value* val);
void showValue(Value* val);
void assignValueNum(Value* ptr, double num);
void assignValueExpr(Value* ptr, void* expr);

#endif /* _VALUE_H */

