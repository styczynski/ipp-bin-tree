/*
*  Bidirectional list implementation (C99 standard)
*  Usage:
*     #include <list.h>
*      ...
*     list l = Lists.new();
*
*  All interface sould be accessed through Lists constant.
*
*  MIT LICENSE
*  @Piotr Styczyński 2017
*/
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "list.h"


/*
* Structure representing one element of list
* It's got two neighbours (may be NULL)
* Element also contains void* pointer to the actual data.
*/
struct listNode {
  listNode* right;
  void* value;
  listNode* left;
};

/*
* Root element of the list containing pointers
* to the two ends of a list
*/
struct listRoot {
  listNode* begin;
  listNode* end;
};

/*
* Null/empty objects - used for memory allocation
*/
const listNode nullListNode = {
  .right = NULL,
  .left = NULL
};

const listRoot nullListRoot = {
  .begin = NULL,
  .end = NULL
};

/*
* Makes new list from given values
*/
listNode* makeListNode(listNode* left, void* value, listNode* right) {
  listNode* l = malloc(sizeof(nullListNode));
  l->right = right;
  l->left = left;
  l->value = value;
  return l;
}

/*
* Allocate new list
*/
list newList() {
  list l = malloc(sizeof(nullListRoot));
  l->begin = NULL;
  l->end = NULL;
  return l;
}

/*
* Null/empty objects - used for memory allocation
*/
void freeListRecLeft(listNode* l) {
  if(l == NULL) return;
  if(l->left != NULL) {
    freeListRecLeft(l->left);
  }
  free(l);
}

/*
* Push element to the front of the given list
*/
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

/*
* Push element to the end of the given list
*/
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

/*
* Remove the first element of the given list
*/
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

/*
* Remove the last element of the given list
*/
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

/*
* Remove all elements of the given list
*/
void clearList(list l) {
  if(l == NULL) return;
  if(l->end != NULL) {
    freeListRecLeft(l->end);
  }
  (l->begin)=NULL;
  (l->end)=NULL;
}

/*
* Deallocate list
*/
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

/*
* Get first element data pointer or NULL if the list is empty
*/
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

/*
* Get lst element data pointer or NULL if the list is empty
*/
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

/*
* Measure list size in O(n) time
*/
int getListSize(list l) {
  if(l == NULL) return 0;
  int size = 0;
  loop_list(l, it) {
    ++size;
  }
  return size;
}

/*
* Check if list is empty
*/
int isListEmpty( list l ) {
  if(l == NULL) return 1;
  return (l->begin == NULL && l->end == NULL);
}

/*
* Add all elements of <src> to the <tgt>
*/
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

/*
* Make a copy of a list
*/
list copyList( list l ) {
  if(l == NULL) return NULL;
  list ret = newList();
  copyListInto(l, ret);
  return ret;
}

/*
* Iterate (void*)->void function from node <l> to its right
*/
void iterateListNodes( listNode* l, listIteratorFn iterator ) {
  if(l==NULL) return;
  iterator(l->value);
  iterateListNodes(l->right, iterator);
}

/*
* Iterate (void*)->void function through the given list
*/
void iterateList(list l, listIteratorFn iterator) {
  if(l == NULL) return;
  if(l->begin == NULL) return;
  iterateListNodes(l->begin, iterator);
}

/*
* Print list nodes starting at <l> and going right
*/
void printListNodes(listNode* l) {
  if(l==NULL) return;
  printf("%p; ", (void*)(l));
  printListNodes(l->right);
}

/*
* Print list nodes of a given list
*/
void printList(list l) {
  printf("[ ");
  printListNodes(l->begin);
  printf("] ");
}

/*
* Print list nodes of a given list with trailing newline
*/
void printlnList(list l) {
  printList(l);
  printf("\n");
}

/*
* Obtain first list element
*/
listNode* getListBegin( list l ) {
  if(l == NULL) return NULL;
  return l->begin;
}

/*
* Obtain last list element
*/
listNode* getListEnd( list l ) {
  if(l == NULL) return NULL;
  return l->end;
}

/*
* Remove given element from the list
*/
void detachListElement( list l, listNode* node ) {
  if(node == NULL) return;

  listNode* left_neighbour = node->left;
  listNode* right_neighbour = node->right;

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
  free(node);
}

/*
* Create new element container not attached to any list.
*/
listNode* newListDetachedElement() {
  listNode* ret = malloc(sizeof(nullListNode));
  ret->left = NULL;
  ret->right = NULL;
  ret->value = NULL;
  return ret;
}

/*
* Check if is first/last element
*/
int isListSideElement( listNode* node ) {
  if(node == NULL) return 0;
  return ( (node->left == NULL) || (node->right == NULL) );
}

/*
* Check if is first element
*/
int isListLeftSideEnd( listNode* node ) {
  if(node == NULL) return 0;
  return (node->left == NULL);
}

/*
* Check if is last element
*/
int isListRightSideEnd( listNode* node ) {
  if(node == NULL) return 0;
  return (node->right == NULL);
}

/*
* Append list <src> to the left of <node> in list <tgt>
* leaving <src> empty.
* Tgt parameter MUST BE NON-NULL only if <node> is first/last element.
* Otherwise it may be NULL
*/
void insertListAt( list tgt, listNode* node, list src ) {
  if(node == NULL) return;
  if(src == NULL) return;
  if((src->begin == NULL) || (src->end == NULL)) {
    return;
  }
  if(node->left == NULL) {
    tgt->begin = src->begin;
    src->end->right = node;
    node->left = src->end;

    src->begin = NULL;
    src->end = NULL;
    return;
  } else if(node->right == NULL) {
    node->left->right = src->begin;
    src->begin->left = node->left;
    node->left = src->end;
    src->end->right = node;

    src->begin = NULL;
    src->end = NULL;
    return;
  } else {
    node->left->right = src->begin;
    src->begin->left = node->left;
    node->left = src->end;
    src->end->right = node;

    src->begin = NULL;
    src->end = NULL;
    return;
  }
}

/*
* Transfer all right-side neighbours of <splitter> to a new list.
* Return that new list.
*/
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
    splitter->right = NULL;
    ret->begin->left = NULL;
  }
  return ret;
}

/*
* Get next element on the list.
* Returns NULL if node is the last element.
*/
listNode* listNext( listNode* node ) {
  if(node==NULL) return NULL;
  return node->right;
}

/*
* Get previous element on the list.
* Returns NULL if node is the last element.
*/
listNode* listPrevious( listNode* node ) {
  if(node==NULL) return NULL;
  return node->left;
}

/*
* Get value of the list element. Returns void pointer to underlying data.
* Returns NULL if node is NULL.
*/
void* listGetValue( listNode* node ) {
  if(node==NULL) return NULL;
  return node->value;
}

/*
* Sets value of the list element.
* Does nothing if element is NULL.
*/
void listSetValue( listNode* node, void* value ) {
  if(node==NULL) return;
  node->value = value;
}

/*
* Lists interface
*/
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
  .splitList = splitList,
  .next = listNext,
  .previous = listPrevious,
  .getValue = listGetValue,
  .setValue = listSetValue
};
