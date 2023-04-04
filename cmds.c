#include <stdio.h>
#include <stdlib.h>

#include "cmds.h"
#include "scan.h"

bool do_HELP() {

    printf("help\n");
    return false;
}

// TODO: add an "are you sure" prompt.
bool do_QUIT() {

    printf("quit\n");
    consumeToken();
    //exit(0);
    return true; // make the compiler happy
}

bool do_SYMS() {

    printf("symbols\n");
    consumeToken();
    return false;
}

bool do_PRINT() {

    printf("print\n");
    consumeToken();
    return false;
}

bool do_VERBOSITY() {

    printf("verbosity\n");
    consumeToken();
    return false;
}

bool do_LOAD() {

    printf("load\n");
    consumeToken();
    return false;
}

bool do_SAVE() {

    printf("save\n");
    consumeToken();
    return false;
}

bool do_SOLVE() {

    printf("solve\n");
    consumeToken();
    return false;
}

