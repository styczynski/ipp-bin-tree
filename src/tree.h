#include "list.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef XTREE_TREE_H__
#define XTREE_TREE_H__

#define TREE_REF_TAB_INITIAL_SIZE 107
#define TREE_DEBUG DBG debugInfoTree

typedef struct treeNodeValue treeNodeValue;
typedef struct treeRoot treeRoot;
typedef treeRoot* tree;
typedef listNode treeNode;
typedef struct trees trees;

struct trees {
  tree (*new)();
  void (*free)(tree);
  void (*addNode)(tree, int, int);
  void (*removeNode)(tree, int);
  int (*getRightmostChild)(tree, int);
  void (*printTree)(tree);
  void (*splitNode)(tree, int, int, int);
  void (*deleteSubtree)(tree, int);
  int (*size)(tree);
};

struct treeNodeValue {
  int number;
  list children;
  treeNode* parent;
};

struct treeRoot {
  treeNode* root;
  treeNode** refTab;
  int refTabSize;
  int size;
};

const treeNode* nullTreeNodePtr;
const treeNodeValue nullTreeNodeValue;
const treeRoot nullTreeRoot;
const trees Trees;

treeNodeValue* treeGetNodeValue(treeNode* node);
treeNodeValue* treeNewNodeValue(tree t, int number);
treeNode* treeNewNode(tree t, int number);
treeNode* treeFindNode(tree t, int number);
tree treeNew();
void treeFree(tree t);
void treeAddNode(tree t, int parent, int child);
void treeRemoveNode(tree t, int number);
treeNode* treeNodeGetRightmost(treeNode* node);
int treeGetRightmostChild(tree t, int number);
void printTreeNode(treeNode* node, int rlevel, int printToplevelLabel);
void printTree(tree t);
void treeUpdateChildrenUpwardRefs(treeNode* node);
void treeSplitNode(tree t, int parent, int splitNode, int child);
void treeDeleteSubtree(tree t, int number);
void debugInfoTree(treeNode* node, const char* format, ...);
int treeGetSize(tree t);

#endif
