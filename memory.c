#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* _mem_alloc(size_t size) {

    void* ptr = malloc(size);
    if(ptr == NULL) {
        fprintf(stderr, "memory error: cannot allocate %lu bytes\n", size);
        exit(1);
    }

    memset(ptr, 0, size);
    return ptr;
}

void* _mem_realloc(void* ptr, size_t size) {

    void* nptr = malloc(size);
    if(ptr == NULL) {
        fprintf(stderr, "memory error: cannot allocate %lu bytes\n", size);
        exit(1);
    }

    if(ptr != NULL) {
        memcpy(nptr, ptr, size);
        free(ptr);
    }
    else
        memset(nptr, 0, size);

    return nptr;
}

void _mem_free(void* ptr) {

    if(ptr != NULL)
        free(ptr);
}

void* _mem_dup(void* ptr, size_t size) {

    return _mem_realloc(ptr, size);
}

char* _mem_dup_str(const char* str) {

    size_t len;
    char* ptr;

    if(str == NULL)
        len = 1;
    else
        len = strlen(str);

    ptr = malloc(len);
    memset(ptr, 0, len);

    if(str != NULL)
        memcpy(ptr, str, len);

    return ptr;
}
