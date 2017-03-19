
#ifdef XTREE_DECL_LIST_TYPENAME__
#ifdef XTREE_DECL_LIST_TYPE__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

const T_NAME(lists) T_NAME(Lists) = {
  .new = T_NAME(newList),
  .free = T_NAME(freeList),
  .pushFront = T_NAME(pushFrontList),
  .pushBack = T_NAME(pushBackList),
  .popFront = T_NAME(popFrontList),
  .popBack = T_NAME(popBackList),
  .clear = T_NAME(clearList),
  .first = T_NAME(getFirstListElement),
  .last = T_NAME(getLastListElement),
  .size = T_NAME(getListSize),
  .empty = T_NAME(isListEmpty),
  .iterate = T_NAME(iterateList),
  .print = T_NAME(printList),
  .println = T_NAME(printlnList)
};

const T_NAME(listNode) T_NAME(nullListNode) = {
  .right = NULL,
  .left = NULL
};

const T_NAME(listRoot) T_NAME(nullListRoot) = {
  .begin = NULL,
  .end = NULL
};

T_NAME(listNode)* T_NAME(makeListNode)(T_NAME(listNode)* left, T_TYPE value, T_NAME(listNode)* right) {
  T_NAME(listNode)* l = malloc(sizeof(T_NAME(nullListNode)));
  l->right = right;
  l->left = left;
  l->value = value;
  return l;
}

T_NAME(list) T_NAME(newList)() {
  T_NAME(list) l = malloc(sizeof(T_NAME(nullListRoot)));
  l->begin = NULL;
  l->end = NULL;
  l->size = 0;
  return l;
}

void T_NAME(freeListRecLeft)(T_NAME(listNode)** l) {
  if(l == NULL) return;
  if((*l) == NULL) return;
  if((*l)->left != NULL) {
    T_NAME(freeListRecLeft)(&((*l)->left));
  }
  free(*l);
  (*l) = NULL;
}

void T_NAME(pushFrontList)(T_NAME(list) l, T_TYPE value) {
  if(l == NULL) {
    return;
  } else {
    (l->size)++;
    T_NAME(listNode)* new_node = T_NAME(makeListNode)(NULL, value, l->begin);
    if(l->begin != NULL) {
      (l->begin)->left = new_node;
    }
    (l->begin) = new_node;
    if(l->end == NULL) {
      (l->end) = new_node;
    }
  }
}

void T_NAME(pushBackList)(T_NAME(list) l, T_TYPE value) {
  if(l == NULL) {
    return;
  } else {
    (l->size)++;
    T_NAME(listNode)* new_node = T_NAME(makeListNode)(l->end, value, NULL);
    if(l->end != NULL) {
      (l->end)->right = new_node;
    }
    (l->end) = new_node;
    if(l->begin == NULL) {
      (l->begin) = new_node;
    }
  }
}

void T_NAME(popFrontList)(T_NAME(list) l) {
  if(l == NULL) {
    return;
  } else if (l->begin == NULL) {
    return;
  } else {
    (l->size)--;
    T_NAME(listNode)* new_begin = (l->begin)->right;
    if(new_begin != NULL) {
      new_begin->left = NULL;
    } else {
      (l->end) = NULL;
    }
    free(l->begin);
    (l->begin) = new_begin;
  }
}

void T_NAME(popBackList)(T_NAME(list) l) {
  if(l == NULL) {
    return;
  } else if (l->end == NULL) {
    return;
  } else {
    (l->size)--;
    T_NAME(listNode)* new_end = (l->end)->left;
    if(new_end != NULL) {
      new_end->right = NULL;
    } else {
      (l->begin) = NULL;
    }
    free(l->end);
    (l->end) = new_end;
  }
}

void T_NAME(clearList)(T_NAME(list) l) {
  if(l == NULL) return;
  if(l->end != NULL) {
    T_NAME(freeListRecLeft)(&(l->end));
  }
  (l->begin)=NULL;
  (l->end)=NULL;
  (l->size)=0;
}

void T_NAME(freeList)(T_NAME(list) l) {
  if(l == NULL) return;
  T_NAME(clearList)(l);
  free(l);
}

T_TYPE T_NAME(getFirstListElement)(T_NAME(list) l) {
  if(l == NULL) {
    perror("Get first element of empty list.");
    #ifdef XTREE_DECL_LIST_TYPE_DEFAULT__
      return T_DEFAULT_VALUE;
    #else
      return;
    #endif
  }
  if(l->begin == NULL) {
    perror("Get first element of empty list.");
    #ifdef XTREE_DECL_LIST_TYPE_DEFAULT__
      return T_DEFAULT_VALUE;
    #else
      return;
    #endif
  }
  if(l->begin != NULL) return (l->begin)->value;
  #ifdef XTREE_DECL_LIST_TYPE_DEFAULT__
    return T_DEFAULT_VALUE;
  #else
    return;
  #endif
}

T_TYPE T_NAME(getLastListElement)(T_NAME(list) l) {
  if(l == NULL) {
    perror("Get first element of empty list.");
    #ifdef XTREE_DECL_LIST_TYPE_DEFAULT__
      return T_DEFAULT_VALUE;
    #else
      return;
    #endif
  }
  if(l->end == NULL) {
    perror("Get first element of empty list.");
    #ifdef XTREE_DECL_LIST_TYPE_DEFAULT__
      return T_DEFAULT_VALUE;
    #else
      return;
    #endif
  }
  if(l->end != NULL) return (l->end)->value;
  #ifdef XTREE_DECL_LIST_TYPE_DEFAULT__
    return T_DEFAULT_VALUE;
  #else
    return;
  #endif
}

int T_NAME(getListSize)(T_NAME(list) l) {
  if(l == NULL) return 0;
  return l->size;
}

int T_NAME(isListEmpty)( T_NAME(list) l ) {
  if(l == NULL) return 1;
  return (l->size == 0);
}

void T_NAME(iterateListNodes)( T_NAME(listNode)* l, T_NAME(listIteratorFn) iterator ) {
  if(l==NULL) return;
  iterator(l->value);
  T_NAME(iterateListNodes)(l->right, iterator);
}

void T_NAME(iterateList)(T_NAME(list) l, T_NAME(listIteratorFn) iterator) {
  if(l == NULL) return;
  if(l->begin == NULL) return;
  T_NAME(iterateListNodes)(l->begin, iterator);
}

void T_NAME(printListNodes)(T_NAME(listNode)* l) {
  if(l==NULL) return;
  #ifdef XTREE_DECL_LIST_TYPE_PRINTF_SIG__
    printf(XTREE_DECL_LIST_TYPE_PRINTF_SIG__, (T_TYPE)(l->value));
  #else
    printf("");
  #endif
  T_NAME(printListNodes)(l->right);
}

void T_NAME(printList)(T_NAME(list) l) {
  printf("[ ");
  T_NAME(printListNodes)(l->begin);
  printf("] ");
}

void T_NAME(printlnList)(T_NAME(list) l) {
  T_NAME(printList)(l);
  printf("\n");
}

#endif
#endif
