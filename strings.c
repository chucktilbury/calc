
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "memory.h"

struct _string_ {
    unsigned char* array;
    int len;
    int cap;
    int idx;
};

int _str_append_char(struct _string_* str, int ch) {

    if(str->len+2 > str->cap) {
        str->cap <<= 1;
        str->array = _realloc_obj_array(str->array, unsigned char, str->cap);
    }

    str->array[str->len] = (unsigned char)ch;
    str->len++;

    return str->len;
}

int _str_append_str(struct _string_* str, const char* ptr) {

    int len = strlen(ptr);

    if(str->len+len+1 > str->cap) {
        while(str->len+len+1 > str->cap)
            str->cap <<= 1;
        str->array = _realloc_obj_array(str->array, unsigned char, str->cap);
    }

    memcpy(&str->array[str->len], ptr, len);
    str->len += len;

    return str->len;
}

int _str_append_format(struct _string_* str, const char* ptr, ...) {

    va_list(args);

    va_start(args, ptr);
    size_t len = vsnprintf(NULL, 0, ptr, args);
    va_end(args);
    len++;

    char* buff = _alloc(len);
    va_start(args, ptr);
    vsnprintf(buff, len, ptr, args);
    va_end(args);

    int retv = _str_append_str(str, buff);
    _free(buff);
    return retv;
}

int _str_append_string(struct _string_* str, struct _string_* ptr) {

    return _str_append_str(str, (const char*)ptr->array);
}

const char* _str_raw(struct _string_* str) {

    str->array[str->len] = 0;
    return (const char*)str->array;
}

void _str_reset(struct _string_* str) {

    str->idx = 0;
}

int _str_iterate(struct _string_* str) {

    int ch = 0;

    if(str->idx < str->len) {
        ch = str->array[str->idx];
        str->idx++;
    }

    return ch;
}

struct _string_* _str_create(const char* str) {

    struct _string_* ptr = _alloc_obj(struct _string_);
    ptr->len = 0;
    ptr->idx = 0;
    ptr->cap = 0x01 << 3;
    ptr->array = _alloc_obj_array(unsigned char, ptr->cap);

    if(str != NULL)
        _str_append_str(ptr, str);

    return ptr;
}

void _str_destroy(struct _string_* str) {

    if(str != NULL) {
        _free(str->array);
        _free(str);
    }
}

int _str_find_char(struct _string_* str, int index, int ch) {

    if(index < 0 || index > str->len)
        return -1; // not found

    const char* i = strchr((char*)&str->array[index], ch);
    if(i == NULL)
        return -1;

    return (int)((unsigned long)i - (unsigned long)str->array);
}

void _str_repl_char(struct _string_* str, int index, int ch) {

    if(index < 0 || index > str->len)
        return; // silent fail!

    str->array[index] = ch;
}

// Find a char from the end of the string where the index is taken to be
// the end. If the index <=0 then ignore the index. If the index > len then
// return not found.
int _str_find_rev_char(struct _string_* str, int index, int ch) {

    if(index <= 0)
        index = str->len+1;
    else if(index > str->len)
        return -1; // not found

    unsigned char tmp = str->array[index];
    str->array[index] = 0;

    const char* i = strrchr((char*)str->array, ch);
    if(i == NULL)
        return -1;

    str->array[index] = tmp;
    return (int)((unsigned long)i - (unsigned long)str->array);
}

// chop a string off at the index.
void _str_truncate(struct _string_* str, int index) {

    if(index < 0 || index > str->len)
        return; // silent fail!

    str->array[index] = 0;
    str->len = index;
}

// insert a formatted sub string at the index and return the length.
int _str_insert_format(struct _string_* str, int index, const char* ptr, ...) {

    va_list(args);

    va_start(args, ptr);
    size_t len = vsnprintf(NULL, 0, ptr, args);
    va_end(args);
    len++;

    char* buff = _alloc(len);
    va_start(args, ptr);
    vsnprintf(buff, len, ptr, args);
    va_end(args);

    int retv = 0;
    if(index < 0 || index > str->len) {
        retv = _str_append_str(str, buff);
    }
    else {
        const char* tmp = _dup_str((char*)&str->array[index]);
        _str_truncate(str, index);
        //printf("tmp: %s\n", tmp);
        //printf("buff: %s\n", buff);
        //printf("str: %s\n", str->array);
        _str_append_str(str, buff);
        retv = _str_append_str(str, tmp);
        _free(tmp);
    }

    _free(buff);

    return retv;
}

