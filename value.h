#ifndef _VALUE_H
#define _VALUE_H

/*
 * Definitions for the values.
 */
typedef enum {
    // An actual number
    VAL_OPERAND,

    // Binary, left assoc operators
    VAL_ADD,
    VAL_SUB,
    VAL_MUL,
    VAL_DIV,
    VAL_MOD,
    VAL_POW,    // the '^' operator

    // Right assoc unary operators
    VAL_UMINUS, // sign switch to -
    VAL_UPLUS,  // only sign switch to +

    // Right assoc unary functions with 1 parameter
    VAL_COS,
    VAL_SIN,
    VAL_TAN,
    VAL_ACOS,
    VAL_ASIN,
    VAL_ATAN,
    VAL_COSH,
    VAL_SINH,
    VAL_TANH,
    VAL_ACOSH,
    VAL_ASINH,
    VAL_ATANH,
    VAL_LOG,
    VAL_SQRT,
    VAL_CBRT,
    VAL_CEIL,
    VAL_FLOOR,
    VAL_ABS,

    // Non-assoc and no precedence.
    VAL_OPAREN,
    VAL_CPAREN,
} ValueType;

typedef void* Value;

#define createValue(t) _create_value(t)
#define destroyValue(v) _destroy_value(v)
#define setValue(v, n) _set_value((v), (n))
#define getValue(v) _get_value(v)
#define printValue(v) _print_value(v)

struct _value_* _create_value(ValueType t);
void _destroy_value(struct _value_* val);
void _set_value(struct _value_* val, double num);
double _get_value(struct _value_* val);
void _print_value(struct _value_* val);

#endif /* _VALUE_H */

