#include <stdio.h>
#include <stdbool.h>

#include "value.h"
#include "memory.h"

struct _value_ {
    ValueType type;
    double num;
    bool is_assigned;
};

struct _value_* _create_value(ValueType t) {

    struct _value_* ptr = _alloc_obj(struct _value_);
    ptr->type = t;
    ptr->is_assigned = false;

    return ptr;
}

void _destroy_value(struct _value_* val) {

    _free(val);
}

void _set_value(struct _value_* val, double num) {

    val->num = num;
}

double _get_value(struct _value_* val) {

    return val->num;
}

static const char* typeToStr(ValueType type) {

    return (type == VAL_OPERAND)? "OPERAND":
        (type == VAL_ADD)? "ADD":
        (type == VAL_SUB)? "SUB":
        (type == VAL_MUL)? "MUL":
        (type == VAL_DIV)? "DIV":
        (type == VAL_MOD)? "MOD":
        (type == VAL_POW)? "POW":
        (type == VAL_COS)? "COS":
        (type == VAL_SIN)? "SIN":
        (type == VAL_TAN)? "TAN":
        (type == VAL_ACOS)? "ACOS":
        (type == VAL_ASIN)? "ASIN":
        (type == VAL_ATAN)? "ATAN":
        (type == VAL_COSH)? "COSH":
        (type == VAL_SINH)? "SINH":
        (type == VAL_TANH)? "TANH":
        (type == VAL_ACOSH)? "ACOSH":
        (type == VAL_ASINH)? "ASINH":
        (type == VAL_ATANH)? "ATANH":
        (type == VAL_LOG)? "LOG":
        (type == VAL_SQRT)? "SQRT":
        (type == VAL_CBRT)? "CBRT":
        (type == VAL_CEIL)? "CEIL":
        (type == VAL_ABS)? "ABS":
        (type == VAL_UMINUS)? "UMINUS":
        (type == VAL_UPLUS)? "UPLUS":
        (type == VAL_FLOOR)? "FLOOR": "UNKNOWN";
}

void _print_value(struct _value_* val) {

    switch(val->type) {
        case VAL_OPERAND:
            if(val->is_assigned)
                printf("value: %s %f\n", typeToStr(val->type), val->num);
            else
                printf("value: %s not assigned\n", typeToStr(val->type));
            break;
        case VAL_ADD:
        case VAL_SUB:
        case VAL_MUL:
        case VAL_DIV:
        case VAL_MOD:
        case VAL_UMINUS:
        case VAL_UPLUS:
            printf("operator: %s\n", typeToStr(val->type));
            break;
        case VAL_POW:
            printf("func: %s()\n", typeToStr(val->type));
            break;
        case VAL_COS:
        case VAL_SIN:
        case VAL_TAN:
        case VAL_ACOS:
        case VAL_ASIN:
        case VAL_ATAN:
        case VAL_COSH:
        case VAL_SINH:
        case VAL_TANH:
        case VAL_ACOSH:
        case VAL_ASINH:
        case VAL_ATANH:
        case VAL_LOG:
        case VAL_SQRT:
        case VAL_CBRT:
        case VAL_CEIL:
        case VAL_FLOOR:
        case VAL_ABS:
            printf("func: %s()", typeToStr(val->type));
            break;
        default:
            printf("unknown value type: %d\n", val->type);
    }
}
