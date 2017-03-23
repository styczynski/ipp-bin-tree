#ifndef XTREE_INCREMENTAL_TREE_H__
#define XTREE_INCREMENTAL_TREE_H__

#include "tree.h"

typedef struct incrTreeData incrTreeData;
typedef struct incrTrees incrTrees;
typedef incrTreeData* incrTree;

struct incrTreeData {
  tree t;
  int lastNodeNo;
};

struct incrTrees {
  incrTree (*new)();
  void (*free)(incrTree);
  void (*addNode)(incrTree, int);
  void (*removeNode)(incrTree, int);
  int (*getRightmostChild)(incrTree, int);
  void (*printTree)(incrTree);
  void (*splitNode)(incrTree, int, int);
  void (*deleteSubtree)(incrTree, int);
  int (*size)(incrTree);
};

const incrTreeData nullIncrTreeData;
const incrTrees IncrTrees;

incrTree incrTreeNew();
void incrTreeFree(incrTree t);
void incrTreeAddNode(incrTree t, int number);
void incrTreeRemoveNode(incrTree t, int number);
int incrTreeGetRightmostChild(incrTree t, int number);
void incrTreePrint(incrTree t);
void incrTreeSplitNode(incrTree t, int parent, int splitter);
void incrTreeDeleteSubtree(incrTree t, int);
int incrTreeGetSize(incrTree t);


#endif
