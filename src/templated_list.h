#include "utils.h"

#ifdef XTREE_DECL_LIST_TYPENAME__
#ifdef XTREE_DECL_LIST_TYPE__

#define T_NAME XTREE_DECL_LIST_TYPENAME__
#define T_TYPE XTREE_DECL_LIST_TYPE__
#define T_DEFAULT_VALUE XTREE_DECL_LIST_TYPE_DEFAULT__

typedef struct T_NAME(lists) T_NAME(lists);
typedef struct T_NAME(listNode) T_NAME(listNode);
typedef struct T_NAME(listRoot) T_NAME(listRoot);
typedef T_NAME(listRoot)* T_NAME(list);
typedef void (*T_NAME(listIteratorFn))(T_TYPE);



struct T_NAME(lists) {
  T_NAME(list) (*new)();
  void (*free)(T_NAME(list));
  void (*pushFront)(T_NAME(list), T_TYPE);
  void (*pushBack)(T_NAME(list), T_TYPE);
  void (*popFront)(T_NAME(list));
  void (*popBack)(T_NAME(list));
  void (*clear)(T_NAME(list));
  T_TYPE (*first)(T_NAME(list));
  T_TYPE (*last)(T_NAME(list));
  int (*size)(T_NAME(list));
  int (*empty)(T_NAME(list));
  void (*iterate)(T_NAME(list), T_NAME(listIteratorFn));
  void (*print)(T_NAME(list));
  void (*println)(T_NAME(list));
};

struct T_NAME(listNode) {
  T_NAME(listNode)* right;
  T_TYPE value;
  T_NAME(listNode)* left;
};
struct T_NAME(listRoot) {
  T_NAME(listNode)* begin;
  T_NAME(listNode)* end;
  int size;
};


const struct T_NAME(lists) T_NAME(Lists);
const struct T_NAME(listNode) T_NAME(nullListNode);
const T_NAME(listRoot) T_NAME(nullListRoot);



T_NAME(list) T_NAME(newList)();
void T_NAME(freeList)( T_NAME(list) l );
void T_NAME(freeListRecLeft)( T_NAME(listNode)** l );
void T_NAME(pushFrontList)( T_NAME(list) l, T_TYPE value );
void T_NAME(pushBackList)( T_NAME(list) l, T_TYPE value );
void T_NAME(popFrontList)( T_NAME(list) l );
void T_NAME(popBackList)( T_NAME(list) l );
void T_NAME(clearList)( T_NAME(list) l );
T_TYPE T_NAME(getFirstListElement)( T_NAME(list) l );
T_TYPE T_NAME(getLastListElement)( T_NAME(list) l );
int T_NAME(getListSize)( T_NAME(list) l );
int T_NAME(isListEmpty)( T_NAME(list) l );
T_NAME(listNode)* T_NAME(makeListNode)(T_NAME(listNode)* left, T_TYPE value, T_NAME(listNode)* rights );
void T_NAME(iterateListNodes)( T_NAME(listNode)* l, T_NAME(listIteratorFn) iterator );
void T_NAME(iterateList)( T_NAME(list) l, T_NAME(listIteratorFn) iterator );
void T_NAME(printListNodes)( T_NAME(listNode)* l );
void T_NAME(printList)( T_NAME(list) l );
void T_NAME(printlnList)( T_NAME(list) l );


#endif
#endif
