#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "iterator.h"
#include "list.h"

const lists Lists = {
  .new = newList,
  .free = freeList,
  .pushFront = pushFrontList,
  .pushBack = pushBackList,
  .popFront = popFrontList,
  .popBack = popBackList,
  .clear = clearList,
  .first = getFirstListElement,
  .last = getLastListElement,
  .size = getListSize,
  .empty = isListEmpty,
  .copy = copyList,
  .copyInto = copyListInto,
  .iterate = iterateList,
  .print = printList,
  .println = printlnList,
  .begin = getListBegin,
  .end = getListEnd,
  .detachElement = detachListElement,
  .newDetachedElement = newListDetachedElement,
  .isSideElement = isListSideElement,
  .insertListAt = insertListAt,
  .isListEnd = isListRightSideEnd,
  .isListBegin = isListLeftSideEnd,
  .splitList = splitList
};

const listNode nullListNode = {
  .right = NULL,
  .left = NULL
};

const listRoot nullListRoot = {
  .begin = NULL,
  .end = NULL
};

listNode* makeListNode(listNode* left, void* value, listNode* right) {
  listNode* l = malloc(sizeof(nullListNode));
  l->right = right;
  l->left = left;
  l->value = value;
  return l;
}

list newList() {
  list l = malloc(sizeof(nullListRoot));
  l->begin = NULL;
  l->end = NULL;
  return l;
}

void freeListRecLeft(listNode* l) {
  if(l == NULL) return;
  //if((*l) == NULL) return;
  if(l->left != NULL) {
    freeListRecLeft(l->left);
  }
  free(l);
  //(*l) = NULL;
}

listNode* pushFrontList(list l, void* value) {
  if(l == NULL) {
    return NULL;
  } else {
    listNode* new_node = makeListNode(NULL, value, l->begin);
    if(l->begin != NULL) {
      (l->begin)->left = new_node;
    }
    (l->begin) = new_node;
    if(l->end == NULL) {
      (l->end) = new_node;
    }
    return new_node;
  }
}

listNode* pushBackList(list l, void* value) {
  if(l == NULL) {
    return NULL;
  } else {
    listNode* new_node = makeListNode(l->end, value, NULL);
    if(l->end != NULL) {
      (l->end)->right = new_node;
    }
    (l->end) = new_node;
    if(l->begin == NULL) {
      (l->begin) = new_node;
    }
    return new_node;
  }
}

void popFrontList(list l) {
  if(l == NULL) {
    return;
  } else if (l->begin == NULL) {
    return;
  } else {
    listNode* new_begin = (l->begin)->right;
    if(new_begin != NULL) {
      new_begin->left = NULL;
    } else {
      (l->end) = NULL;
    }
    free(l->begin);
    (l->begin) = new_begin;
  }
}

void popBackList(list l) {
  if(l == NULL) {
    return;
  } else if (l->end == NULL) {
    return;
  } else {
    listNode* new_end = (l->end)->left;
    if(new_end != NULL) {
      new_end->right = NULL;
    } else {
      (l->begin) = NULL;
    }
    free(l->end);
    (l->end) = new_end;
  }
}

void clearList(list l) {
  if(l == NULL) return;
  if(l->end != NULL) {
    freeListRecLeft(l->end);
  }
  (l->begin)=NULL;
  (l->end)=NULL;
}

void freeList(list l) {
  if(l == NULL) return;
  //clearList(l);
  listNode* it = l->begin;
  while(it != NULL) {
    listNode* next = it->right;
    free(it);
    it = next;
  }

  free(l);
}

void* getFirstListElement(list l) {
  if(l == NULL) {
    return NULL;
  }
  if(l->begin == NULL) {
    return NULL;
  }
  if(l->begin != NULL) return (l->begin)->value;
  return NULL;
}

void* getLastListElement(list l) {
  if(l == NULL) {
    return NULL;
  }
  if(l->end == NULL) {
    return NULL;
  }
  if(l->end != NULL) return (l->end)->value;
  return NULL;
}

int getListSize(list l) {
  if(l == NULL) return 0;
  int size = 0;
  loop_list(l) {
    ++size;
  }
  return size;
}

