#ifndef _SYMBOLS_H
#define _SYMBOLS_H

#include <stdbool.h>
#include "value.h"

typedef struct {
    bool is_assigned;
    Value* value;
} Symbol;

void createSymbolTable();
void destroySymbolTable();
Symbol* createSymbol(Value*);
void destroySymbol(Symbol*);
void assignSymbol(Symbol*, Value*);

Value* getSymbol(const char*);
void addSymValue(const char* key, Value* ptr);
void dumpSymbolTable();

#endif /* _SYMBOLS_H */
