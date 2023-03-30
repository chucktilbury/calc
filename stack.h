#ifndef _STACK_H_
#define _STACK_H_

#include "ptrlst.h"

typedef List Stack;

#define createStack()   (Stack)createList()
#define pushStack(s, v) pushList((List)(s), (v))
#define popStack(s)     ((Value*)(popList((List)s)))
#define peekStack(s)    ((Value*)(peekList((List)s)))
#define stackIsEmpty(s) isEmptyList(s)

#endif
