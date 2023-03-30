
#include <stdlib.h>
#include "memory.h"

struct _plst_ {
    void** array;
    int len;
    int cap;
    int idx;
};

typedef struct _plst_ PLst;

struct _plst_* _lst_create() {

    PLst* ptr = _alloc_obj(struct _plst_);
    ptr->idx = 0;
    ptr->len = 0;
    ptr->cap = 0x01 << 3;
    ptr->array = _alloc_obj_array(void*, ptr->cap);

    return ptr;
}

void _lst_destroy(struct _plst_* lst) {

    if(lst != NULL) {
        for(int i = 0; i < lst->len; i++)
            _free(lst->array[i]);
        _free(lst->array);
        _free(lst);
    }
}

void _lst_add(struct _plst_* lst, void* ptr)  {

    if(lst->len+1 > lst->cap) {
        lst->cap <<= 1;
        lst->array = _realloc_obj_array(lst->array, void*, lst->cap);
    }

    lst->array[lst->len] = ptr;
    lst->len++;
}

void* _lst_get(struct _plst_* lst, int idx) {

    void* ptr = NULL;

    if(idx < lst->len)
        ptr = lst->array[lst->idx];

    return ptr;
}

void _lst_push(struct _plst_* lst, void* ptr) {

    _lst_add(lst, ptr);
}

void* _lst_pop(struct _plst_* lst) {

    void* ptr = NULL;

    if(lst->len > 0) {
        lst->len--;
        ptr = lst->array[lst->len];
    }

    return ptr;
}

void* _lst_peek(struct _plst_* lst) {

    void* ptr = NULL;

    if(lst->len > 0)
        ptr = lst->array[lst->len-1];

    return ptr;
}

void _lst_reset(struct _plst_* lst) {

    lst->idx = 0;
}

void* _lst_iterate(struct _plst_* lst) {

    void* ptr = NULL;

    if(lst->idx < lst->len) {
        ptr = lst->array[lst->idx];
        lst->idx++;
    }

    return ptr;
}

int _lst_len(struct _plst_* lst) {

    return lst->len;
}

void** _lst_raw(struct _plst_* lst) {

    return lst->array;
}

int _lst_empty(struct _plst_* lst) {

    return (lst->len == 0);
}

void _lst_append(struct _plst_* to, struct _plst_* from) {

    _lst_reset(from);
    for(void* ptr = _lst_iterate(from); ptr != NULL; ptr = _lst_iterate)
        _lst_add(to, ptr);
}

