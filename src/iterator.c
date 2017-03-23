#include "iterator.h"

const iterators Iterators = {
  .next = iteratorNext,
  .new = newIterator,
  .free = freeIterator
};

const iteratorValue nullIteratorValue = {
  .begin = NULL,
  .end = NULL,
  .element = NULL
};

int iteratorNext(iterator i) {
  if(i == NULL) return 0;
  if(i->element != NULL) {
    if(i->element != i->end) {
      ++(i->element);
      return 1;
    } else {
      return 0;
    }
  }
  return 0;
}

iterator newIterator(void* begin, void* end, void* cur) {
  iterator i = malloc(sizeof(nullIteratorValue));
  i->begin = begin;
  i->end = end;
  i->element = cur;
  return i;
}

void freeIterator(iterator i) {
  if(i == NULL) return;
  free(i);
}
