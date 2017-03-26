/*
*  Tree structure implementation based on bidirectional lists (C99 standard)
*  Usage:
*     #include <tree.h>
*      ...
*     tree l = Trees.new();
*
*  All interface sould be accessed through Trees constant.
*
*  MIT LICENSE
*  @Piotr Styczyński 2017
*/
#include "list.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef XTREE_TREE_H__
#define XTREE_TREE_H__

/*
* Implementation data types declarations.
*/
typedef struct treeNodeValue treeNodeValue;
typedef struct treeRoot treeRoot;
typedef treeRoot* tree;
typedef listNode treeNode;
typedef struct trees trees;

/*
* Interface of trees
*/
struct trees {
  /*
  * Create new tree with -1 root element.
  * All trees must be then freed with Trees.free(tree);
  *
  */
  tree (*new)( );

  /*
  * Destroy given tree freeing up memory.
  */
  void (*free)( tree t );

  /*
  * Add new node <child> as the child of already
  * existing node <parent>
  */
  void (*addNode)( tree t, int parent, int child );

  /*
  * Remove node with given number.
  * All tree numbers must be non-negative.
  */
  void (*removeNode)( tree t, int node );

  /*
  * Get rightmost direct child of a given node.
  * All tree numbers must be non-negative.
  */
  int (*getRightmostChild)( tree t, int );

  /*
  * Print tree representation to stdout.
  */
  void (*printTree)( tree t );

  /*
  * Split tree node.
  * Splitting means that all right neighbours of <splitter>
  * are now a children of new <node> node added on the right
  * side of <spitter>
  * All tree numbers must be non-negative.
  */
  void (*splitNode)( tree t, int parent, int splitter, int node);

  /*
  * Removes <node> and all its children recursively.
  */
  void (*deleteSubtree)( tree t, int node );

  /*
  * Obtains the number of nodes in a tree.
  *
  * NOTICE: Works in O(1) time and memory.
  */
  int (*size)( tree t );
};

/*
*  Tree interface accessor object
*/
const trees Trees;

#endif
