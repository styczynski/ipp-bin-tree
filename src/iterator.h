#ifndef XTREE_ITERATOR_H__
#define XTREE_ITERATOR_H__

#include <stdlib.h>

typedef struct iteratorValue iteratorValue;
typedef struct iterators iterators;
typedef iteratorValue* iterator;

struct iteratorValue {
  void* begin;
  void* element;
  void* end;
};

struct iterators {
  int (*next)(iterator);
  iterator (*new)(void* begin, void* end, void* cur);
  void (*free)(iterator);
};

const struct iterators Iterators;
const struct iteratorValue nullIteratorValue;

int iteratorNext(iterator i);
iterator newIterator(void* begin, void* end, void* cur);
void freeIterator(iterator i);

#endif
