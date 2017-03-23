#include "utils.h"
#include "list.h"
#include "tree.h"
#include "iterator.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

const trees Trees = {
  .new = treeNew,
  .free = treeFree,
  .addNode = treeAddNode,
  .removeNode = treeRemoveNode,
  .getRightmostChild = treeGetRightmostChild,
  .printTree = printTree,
  .splitNode = treeSplitNode,
  .deleteSubtree = treeDeleteSubtree
};

const treeRoot nullTreeRoot = {
  .root = NULL,
  .refTab = NULL,
  .refTabSize = 0
};

const treeNodeValue nullTreeNodeValue = {
  .parent = NULL,
  .children = NULL,
  .number = 0
};

treeNodeValue* treeGetNodeValue(treeNode* node) {
  if(node == NULL) return NULL;
  return (treeNodeValue*)(node->value);
}

treeNode* treeFindNode(tree t, int number) {
  if(t==NULL) return NULL;
  if(number<0) return t->root;
  return (t->refTab)[number];
}

treeNodeValue* treeNewNodeValue(int number) {
  treeNodeValue* ret = malloc(sizeof(nullTreeNodeValue));
  ret->number = number;
  ret->children = Lists.new();
  ret->parent = NULL;
  return ret;
}

treeNode* treeNewNode(tree t, int number) {
  treeNode* node = Lists.newDetachedElement();
  node->value = (void*)treeNewNodeValue(number);
  (t->refTab)[number] = node;
  return node;
}

tree treeNew() {
  tree t = malloc(sizeof(nullTreeRoot));
  t->root = NULL;
  t->refTab = malloc(100*sizeof(int));
  t->refTabSize = 100;
  for(int i=0;i<t->refTabSize;++i) {
    (t->refTab)[i] = NULL;
  }
  t->root = Lists.newDetachedElement();
  t->root->value = (void*)treeNewNodeValue(-1);
  return t;
}

void treeAddNode(tree t, int parent, int child) {
  if(t == NULL) return;
  if(t->root == NULL) {
    t->root = treeNewNode(t, parent);
    (t->refTab)[parent] = t->root;
  } else {
    treeNode* parentNode = treeFindNode(t, parent);
    treeNodeValue* parentNodeValue = treeGetNodeValue(parentNode);
    treeNodeValue* childNodeValue = treeNewNodeValue(child);
    childNodeValue->parent = parentNode;
    treeNode* childNode = (treeNode*) Lists.pushBack(parentNodeValue->children, childNodeValue);
    (t->refTab)[child] = childNode;
    //treeNode* childNode = treeNewNode(t, child);
    //Lists.pushBack(treeGetNodeValue(parentNode)->children, treeGetNodeValue(childNode));
  }
}

int treeGetRightmostChild(tree t, int number) {
  if(t == NULL) return -1;
  treeNode* node = treeFindNode(t, number);
  treeNodeValue* nodeValue = treeGetNodeValue(node);
  if(nodeValue != NULL) {
    treeNodeValue* rightmostChildValue = (treeNodeValue*) Lists.last(nodeValue->children);
    if(rightmostChildValue != NULL) {
      return rightmostChildValue->number;
    }
  }
  return -1;
}

void printTreeNode(treeNode* node, int rlevel, int printToplevelLabel) {
  if(node == NULL) printf("NULL");
  if(printToplevelLabel){
    for(int i=0;i<rlevel;++i) printf("  ");
  }

  treeNodeValue* nodeValue = treeGetNodeValue(node);

  if(!Lists.empty(nodeValue->children)) {
    if(printToplevelLabel){
      printf("Node %d - %p: [%p] <%p> {\n", nodeValue->number, node, nodeValue->children, nodeValue );fflush(stdout);
    }
    loop_list(nodeValue->children) {
      printTreeNode((treeNode*)it, rlevel+1, 1);fflush(stdout);
    }
    if(printToplevelLabel) {
      for(int i=0;i<rlevel;++i) printf("  ");
      printf("}\n");fflush(stdout);
    }
  } else if(printToplevelLabel) {
    printf("Node %d - %p [%p] <%p>\n", nodeValue->number, node, nodeValue->children, nodeValue);fflush(stdout);
  }

}

void printTree(tree t) {
  if(t==NULL) {
    printf("Tree: NULL");
    return;
  }
  treeNodeValue* rootValue = treeGetNodeValue(t->root);
  if(t->root==NULL || rootValue==NULL) {
    printf("Tree: {}");
    return;
  }
  if(Lists.empty(rootValue->children)) {
    printf("Tree: {}");
    return;
  }
  printf("Tree: {\n");fflush(stdout);
  printTreeNode(t->root, 1, 0);
  printf("}\n");
}