int isListEmpty( list l ) {
  if(l == NULL) return 1;
  return (getListSize(l) == 0);
}

void copyListInto( list src, list tgt ) {
  if(src == NULL) return;
  listNode* it = src->begin;
  while(it != src->end) {
    if(it!=NULL) {
      pushBackList(tgt, it->value);
    }
    ++it;
  }
}

list copyList( list l ) {
  if(l == NULL) return NULL;
  list ret = newList();
  copyListInto(l, ret);
  return ret;
}

void iterateListNodes( listNode* l, listIteratorFn iterator ) {
  if(l==NULL) return;
  iterator(l->value);
  iterateListNodes(l->right, iterator);
}

void iterateList(list l, listIteratorFn iterator) {
  if(l == NULL) return;
  if(l->begin == NULL) return;
  iterateListNodes(l->begin, iterator);
}

void printListNodes(listNode* l) {
  if(l==NULL) return;
  printf("%p; ", (void*)(l));
  printListNodes(l->right);
}

void printList(list l) {
  printf("[ ");
  printListNodes(l->begin);
  printf("] ");
}

void printlnList(list l) {
  printList(l);
  printf("\n");
}

listNode* getListBegin( list l ) {
  if(l == NULL) return NULL;
  return l->begin;
}

listNode* getListEnd( list l ) {
  if(l == NULL) return NULL;
  return l->end;
}

void detachListElement( list l, listNode* node ) {
  if(node == NULL) return;

  listNode* left_neighbour = node->left;
  listNode* right_neighbour = node->right;

  DBG printf("Detach %p from %p [left=%p right=%p]\n", node, l, left_neighbour, right_neighbour);fflush(stdout);

  if(left_neighbour != NULL) {
    left_neighbour->right = right_neighbour;
  } else {
    l->begin = right_neighbour;
  }
  if(right_neighbour != NULL) {
    right_neighbour->left = left_neighbour;
  } else {
    l->end = left_neighbour;
  }
  DBG printf("Detach.free()\n");fflush(stdout);
  free(node);
  DBG printf("Detach.done()\n");fflush(stdout);
}

listNode* newListDetachedElement() {
  listNode* ret = malloc(sizeof(nullListNode));
  ret->left = NULL;
  ret->right = NULL;
  ret->value = NULL;
  return ret;
}

int isListSideElement( listNode* node ) {
  DBG printf("Check sideness := %p ...\n", node);fflush(stdout);
  if(node == NULL) return 0;
  DBG printf("Check sideness := %p {left=%p right=%p}\n", node, node->left, node->right);fflush(stdout);
  return ( (node->left == NULL) || (node->right == NULL) );
}

int isListLeftSideEnd( listNode* node ) {
  if(node == NULL) return 0;
  return (node->left == NULL);
}

int isListRightSideEnd( listNode* node ) {
  if(node == NULL) return 0;
  return (node->right == NULL);
}

//Append list to the left of element
void insertListAt( list tgt, listNode* node, list src ) {
  if(node == NULL) return;
  if(src == NULL) return;
  if((src->begin == NULL) || (src->end == NULL)) return;
  if(node->left == NULL) {
    tgt->begin = src->begin;

    src->end->right = node;
    node->left = src->end;

    src->begin = NULL;
    src->end = NULL;
    freeList(src);
    return;
  } else if(node->right == NULL) {
    //tgt->end = node;
    //node->left->right = src->begin;
    //node->left = src->end;
    //src->end->right = node;

    node->left->right = src->begin;
    src->begin->left = node->left;
    node->left = src->end;
    src->end->right = node;

    src->begin = NULL;
    src->end = NULL;
    freeList(src);
    return;
  } else {
    node->left->right = src->begin;
    src->begin->left = node->left;
    node->left = src->end;
    src->end->right = node;
    //freeListRecLeft(&node);

    src->begin = NULL;
    src->end = NULL;
    freeList(src);
    return;
  }
}

list splitList( list src, listNode* splitter ) {
  list ret = newList();
  if(splitter == NULL) {
    return ret;
  }

  listNode* realEnd = src->end;
  src->end = splitter;

  if(splitter->right != NULL) {
    ret->begin = splitter->right;
    ret->end = realEnd;
  }
  return ret;
}
