
#include <stdbool.h>

#include "scan.h"

bool consumeExpr() {

    printToken(crntToken());
    consumeToken();

    return true; // return after evaluating the line
}