void treeUpdateChildrenUpwardRefs(treeNode* node) {
  if(node == NULL) return;
  treeNodeValue* nodeValue = treeGetNodeValue(node);
  if(nodeValue == NULL) return;
  treeNodeValue* firstChildValue = (treeNodeValue*) Lists.first(nodeValue->children);
  treeNodeValue* lastChildValue = (treeNodeValue*) Lists.last(nodeValue->children);
  if(firstChildValue != NULL) firstChildValue->parent = node;
  if(lastChildValue != NULL) lastChildValue->parent = node;
}

void treeRemoveNode(tree t, int number) {
  if(t == NULL) return;
  if(t->root == NULL) return;

  treeNode* node = treeFindNode(t, number);

  if(node == t->root) {
    return;
  } else {
    treeNodeValue* nodeValue = treeGetNodeValue(node);
    if(nodeValue != NULL) {

      if(Lists.isSideElement(node)) {
        treeNode* parentNode = nodeValue->parent;
        treeNodeValue* parentNodeValue = treeGetNodeValue(parentNode);
        DBG printf("removeNode (side)...\n");fflush(stdout);
        if(parentNodeValue != NULL) {
          DBG printf("insertListAt\n");fflush(stdout);
          Lists.insertListAt(parentNodeValue->children, node, nodeValue->children);
          DBG printf("detachElement\n");fflush(stdout);
          Lists.detachElement(parentNodeValue->children, node);
        }
        treeUpdateChildrenUpwardRefs(parentNode);
      } else {
        DBG printf("insertListAt (nonside)\n");fflush(stdout);
        Lists.insertListAt(NULL, node, nodeValue->children);
        DBG printf("detachElement (nonside)\n");fflush(stdout);
        Lists.detachElement(NULL, node);
      }
      DBG printf("Free node value\n");fflush(stdout);
      free(nodeValue);
    }
  }
  DBG printf("Done?\n");fflush(stdout);
  (t->refTab)[number] = NULL;
}

void treeSplitNode(tree t, int parent, int splitNode, int child) {
  treeNode* parentNode = treeFindNode(t, parent);
  treeNode* splitingNode = treeFindNode(t, splitNode);
  treeNodeValue* parentNodeValue = treeGetNodeValue(parentNode);
  list rightChildren = Lists.splitList(parentNodeValue->children, splitingNode);

  treeNodeValue* childNodeValue = treeNewNodeValue(child);
  childNodeValue->parent = parentNode;
  Lists.free(childNodeValue->children);
  childNodeValue->children = rightChildren;
  treeNode* childNode = (treeNode*) Lists.pushBack(parentNodeValue->children, childNodeValue);
  (t->refTab)[child] = childNode;

  treeUpdateChildrenUpwardRefs(childNode);
}

void treeDeleteNodeValueRec(tree t, treeNodeValue* value) {
  if(value == NULL) return;
  loop_list(value->children) {
    treeDeleteNodeValueRec(t, treeGetNodeValue(it));
  }
  Lists.free(value->children);
  free(value);
}

void treeDeleteNodeSubtree(tree t, treeNode* node) {
  if(t == NULL) return;
  if(t->root == NULL) return;

  treeNodeValue* nodeValue = treeGetNodeValue(node);
  if(nodeValue != NULL) {

    if(Lists.isSideElement(node)) {
      treeNode* parentNode = nodeValue->parent;
      treeNodeValue* parentNodeValue = treeGetNodeValue(parentNode);
      DBG printf("removeNode (side)...\n");fflush(stdout);
      if(parentNodeValue != NULL) {
        DBG printf("insertListAt\n");fflush(stdout);
        //Lists.insertListAt(parentNodeValue->children, node, nodeValue->children);
        DBG printf("detachElement\n");fflush(stdout);
        Lists.detachElement(parentNodeValue->children, node);
      }
      treeUpdateChildrenUpwardRefs(parentNode);
    } else {
      DBG printf("insertListAt (nonside)\n");fflush(stdout);
      //Lists.insertListAt(NULL, node, nodeValue->children);
      DBG printf("detachElement (nonside)\n");fflush(stdout);
      Lists.detachElement(NULL, node);
    }
    DBG printf("Free node value\n");fflush(stdout);
    /*loop_list(nodeValue->children) {
      treeNode* child = (treeNode*)it;
      treeDeleteNodeSubtree(t, child);
    }*/
    treeDeleteNodeValueRec(t, nodeValue);
  }
  DBG printf("Done?\n");fflush(stdout);
}


void treeDeleteSubtree(tree t, int number) {
  if(t == NULL) return;
  if(t->root == NULL) return;

  treeNode* node = treeFindNode(t, number);
  treeDeleteNodeSubtree(t, node);
}

void treeFree(tree t) {
  if(t == NULL) return;
  treeDeleteNodeSubtree(t, t->root);
  free(t->root);
  free(t->refTab);
  free(t);
}
