#include "utils.h"
#include "iterator.h"

#ifndef XTREE_LIST_H__
#define XTREE_LIST_H__

#define loop_list(LIST) \
for(listNode *it = (LIST)->begin; it != NULL; it=(it->right))

typedef struct lists lists;
typedef struct listNode listNode;
typedef struct listRoot listRoot;
typedef listRoot* list;
typedef void (*listIteratorFn)(void*);


struct lists {
  list (*new)();
  void (*free)(list);
  listNode* (*pushFront)(list, void*);
  listNode* (*pushBack)(list, void*);
  void (*popFront)(list);
  void (*popBack)(list);
  void (*clear)(list);
  void* (*first)(list);
  void* (*last)(list);
  int (*size)(list);
  int (*empty)(list);
  list (*copy)(list);
  void (*copyInto)(list, list);
  void (*iterate)(list, listIteratorFn);
  void (*print)(list);
  void (*println)(list);
  listNode* (*begin)(list);
  listNode* (*end)(list);
  void (*detachElement)(list, listNode*);
  listNode* (*newDetachedElement)();
  int (*isSideElement)(listNode*);
  void (*insertListAt)(list, listNode*, list);
  int (*isListEnd)(listNode*);
  int (*isListBegin)(listNode*);
  list (*splitList)(list,listNode*);
};

struct listNode {
  listNode* right;
  void* value;
  listNode* left;
};

struct listRoot {
  listNode* begin;
  listNode* end;
};

const struct lists Lists;
const struct listNode nullListNode;
const listRoot nullListRoot;


list newList();
void freeList( list l );
void freeListRecLeft( listNode* l );
listNode* pushFrontList( list l, void* value );
listNode* pushBackList( list l, void* value );
void popFrontList( list l );
void popBackList( list l );
void clearList( list l );
void* getFirstListElement( list l );
void* getLastListElement( list l );
int getListSize( list l );
int isListEmpty( list l );
list copyList( list l );
void copyListInto( list src, list tgt );
listNode* makeListNode(listNode* left, void* value, listNode* rights );
void iterateListNodes( listNode* l, listIteratorFn iterator );
void iterateList( list l, listIteratorFn iterator );
void printListNodes( listNode* l );
void printList( list l );
void printlnList( list l );
listNode* getListBegin( list l );
listNode* getListEnd( list l );
void detachListElement( list l, listNode* node );
listNode* newListDetachedElement();
int isListSideElement( listNode* node );
int isListLeftSideEnd( listNode* node );
int isListRightSideEnd( listNode* node );
void insertListAt( list tgt, listNode* node, list src );
list splitList( list src, listNode* splitter );

#endif
