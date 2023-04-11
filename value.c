#include <stdio.h>
#include <stdbool.h>

#include "value.h"
#include "errors.h"
#include "memory.h"

Value* createValue(ValueType type, Token* tok) {

    Value* val = _alloc_obj(Value);
    val->type = type;
    val->tok = tok;
    val->is_assigned = false;

    return val;
}

void destroyValue(Value* val) {

    (void)val;
}

void showValue(Value* val) {

    switch(val->type) {
        case VAL_OPERATOR:
        case VAL_NUMBER:
            printToken(val->tok);
            break;
        case VAL_EXPRESSION:
            printf("expression");
            break;
        case VAL_VARIABLE:
            printToken(val->tok);
            break;
        default:
            fatalError("unknown value type is showValue(): %d", val->type);
    }
}

void assignValueNum(Value* ptr, double num) {

    ptr->data.num = num;
    ptr->is_assigned = true;
}

void assignValueExpr(Value* ptr, void* expr) {

    ptr->data.expr = expr;
    ptr->is_assigned = true;
}

