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

#ifndef XTREE_LIST_H__
#define XTREE_LIST_H__

/*
* Macro for interating through list
* Usage:
*
*   loop_list(list_object, i) {
*         void* element = i->value;
*         printf("void_ptr = %p\n", i);
*    }
*
*/
#define loop_list(LIST, VAR_NAME) \
  for(listNode *VAR_NAME = (LIST)->begin; VAR_NAME != NULL; VAR_NAME=(VAR_NAME->right))

/*
* Declare data types needed for lists implementation
*/
typedef struct lists lists;
typedef struct listNode listNode;
typedef struct listRoot listRoot;

/*
* Actual list - syntax sugar for writing pointers everywhere
*/
typedef listRoot* list;

/*
* Function of type
* void* -> void
* Used as list iterator
*/
typedef void (*listIteratorFn)(void*);

/*
* Interface for lists
*/
struct lists {

  /*
  * Create new list
  * All lists must be then freed with Lists.free(list).
  *
  */
  list (*new)( );

  /*
  * Destroy given list freeing up memory.
  *
  * WARN: Invalidates listNode* pointers
  */
  void (*free)( list );

  /*
  * Push element to the front of a given list.
  * Method returns pointer to the newly created list node.
  *
  * NOTICE: All listNode pointers are valid until used operation does not
  *         keep pointers validity.
  */
  listNode* (*pushFront)( list l, void* element );

  /*
  * Push element to the end of a given list.
  * Method returns pointer to the newly created list node.
  *
  * NOTICE: All listNode pointers are valid until used operation does not
  *         keep pointers validity.
  */
  listNode* (*pushBack)( list l, void* element );

  /*
  * Removes first element of the given list or does nothing if it's empty.
  *
  * WARN: Invalidates listNode* pointers when elment under pointers
  *       will be popped.
  */
  void (*popFront)( list l );

  /*
  * Removes last element of the given list or does nothing if it's empty.
  *
  * WARN: Invalidates listNode* pointers when elment under pointers
  *       will be popped.
  */
  void (*popBack)( list l );

  /*
  * Clears the entire list.
  *
  * WARN: Invalidates listNode* pointers to all elements of list
  */
  void (*clear)( list l );

  /*
  * Obtain first element of the list.
  * Function return void* pointer to the data under first element.
  *
  * If the list is empty NULL is returned.
  */
  void* (*first)( list l );

  /*
  * Obtain last element of the list.
  * Function return void* pointer to the data under first element.
  *
  * If the list is empty NULL is returned.
  */
  void* (*last)( list l );

  /*
  * Obtain the size of a list.
  *
  * WARN: Works in O(n) time where n is the length of the list
  */
  int (*size)( list l );

  /*
  * Check's if list is empty
  */
  int (*empty)( list l );

  /*
  * Copy the list into a new one.
  *
  * WARN: Each element will be a new one, but the data
  *       pointers will be still pointing to the same
  *       memory locations (there're still the same
  *       objects under void* pointers)
  */
  list (*copy)( list l );

  /*
  * Copy the list <source> into other list - <target>
  *
  * WARN: Each element will be a new one, but the data
  *       pointers will be still pointing to the same
  *       memory locations (there're still the same
  *       objects under void* pointers)
  */
  void (*copyInto)( list source, list target );

  /*
  * Iterate through list using given
  * (void*)->void function.
  *
  */
  void (*iterate)( list l, listIteratorFn iterator );

  /*
  * Print given list to stdout.
  * Prints only adresses of values not exact values.
  */
  void (*print)( list );

  /*
  * Print given list to stdout.
  * Prints only adresses of values not exact values.
  * Variant displaying new line at the end of stringified list.
  */
  void (*println)( list l );

  /*
  * Get the first element container pointer.
  * If the list is empty then NULL is returned.
  *
  * NOTICE: All listNode pointers are valid until used operation does not
  *         keep pointers validity.
  */
  listNode* (*begin)( list l );

  /*
  * Get the last element container pointer.
  * If the list is empty then NULL is returned.
  *
  * NOTICE: All listNode pointers are valid until used operation does not
  *         keep pointers validity.
  */
  listNode* (*end)( list l );

  /*
  * Removes element from the list using given container pointer.
  * The list parameter MUST BE NON NULL for nodes that are first or last
  * (isSideElement return true)
  * For all other situations it may be NULL
  *
  * WARN: Invalidates pointers to the removed elements.
  */
  void (*detachElement)( list l, listNode* node );

  /*
  * Create node that is not attached to anything.
  * This functionality may be used in situations when you need
  * lsit nodes outside actual list.
  *
  * NOTICE: All listNode pointers are valid until used operation does not
  *         keep pointers validity.
  */
  listNode* (*newDetachedElement)( );

  /*
  * Checks if given node is the last or first element.
  */
  int (*isSideElement)( listNode* node );

  /*
  * Inserts list <source> to the left side of <node> of list <target>.
  * Note that <target> MUST BE NON-NULL only when the <node> is first/last
  * element of the list (isSideElement return true).
  * For all other situations it may be NULL
  *
  */
  void (*insertListAt)( list target, listNode* node, list source );

  /*
  * Checks if given node is the last element
  */
  int (*isListEnd)(listNode*);

  /*
  * Checks if given node is the first element.
  */
  int (*isListBegin)(listNode*);

  /*
  * All elements on the right side of <node> are transferred to the new list
  * that is returned.
  */
  list (*splitList)( list l, listNode* node );
};

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
* Lists interface object
* All functions should be accessed using Lists object
*/
const struct lists Lists;


#endif
