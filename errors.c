
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "scan.h"

static int errors = 0;
static int warnings = 0;

void syntaxError(const char* fmt, ...) {

    va_list args;

    fprintf(stderr, "SYNTAX: %s: %d:%d: ",
            getTokenFile(), getTokenLine(), getTokenCol());

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fputc('\n', stderr);

    errors++;
}

void syntaxWarning(const char* fmt, ...) {

    va_list args;

    fprintf(stderr, "WARNING: %s: %d:%d: ",
            getTokenFile(), getTokenLine(), getTokenCol());

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fputc('\n', stderr);

    warnings++;
}

void fatalError(const char* fmt, ...) {

    va_list args;

    fprintf(stderr, "FATAL: ");

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fputc('\n', stderr);

    errors++;
    exit(1);
}

void generalError(const char* fmt, ...) {

    va_list args;

    fprintf(stderr, "GENERAL: ");

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fputc('\n', stderr);

    errors++;
}

int getNumErrors() {

    return errors;
}

int getNumWarnings() {

    return warnings;
}
