#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

#include "parse.h"
#include "scan.h"
#include "cmds.h"
#include "calc.h"
#include "value.h"
#include "memory.h"
#include "symbols.h"

/*
 * Turn the expression list from the scanner into the value list that the
 * expression evaluator can handle.
 */
static void* consume_expression() {

    bool finished = false;

    while(!finished) {
        switch(crntToken()->type) {
            case TOK_EOL:
                finished = true;
                consumeToken();
                break;
            default:
                printToken(crntToken());
                fputc('\n', stdout);
                consumeToken();
        }
    }

    return NULL;
}

#if 0
static double solve_expression(void* expr) {
    (void)expr;
    return 0.0;
}

static void show_result(void* expr) {

    printf("result: %f\n", solve_expression(expr));
}
#else
static void show_result() {

    printf("result: 0.0 (stub)\n");
}
#endif

/*
 * When this is called, a symbol is the first thing encountered. The next
 * thing in the input stream determins what to do:
 *
 * symbol =
 *      the next thing is an expression and the symbol holds a number.
 * symbol <
 *      the next thing is an expression and the symbol holds a parsed
 *      expression.
 * symbol (EOL)
 *      request to print the contents of the symbol.
 */
static void parse_symbol() {

    Value* val;
    Token* tok = crntToken();
    ValueLst lst = createValueLst();

    val = createValue(VAL_VARIABLE, tok);
    addSymValue(tok->str, val);
    addValueLst(lst, val);
    consumeToken(); // consume the TOK_SYM

    switch(crntToken()->type) {
        case TOK_EQU:
        case TOK_EXPR:
            // assign the value of the expression to the variable
            val = createValue(VAL_OPERATOR, crntToken());
            addValueLst(lst, val);
            val = createValue(VAL_EXPRESSION, NULL);
            val->data.expr = consume_expression();
            addValueLst(lst, val);
            break;
        case TOK_EOL:
            // simply print the result of the value specified
            show_result();
            break;
        default:
            // everything else is syntax error
            syntaxError("expected a '=', '<', or EOL, but got %s",
                            tokTypeToStr(crntToken()->type));
            break;
    }

#if 0
    Value* val = createValue(VAL_VARIABLE, crntToken());
    addSymValue(crntToken()->str, val);
    consumeToken();

    if(crntToken()->type == TOK_EQU) {
        // symbol holds a number
        val = createValue(VAL_OPERATOR, crntToken());
        consumeToken();
        void* expr = consume_expression();
        assignValueNum(val, solve_expression(expr));
    }
    else if(crntToken()->type == TOK_EXPR) {
        // symbol holds an expression
        val = createValue(VAL_OPERATOR, crntToken());
        consumeToken();
        assignValueExpr(val, consume_expression());
    }
    else if(crntToken()->type == TOK_EOL) {
        // print the contents of the symbol
        Value* val = getSymbol(key);
        if(val == NULL)
            syntaxError("name \"%s\" is undefined", key);
        else {
            showValue(val);
            fputc('\n', stdout);
        }
    }
    else {
        // else a syntax error
    }
#endif
}

/*
 * This assumes that the commands are already handled and is looking for an
 * expression or a print request.
 */
static bool consume_line() {

    bool finished = false;

    while(!finished) {
        switch(crntToken()->type) {
            case TOK_EOL:
                finished = true;
                consumeToken();
                break;
            case TOK_SYM:
                parse_symbol();
                break;
            default:
                show_result(consume_expression());
                break;
        }
    }

    return true; // return after evaluating the line
}

bool parse() {

    Token* tok;
    bool finished = false;
    bool result = false; // continue by default

    while(!finished) {
        tok = crntToken();
        switch(tok->type) {
            // parse the commands
            case TOK_HELP: finished = do_HELP(); break;
            case TOK_QUIT: result = finished = do_QUIT(); break;
            case TOK_SYMS: finished = do_SYMS(); break;
            case TOK_PRINT: finished = do_PRINT(); break;
            case TOK_VERBO: finished = do_VERBOSITY(); break;
            case TOK_LOAD: finished = do_LOAD(); break;
            case TOK_SAVE: finished = do_SAVE(); break;
            case TOK_SOLVE: finished = do_SOLVE(); break;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough="
            case TOK_EOF:
                result = true;
                // fall through
            case TOK_EOL:
                finished = true;
                consumeToken();
                break;
#pragma GCC diagnostic pop

            default:
                finished = consume_line();
                break;
        }
    }
    return result;
}

