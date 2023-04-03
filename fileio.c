/*
 * If the open file call is NULL, then implement a REPL functionality.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "fileio.h"
#include "errors.h"
#include "memory.h"

static FILE* fp = NULL;
static char* fname = "console";
static char line_buf[1024];
static int bidx = 0;
static int line_no = 1;
static int col_no = 1;

static void get_line() {

    memset(line_buf, 0, sizeof(line_buf));
    bidx = 0;
    line_no++;
    col_no = 1;

    if(fp != NULL) {
        char *ptr = fgets(line_buf, sizeof(line_buf), fp);
        if(ptr == NULL)
            line_buf[0] = -2;
    }
    else {
        while(true) {
            char* ptr = readline(">> ");
            if(ptr && *ptr) {
                strncpy(line_buf, ptr, sizeof(line_buf));
                add_history(ptr);
                free(ptr);
                break;
            }
            else
                line_no++;
        }
    }
}

void openFile(const char* name) {

    if(name != NULL) {
        fp = fopen(name, "r");
        if(fp == NULL)
            generalError("cannot open file \"%s\": %s", name, strerror(errno));
        else
            fname = _dup_str(name);
    }

    get_line();
}

int getChar() {

    if(line_buf[0] == END_OF_FILE)
        return END_OF_FILE;
    else if(line_buf[0] == END_OF_LINE)
        return END_OF_LINE;
    else
        return line_buf[bidx];
}

int consumeChar() {

    if(line_buf[0] == END_OF_LINE) {
        get_line();
        return line_buf[bidx];
    }
    else {
        if(line_buf[0] == END_OF_FILE)
            return END_OF_FILE;
        else if(line_buf[bidx] == 0 || line_buf[bidx] == '\n') {
            line_buf[0] = END_OF_LINE;
            return END_OF_LINE;
        }
        else {
            col_no++;
            return line_buf[bidx++];
        }
    }
}

int getLine() {

    return line_no;
}

int getCol() {

    return col_no;
}

const char* getFname() {

    return fname;
}

