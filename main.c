
#include <stdio.h>
#include <stdbool.h>

#include "scan.h"
#include "errors.h"
#include "fileio.h"

int main(int argc, char** argv) {

    openFile(argv[1]);
    Token* tok = consumeToken(); // prime the pump

    while(!TOKEN_IS_EOL) {
        printToken(crntToken());
        consumeToken();
    }

    return getNumErrors();
}

#if 0
// test the fileio
int main(int argc, char** argv) {

    openFile(argv[1]);
    int ch = consumeChar();
    while(ch != END_OF_FILE) {
        do {
            if(ch > 0)
                fputc(ch, stderr);
            ch = consumeChar();

            if(ch == END_OF_LINE || ch == END_OF_FILE)
                fprintf(stderr, "EOL\n");

        } while(ch != END_OF_LINE && ch != END_OF_FILE);
        syntaxError("fake error: %s", "blart!");
    }

    return getNumErrors();
}
#endif