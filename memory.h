#ifndef _MEMORY_H_
#define _MEMORY_H_

#define _init_memory()
#define _destroy_memory()
#define _alloc(s) _mem_alloc(s)
#define _alloc_obj(t) (t*)_mem_alloc(sizeof(t))
#define _alloc_obj_array(t, n) (t*)_mem_alloc(sizeof(t) * (n))
#define _realloc(p, s) _mem_realloc((void*)(p), (s))
#define _realloc_obj(p, t) (t*)_mem_realloc((void*)(p), sizeof(t))
#define _realloc_obj_array(p, t, n) (t*)_mem_realloc((void*)(p), sizeof(t)*(n))
#define _free(p) _mem_free((void*)p)
#define _dup_obj(p, t) (t*)_mem_dup((void*)(p), sizeof(t))
#define _dup_obj_array(p, t, n) (t*)_mem_dup((void*)(p), sizeof(t)*(n))
#define _dup_str(s) _mem_dup_str(s)

#include <stddef.h>

void* _mem_alloc(size_t size);
void* _mem_realloc(void* ptr, size_t size);
void _mem_free(void* ptr);
void* _mem_dup(void* ptr, size_t size);
char* _mem_dup_str(const char* str);

#endif
