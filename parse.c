
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "parse.h"
#include "value.h"
#include "scan.h"
#include "cmds.h"
#include "calc.h"

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

            case TOK_EOL:
            case TOK_EOF:
                finished = true;
                consumeToken();
                break;

            default:
                finished = consumeExpr();
                break;
        }
    }

    return result;
}


/*
    consumeToken();
    while(!TOKEN_IS_EOF && crntToken()->type != TOK_QUIT) {
        while(!TOKEN_IS_EOL) {
            printToken(crntToken());
            consumeToken();
        }
        consumeToken();
    }
*/