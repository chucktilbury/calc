#ifndef _LST_H_
#define _LST_H_

typedef void* List;
//extern struct _plst_;

#define createList() _lst_create()
#define destroyList(l) _lst_destroy(l)
#define addList(l, v) _lst_add((l), (v))
#define appendList(l, p) _lst_append((l), (p))
#define getList(l, i) _lst_get((l), (i))
#define pushList(l, v) _lst_push((l), (v))
#define popList(l) _lst_pop(l)
#define peekList(l) _lst_peek(l)
#define resetList(l) _lst_reset(l)
#define iterateList(l) _lst_iterate(l)
#define lenList(l) _lst_len(l)
#define rawList(l) _lst_raw(l)
#define isEmptyList(l) _lst_empty(l)

struct _plst_* _lst_create();
void _lst_destroy(struct _plst_* lst);
void _lst_add(struct _plst_* lst, void* ptr);
void _lst_append(struct _plst_* lst, struct _plst_* ptr);
void* _lst_get(struct _plst_* lst, int idx);
void _lst_push(struct _plst_* lst, void* ptr);
void* _lst_pop(struct _plst_* lst);
void* _lst_peek(struct _plst_* lst);
void _lst_reset(struct _plst_* lst);
void* _lst_iterate(struct _plst_* lst);
int _lst_len(struct _plst_* lst);
void** _lst_raw(struct _plst_* lst);
int _lst_empty(struct _plst_* lst);

#endif
