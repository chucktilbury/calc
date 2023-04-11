#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "memory.h"
#include "symbols.h"
#include "hash.h"

static Hash* symbol_table;

static void symbol_destroyer(const char* key, void* sym) {

    (void)key;
    destroySymbol((Symbol*)sym);
}

static void show_symbol(const char* key, void* ptr) {

    Symbol* sym = (Symbol*)ptr;
    printf("\"%s\": ", key);
    if(sym->is_assigned)
        showValue(sym->value);
    else
        printf("not assigned");
    fputc('\n', stdout);
}

void createSymbolTable() {

    symbol_table = hashCreate();
}

void destroySymbolTable() {

    // for(int i = 0; i < symbol_table->cap; i++) {
    //     if(symbol_table->table[i] != NULL) {
    //         if(symbol_table->table[i]->key != NULL) {
    //             destroySymbol((Symbol*)symbol_table->table[i]->data);
    //         }
    //     }
    // }
    hashDump(symbol_table, symbol_destroyer);
    hashDestroy(symbol_table);
}

Symbol* createSymbol(Value* val) {

    Symbol* ptr = _alloc_obj(Symbol);
    ptr->is_assigned = (val == NULL)? false: true;
    ptr->value = val;

    return ptr;
}

void destroySymbol(Symbol* ptr) {

    if(ptr != NULL) {
        destroyValue(ptr->value);
        // This pointer is controlled by the hash table.
        //_free(ptr);
    }
}

void assignSymbol(Symbol* ptr, Value* val) {

    // TODO: issue a warning when changing types
    ptr->value = val;
    ptr->is_assigned = true;
}

Value* getSymbol(const char* key) {

    Symbol sym = {false, NULL};
    if(!(hashFind(symbol_table, key, &sym, sizeof(Symbol)) == HASH_OK))
        return NULL;
    else
        return sym.value;
}

void addSymValue(const char* key, Value* ptr) {

    // If the symbol already exists, then just change the value
    Symbol sym = {false, NULL};
    if(hashFind(symbol_table, key, &sym, sizeof(Symbol)) == HASH_OK) {
        if(sym.value != NULL)
            destroyValue(sym.value);
        sym.value = ptr;
    }
    else {
        Symbol* nsym = createSymbol(ptr);
        HashResult hres = hashInsert(symbol_table, key, nsym, sizeof(Symbol));
        if(!(HASH_OK == hres))
            fatalError("insert symbol failed for \"%s\"", key);
    }
}

void dumpSymbolTable() {

    hashDump(symbol_table, show_symbol);
}