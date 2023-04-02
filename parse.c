
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#include "parse.h"
#include "value.h"

struct _translate_ {
    int val;
    const char* str;
} trans_table[] = {
    {VAL_ADD, "+"},
    {VAL_SUB, "-"},
    {VAL_MUL, "*"},
    {VAL_DIV, "/"},
    {VAL_MOD, "%"},
    {VAL_POW, "^"},
    {VAL_UMINUS, "-"},
    {VAL_UPLUS, "+"},
    {VAL_COS, "cos"},
    {VAL_SIN, "sin"},
    {VAL_TAN, "tan"},
    {VAL_ACOS, "acos"},
    {VAL_ASIN, "asin"},
    {VAL_ATAN, "atan"},
    {VAL_COSH, "cosh"},
    {VAL_SINH, "sinh"},
    {VAL_TANH, "tanh"},
    {VAL_ACOSH, "acosh"},
    {VAL_ASINH, "asinh"},
    {VAL_ATANH, "atanh"},
    {VAL_LOG, "log"},
    {VAL_SQRT, "sqrt"},
    {VAL_CBRT, "cbrt"},
    {VAL_CEIL, "ceil"},
    {VAL_FLOOR, "floor"},
    {VAL_ABS, "abs"},
    {VAL_OPAREN, "("},
    {VAL_CPAREN, ")"},
    {-1, NULL}
};

static char static_buffer[1024];
static int bidx = 0;

static const char* charToTok(int ch) {

    bidx = 0;
    memset(static_buffer, 0, sizeof(static_buffer))

}


static Value get_token(String s) {


}

/**
 * @brief Input a string as an expression and convert it to a queue of values.
 *
 * @param str
 * @return Queue
 */
Queue parse(String str) {

    Queue que = createQueue();

    resetString(str);
    for(int ch = iterateString(str); ch != 0; ch = iterateString(str)) {
        if(isdigit(ch)) {

        }
    }

    return que;
}