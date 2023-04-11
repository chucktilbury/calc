
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "parse.h"
#include "errors.h"
#include "fileio.h"
#include "hash.h"
#include "memory.h"
#include "symbols.h"

extern Hash* symbol_table; // defined in symbols.c

int main(int argc, char** argv) {

    bool finished = false;

    _init_memory();
    createSymbolTable();

    if(argc < 2)
        openFile(NULL);
    else
        openFile(argv[1]);

    consumeChar(); // prime the pipeline
    while(!finished)
        // parse individual lines until finished
        finished = parse();

    destroySymbolTable();
    _destroy_memory();

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