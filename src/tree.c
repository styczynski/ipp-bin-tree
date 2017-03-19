#include "list.h"
#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

const treeRoot nullTreeRoot = {
  .root = NULL,
  .refTab = NULL,
  .refTabSize = 0
};

treeNode* treeFindNode(tree t, int number) {
  return (t->refTab)[number];
}

treeNode* treeNewNode(tree t, int number) {
  treeNode* node = malloc(sizeof(nullTreeNode));
  node->number = number;
  node->children = ListsGeneric.new();
  (t->refTab)[number] = node;
  return node;
}

tree treeNew() {
  tree t = malloc(sizeof(nullTreeRoot));
  t->root = NULL;
  t->refTab = malloc(100*sizeof(int));
  t->refTabSize = 100;
  return t;
}

void treeFreeNode(tree t, treeNode** node) {
  if(t == NULL) return;
  if(node == NULL) return;
  if((*node) == NULL) return;
  free((t->refTab)[(*node)->number]);
  while(!ListsGeneric.empty((*node)->children)) {
    treeNode* child = (treeNode*)ListsGeneric.last((*node)->children);
    treeNode** childn = &child;
    treeFreeNode(t, childn);
    ListsGeneric.popBack((*node)->children);
  }
  ListsGeneric.free((*node)->children);
  free(*node);
  (*node) = NULL;
}

void treeFree(tree t) {
  if(t == NULL) return;
  treeFreeNode(t, &(t->root));
  free(t->refTab);
  free(t);
}

void treeAddNode(tree t, int father, int child) {
  if(t == NULL) return;
  if(t->root == NULL) {
    t->root = treeNewNode(t, father);
  } else {
    treeNode* childNode = treeNewNode(t, child);
    treeNode* fatherNode = treeFindNode(t, father);
    ListsGeneric.pushBack(fatherNode->children, (void*)childNode);
  }
}

treeNode* treeNodeGetRightmost(treeNode* node) {
  if(node == NULL) return NULL;
  if(ListsGeneric.empty(node->children)) return node;
  return treeNodeGetRightmost( (treeNode*)ListsGeneric.last(node->children) );
}

int treeGetRightmost(tree t, int number) {
  if(t == NULL) return -1;
  if(t->root == NULL) return -1;
  treeNode* startNode = treeFindNode(t, number);
  if(startNode == NULL) return -1;
  treeNode* node = treeNodeGetRightmost(startNode);
  if(node == NULL) return -1;
  return node->number;
}

void printTreeNode(treeNode* node, int rlevel) {
  if(node == NULL) return;
  for(int i=0;i<rlevel;++i) printf("  ");

  if(!ListsGeneric.empty(node->children)) {
    printf("Node %d: {\n", node->number);
    listGeneric temp = ListsGeneric.new();
    while(!ListsGeneric.empty(node->children)) {
      treeNode* child = (treeNode*)ListsGeneric.first(node->children);
      printTreeNode(child, rlevel+1);
      ListsGeneric.pushBack(temp, (void*)child);
      ListsGeneric.popFront(node->children);
    }
    ListsGeneric.free(node->children);
    node->children = temp;
    for(int i=0;i<rlevel;++i) printf("  ");
    printf("}\n");
  } else {
    printf("Node %d\n", node->number);
  }

}

void printTree(tree t) {
  if(t==NULL) {
    printf("Tree: NULL");
    return;
  }
  if(t->root==NULL) {
    printf("Tree: {}");
    return;
  }
  printf("Tree: {\n");
  printTreeNode(t->root, 1);
  printf("}\n");
}
