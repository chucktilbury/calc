#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "ptrlst.h"

typedef List Queue;

#define createQueue()   (Queue)createList()
#define addQueue(q, v)  addList((List)(q), (void*)(v))
#define getQueue(q, i)  (Value*)getList((List)(q), (i))
#define resetQueue(q)   resetList((List)q)
#define iterateQueue(q) (Value*)iterateList((List)q)

#endif
