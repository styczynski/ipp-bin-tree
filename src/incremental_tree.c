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
#include "incremental_tree.h"
#include <stdio.h>

/*
* Null object for memory allocating purposes
*/
const incrTreeData nullIncrTreeData = {
  .t = NULL,
  .lastNodeNo = 0
};

/*
* Create new tree with 0 node.
* All trees must be then freed with IncrTrees.free(tree);
*/
incrTree incrTreeNew() {
  incrTree t = (incrTree)malloc(sizeof(nullIncrTreeData));
  t->t = Trees.new();
  t->lastNodeNo = 0;
  Trees.addNode(t->t, -1, 0);
  return t;
}

/*
* Destroy given tree freeing up memory.
*/
void incrTreeFree(incrTree t) {
  if(t==NULL) return;
  Trees.free(t->t);
  free(t);
}

/*
* Add new node as child of <parent> node.
* New node will have number grater by one from
* lastly created node
* (first automatically created at initialization is 1)
* All tree numbers must be non-negative.
*/
void incrTreeAddNode(incrTree t, int number) {
  if(t==NULL) return;
  (t->lastNodeNo)++;
  Trees.addNode(t->t, number, t->lastNodeNo);
}

/*
* Remove node with given number.
* All tree numbers must be non-negative.
*/
void incrTreeRemoveNode(incrTree t, int number) {
  if(t==NULL) return;
  Trees.removeNode(t->t, number);
}

/*
* Get rightmost direct child of a given node.
* All tree numbers must be non-negative.
*/
int incrTreeGetRightmostChild(incrTree t, int number) {
  if(t==NULL) return -1;
  return Trees.getRightmostChild(t->t, number);
}

/*
* Print tree representation to stdout.
*/
void incrTreePrint(incrTree t) {
  if(t==NULL) return;
  printf("IncrTree[lastNodeNo = %d]: ", t->lastNodeNo);
  Trees.printTree(t->t);
}

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
void incrTreeSplitNode(incrTree t, int parent, int splitter) {
  if(t==NULL) return;
  (t->lastNodeNo)++;
  Trees.splitNode(t->t, parent, splitter, t->lastNodeNo);
}

/*
* Removes <node> and all its children recursively.
*/
void incrTreeDeleteSubtree(incrTree t, int number) {
  if(t==NULL) return;
  Trees.deleteSubtree(t->t, number);
}

/*
* Obtains the number of nodes in a tree.
*
* NOTICE: Works in O(1) time and memory.
*/
int incrTreeGetSize(incrTree t) {
  return Trees.size(t->t);
}

/*
*  IncrTree interface accessor object
*/
const incrTrees IncrTrees = {
  .new = incrTreeNew,
  .free = incrTreeFree,
  .addNode = incrTreeAddNode,
  .removeNode = incrTreeRemoveNode,
  .getRightmostChild = incrTreeGetRightmostChild,
  .printTree = incrTreePrint,
  .splitNode = incrTreeSplitNode,
  .deleteSubtree = incrTreeDeleteSubtree,
  .size = incrTreeGetSize
};
