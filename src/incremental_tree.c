#include "incremental_tree.h"
#include <stdio.h>

const incrTreeData nullIncrTreeData = {
  .t = NULL,
  .lastNodeNo = 0
};

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

incrTree incrTreeNew() {
  incrTree t = (incrTree)malloc(sizeof(nullIncrTreeData));
  t->t = Trees.new();
  t->lastNodeNo = 0;
  Trees.addNode(t->t, -1, 0);
  return t;
}

void incrTreeFree(incrTree t) {
  if(t==NULL) return;
  Trees.free(t->t);
  free(t);
}

void incrTreeAddNode(incrTree t, int number) {
  if(t==NULL) return;
  (t->lastNodeNo)++;
  Trees.addNode(t->t, number, t->lastNodeNo);
}

void incrTreeRemoveNode(incrTree t, int number) {
  if(t==NULL) return;
  Trees.removeNode(t->t, number);
}

int incrTreeGetRightmostChild(incrTree t, int number) {
  if(t==NULL) return -1;
  return Trees.getRightmostChild(t->t, number);
}

void incrTreePrint(incrTree t) {
  if(t==NULL) return;
  printf("IncrTree[lastNodeNo = %d]: ", t->lastNodeNo);
  Trees.printTree(t->t);
}

void incrTreeSplitNode(incrTree t, int parent, int splitter) {
  if(t==NULL) return;
  (t->lastNodeNo)++;
  Trees.splitNode(t->t, parent, splitter, t->lastNodeNo);
}

void incrTreeDeleteSubtree(incrTree t, int number) {
  if(t==NULL) return;
  Trees.deleteSubtree(t->t, number);
}

int incrTreeGetSize(incrTree t) {
  return Trees.size(t->t);
}
