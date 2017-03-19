#include "list.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef XTREE_TREE_H__
#define XTREE_TREE_H__

typedef struct treeNode treeNode;
typedef struct treeRoot treeRoot;
typedef treeRoot* tree;

struct treeNode {
  int number;
  listGeneric children;
};

struct treeRoot {
  treeNode* root;
  treeNode** refTab;
  int refTabSize;
};

const treeNode nullTreeNode;
const treeRoot nullTreeRoot;

treeNode* treeNewNode(tree t, int number);
treeNode* treeFindNode(tree t, int number);
tree treeNew();
void treeFreeNode(tree t, treeNode** node);
void treeFree(tree t);
void treeAddNode(tree t, int father, int child);
treeNode* treeNodeGetRightmost(treeNode* node);
int treeGetRightmost(tree t, int number);
void printTreeNode(treeNode* node, int rlevel);
void printTree(tree t);

#endif
