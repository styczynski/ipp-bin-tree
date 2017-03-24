/*
*  Incremental tree structure implementation based on bidirectional lists (C99 standard)
*  Incremental tree differs from basic tree that each new node created is one
*  with lastly created node number plus one.
*
*  Usage:
*     #include <incremental_tree.h>
*      ...
*     incrTree l = IncrTrees.new();
*
*  All interface sould be accessed through Trees constant.
*
*  MIT LICENSE
*  @Piotr Styczyński 2017
*/
#ifndef XTREE_INCREMENTAL_TREE_H__
#define XTREE_INCREMENTAL_TREE_H__

#include "tree.h"

/*
* Implementation data types declarations.
*/
typedef struct incrTreeData incrTreeData;
typedef struct incrTrees incrTrees;
typedef incrTreeData* incrTree;

/*
* Structure containing incrTree representation
*/
struct incrTreeData {
  tree t;
  int lastNodeNo;
};

/*
* Interface of incremental trees
*/
struct incrTrees {

  /*
  * Create new tree with 0 node.
  * All trees must be then freed with IncrTrees.free(tree);
  */
  incrTree (*new)( );

  /*
  * Destroy given tree freeing up memory.
  */
  void (*free)( incrTree t );

  /*
  * Add new node as child of <parent> node.
  * New node will have number grater by one from
  * lastly created node
  * (first automatically created at initialization is 1)
  * All tree numbers must be non-negative.
  */
  void (*addNode)( incrTree t, int parent );

  /*
  * Remove node with given number.
  * All tree numbers must be non-negative.
  */
  void (*removeNode)( incrTree t, int node );

  /*
  * Get rightmost direct child of a given node.
  * All tree numbers must be non-negative.
  */
  int (*getRightmostChild)( incrTree t, int node );

  /*
  * Print tree representation to stdout.
  */
  void (*printTree)( incrTree t );

  /*
  * Split tree node.
  * Splitting means that all right neighbours of <splitter>
  * are now a children of new  node added on the right
  * side of <spitter>
  * New node will have number grater by one from
  * lastly created node
  * (first automatically created at initialization is 1)
  * All tree numbers must be non-negative.
  */
  void (*splitNode)( incrTree t, int parent, int splitter );

  /*
  * Removes <node> and all its children recursively.
  */
  void (*deleteSubtree)( incrTree t, int node );

  /*
  * Obtains the number of nodes in a tree.
  *
  * NOTICE: Works in O(1) time and memory.
  */
  int (*size)( incrTree t );

};

/*
*  IncrTree interface accessor object
*/
const incrTrees IncrTrees;

#endif
