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
#include "utils.h"
#include "list.h"
#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>

/*
* Initial size of reference table
*/
#define TREE_REF_TAB_INITIAL_SIZE 107

/*
* Define debug symbol
*/
#define TREE_DEBUG DBG debugInfoTree

/*
* Null values used by memory allocation
*/
const treeNode* nullTreeNodePtr = NULL;

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

/*
* Extract value of the node from node pointer.
*/
treeNodeValue* treeGetNodeValue(treeNode* node) {
  if(node == NULL) return NULL;
  return (treeNodeValue*)(node->value);
}

/*
* Used for debbuging purposes
* Use like printf:
*
*   debugInfoTree(node, "formatting d=%d", 42);
*
* NOTICE: This function should NOT BE used directly.
*         To print debug information - macro TREE_DEBUG is used.
*         Works like debugInfoTree:
*         TREE_DEBUG (node, "d = %d", 42);
*
*/
void debugInfoTree(treeNode* node, const char* format, ...) {
  treeNodeValue* value = treeGetNodeValue(node);
  void* children = NULL;
  int id = -1;
  if(value != NULL) {
    children = value->children;
    id = value->number;
  }
  va_list arg;
  va_start (arg, format);
  if(node == NULL) {
    debugInfo(format, "                                                  -> ", id, node, value, children);
  } else {
    debugInfo(format, " NODE:%d  { %p <%p> [%p] } -> ", id, node, value, children);
  }
  va_end (arg);
}

/*
* Obtain node pointer from its number.
*/
treeNode* treeFindNode(tree t, int number) {
  if(t==NULL) return NULL;
  if(number<0) {
    TREE_DEBUG (t->root, " [WARN] ABNORMAL CASE -> FIND NDOE RETURNED ROOT number:%d", number);
  }
  if(number<0) return t->root;
  return (t->refTab)[number];
}

/*
* Save pointer to the node in the reference table.
* This technique is used to provide O(1) access time.
*
* If the reference table is too small it's reallocated
* with new size eual to 1.5 x (current size)
*/
void treePutRef(tree t, int number, treeNode* node) {
  if(t == NULL) return;
  if(t->refTab == NULL) return;
  TREE_DEBUG (node, " PUT REF number: %d", number);

  if(number<0) {
    return;
  }
  /*if(number<0) {
    printf("[ERROR] Tried to access %d index refTab\n", number);
    fflush(stdout);
    return;
  }*/
  if(number>=(t->refTabSize)) {
    const int newSize = (t->refTabSize)*2 - (t->refTabSize)/2;
    t->refTab = realloc(t->refTab, newSize*sizeof(nullTreeNodePtr));
    TREE_DEBUG (node, " RESIZE REF-TAB TO %d (%d B)", newSize, (newSize*sizeof(nullTreeNodePtr)));
    t->refTabSize = newSize;
  }
  (t->refTab)[number] = node;
}

/*
* Create new tree node value object.
* (all values should be paired with corelated treeNodes)
*/
treeNodeValue* treeNewNodeValue(tree t, int number) {
  treeNodeValue* ret = malloc(sizeof(nullTreeNodeValue));
  ret->number = number;
  ret->children = Lists.new();
  ret->parent = NULL;
  (t->size)++;
  return ret;
}

/*
* Create new tree node and fill automatically its value pointer.
*/
treeNode* treeNewNode(tree t, int number) {
  treeNode* node = Lists.newDetachedElement();
  node->value = (void*)treeNewNodeValue(t, number);
  treePutRef(t, number, node);
  return node;
}

/*
* Allocate new tree
*/
tree treeNew() {
  tree t = malloc(sizeof(nullTreeRoot));
  t->root = NULL;
  t->refTab = malloc((TREE_REF_TAB_INITIAL_SIZE)*sizeof(nullTreeNodePtr));
  t->refTabSize = TREE_REF_TAB_INITIAL_SIZE;
  for(int i=0;i<t->refTabSize;++i) {
    (t->refTab)[i] = NULL;
  }
  t->root = Lists.newDetachedElement();
  t->size = 0;
  t->root->value = (void*)treeNewNodeValue(t, -1);
  t->size = 0;
  return t;
}

/*
* Add new node <child> as the child of already
* existing node <parent>
*/
void treeAddNode(tree t, int parent, int child) {
  if(t == NULL) return;
  TREE_DEBUG (NULL, " ADD NODE parent:%d child:%d", parent, child);
  if(t->root == NULL) {
    t->root = treeNewNode(t, parent);
    TREE_DEBUG (t->root, " ADDED NODE -> AS ROOT");
    (t->refTab)[parent] = t->root;
  } else {
    treeNode* parentNode = treeFindNode(t, parent);
    TREE_DEBUG (parentNode, " ADD NODE TO SELF child:%d", child);
    treeNodeValue* parentNodeValue = treeGetNodeValue(parentNode);
    treeNodeValue* childNodeValue = treeNewNodeValue(t, child);
    childNodeValue->parent = parentNode;
    treeNode* childNode = (treeNode*) Lists.pushBack(parentNodeValue->children, childNodeValue);
    treePutRef(t, child, childNode);
    TREE_DEBUG (t->root, " ADDED NODE -> AS NORMAL");
    //treeNode* childNode = treeNewNode(t, child);
    //Lists.pushBack(treeGetNodeValue(parentNode)->children, treeGetNodeValue(childNode));
  }
}

/*
* Get rightmost direct child of a given node.
* All tree numbers must be non-negative.
*/
int treeGetRightmostChild(tree t, int number) {
  if(t == NULL) return -1;
  treeNode* node = treeFindNode(t, number);
  TREE_DEBUG (node, " OBTAIN RIGHTMOST number: %d", number);
  treeNodeValue* nodeValue = treeGetNodeValue(node);
  if(nodeValue != NULL) {
    treeNodeValue* rightmostChildValue = (treeNodeValue*) Lists.last(nodeValue->children);
    TREE_DEBUG (NULL, " OBTAIN RIGHTMOST -> VALUE: %p", rightmostChildValue);
    if(rightmostChildValue != NULL) {
      TREE_DEBUG (NULL, " OBTAIN RIGHTMOST END -> GOT number: %d", rightmostChildValue->number);
      return rightmostChildValue->number;
    }
  }
  TREE_DEBUG (NULL, " OBTAIN RIGHTMOST END -> EXIT(-1)");
  return -1;
}

/*
* Prints tree node representation.
* The information printed to stdout looks like following:
*
* Node node_value - node_pointer [value_pointer] <pointer_to_node_children_list> | <pointer_to_parent> {
*       ... Children nodes information ...
* }
*
* If there's no children curly brackets are removed.
*/
void printTreeNode(treeNode* node, int rlevel, int printToplevelLabel) {
  if(node == NULL) printf("NULL");
  if(printToplevelLabel){
    for(int i=0;i<rlevel;++i) printf("  ");
  }

  treeNodeValue* nodeValue = treeGetNodeValue(node);

  if(!Lists.empty(nodeValue->children)) {
    if(printToplevelLabel){
      printf("Node %d - %p: [%p] <%p> | %p {\n", nodeValue->number, node, nodeValue->children, nodeValue, nodeValue->parent );fflush(stdout);
    }
    loop_list(nodeValue->children, it) {
      printTreeNode((treeNode*)it, rlevel+1, 1);fflush(stdout);
    }
    if(printToplevelLabel) {
      for(int i=0;i<rlevel;++i) printf("  ");
      printf("}\n");fflush(stdout);
    }
  } else if(printToplevelLabel) {
    printf("Node %d - %p [%p] <%p> | %p\n", nodeValue->number, node, nodeValue->children, nodeValue, nodeValue->parent);fflush(stdout);
  }

}

/*
* Prints entire tree to stdout.
*/
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

/*
* Update parent pointer references in children of <node>
* This function should be called each time the children list
* end are changed (remove, swaped, new one created) to ensure
* parent pointers are valid among all tree nodes.
*/
void treeUpdateChildrenUpwardRefs(treeNode* node) {
  TREE_DEBUG (node, " UPDATE REFS");
  if(node == NULL) return;
  treeNodeValue* nodeValue = treeGetNodeValue(node);
  if(nodeValue == NULL) return;
  treeNodeValue* firstChildValue = (treeNodeValue*) Lists.first(nodeValue->children);
  treeNodeValue* lastChildValue = (treeNodeValue*) Lists.last(nodeValue->children);

  TREE_DEBUG (NULL, " UPDATE REFS: LEFT-/RIGHTMOST -> %p / %p ", firstChildValue, lastChildValue);
  if(firstChildValue != NULL) firstChildValue->parent = node;
  if(lastChildValue != NULL) lastChildValue->parent = node;
  TREE_DEBUG (node, " UPDATE REFS DONE");
}

/*
* Remove node with given number.
* All tree numbers must be non-negative.
*/
void treeRemoveNode(tree t, int number) {
  if(t == NULL) return;
  if(t->root == NULL) return;

  treeNode* node = treeFindNode(t, number);

  TREE_DEBUG (node, " REMOVE NODE");
  if(node == t->root) {
    TREE_DEBUG (node, " REMOVE NODE -> EXIT() BECAUSE ROOT");
    return;
  } else {
    treeNodeValue* nodeValue = treeGetNodeValue(node);
    if(nodeValue != NULL) {

      if(Lists.isSideElement(node)) {
        treeNode* parentNode = nodeValue->parent;
        treeNodeValue* parentNodeValue = treeGetNodeValue(parentNode);
        TREE_DEBUG (node, " REMOVE NODE - SIDED branch");
        TREE_DEBUG (node, " REMOVE NODE - PARENT VALUE: %p", parentNodeValue);
        if(parentNodeValue != NULL) {
          TREE_DEBUG (node, " INSERT LIST AT NODE, PARENT.CHILDREN = %p", parentNodeValue->children);
          Lists.insertListAt(parentNodeValue->children, node, nodeValue->children);
          TREE_DEBUG (node, " DETACH ELEMENT AT NODE, PARENT.CHILDREN = %p", parentNodeValue->children);
          Lists.detachElement(parentNodeValue->children, node);
        }
        treeUpdateChildrenUpwardRefs(parentNode);
      } else {
        TREE_DEBUG (node, " REMOVE NODE - NON-SIDED branch");
        TREE_DEBUG (node, " INSERT LIST AT NODE");
        Lists.insertListAt(NULL, node, nodeValue->children);
        TREE_DEBUG (node, "DETACH ELEMENT AT NODE");
        Lists.detachElement(NULL, node);
      }
      TREE_DEBUG (node, " FREE NODE VALUE");
      (t->size)--;
      free(nodeValue);
    }
  }
  TREE_DEBUG (NULL, " DONE REMOVING NODE EXIT()");
  treePutRef(t, number, NULL);
}

/*
* Split tree node.
* Splitting means that all right neighbours of <splitter>
* are now a children of new <node> node added on the right
* side of <spitter>
* All tree numbers must be non-negative.
*/
void treeSplitNode(tree t, int parent, int splitNode, int child) {
  treeNode* parentNode = treeFindNode(t, parent);
  treeNode* splitingNode = treeFindNode(t, splitNode);

  TREE_DEBUG (splitingNode, " SPLIT NODE, PARENT = %p", parentNode);

  treeNodeValue* parentNodeValue = treeGetNodeValue(parentNode);
  list rightChildren = Lists.splitList(parentNodeValue->children, splitingNode);

  TREE_DEBUG (splitingNode, " SPLIT NODE, LIST SPLITTED NOW ADD NEW NODE");
  treeNodeValue* childNodeValue = treeNewNodeValue(t, child);
  childNodeValue->parent = parentNode;
  Lists.free(childNodeValue->children);
  childNodeValue->children = rightChildren;
  treeNode* childNode = (treeNode*) Lists.pushBack(parentNodeValue->children, childNodeValue);
  treePutRef(t, child, childNode);

  TREE_DEBUG (childNode, " SPLIT NODE -> NEW NODE ADDED: THIS ");

  treeUpdateChildrenUpwardRefs(childNode);
  treeUpdateChildrenUpwardRefs(parentNode);
}

/*
* Deallocates value objects for node recursively
*/
void treeDeleteNodeValueRec(tree t, treeNodeValue* value) {
  if(value == NULL) return;
  treePutRef(t, value->number, NULL);
  TREE_DEBUG (NULL, " FREE NODE VALUE -> BEGIN %p", value);
  loop_list(value->children, it) {
    TREE_DEBUG (NULL, " FREE NODE VALUE (RECURSE INTO)----> %p", value);
    treeDeleteNodeValueRec(t, treeGetNodeValue(it));
  }
  TREE_DEBUG (NULL, " FREE NODE VALUE -> DELETE %p", value);
  TREE_DEBUG (NULL, " FREE NODE VALUE -> DELETE CHILDREN LIST %p", value->children);
  Lists.free(value->children);
  TREE_DEBUG (NULL, " FREE NODE VALUE -> DELETE REAL %p", value);
  free(value);
  (t->size)--;
  TREE_DEBUG (NULL, " FREE NODE VALUE END");
}

/*
* Removes <node> and all its children recursively.
*/
void treeDeleteNodeSubtree(tree t, treeNode* node) {
  if(t == NULL) return;
  if(t->root == NULL) return;

  treeNodeValue* nodeValue = treeGetNodeValue(node);
  TREE_DEBUG (node, " REMOVE NODE-SUBTREE");
  if(nodeValue != NULL) {

    if(Lists.isSideElement(node)) {
      treeNode* parentNode = nodeValue->parent;
      treeNodeValue* parentNodeValue = treeGetNodeValue(parentNode);
      TREE_DEBUG (node, " REMOVE NODE-SUBTREE - SIDED branch");
      TREE_DEBUG (node, " REMOVE NOD-SUBTREEE - PARENT VALUE: %p", parentNodeValue);
      if(parentNodeValue != NULL) {
        TREE_DEBUG (node, " DETACH SELF FROM NODE %p <%p> [%p]\n", parentNode, parentNodeValue, parentNodeValue->children);
        Lists.detachElement(parentNodeValue->children, node);
      }
      TREE_DEBUG (node, " REMOVE NODE-SUBTREE - UPDATE REFS");
      treeUpdateChildrenUpwardRefs(parentNode);
    } else {
      TREE_DEBUG (node, " REMOVE NODE-SUBTREE - NON-SIDED branch");
      TREE_DEBUG (node, " INSERT LIST AT NODE");
      //Lists.insertListAt(NULL, node, nodeValue->children);
      TREE_DEBUG (node, "DETACH ELEMENT AT NODE");
      Lists.detachElement(NULL, node);
    }
    TREE_DEBUG (node, " FREE NODE-SUBTREE VALUE");
    /*loop_list(nodeValue->children) {
      treeNode* child = (treeNode*)it;
      treeDeleteNodeSubtree(t, child);
    }*/
    treeDeleteNodeValueRec(t, nodeValue);
  }
  TREE_DEBUG (NULL, " DONE REMOVING NODE-SUBTREE EXIT()");
}

/*
* Removes node and all its children recursively.
*/
void treeDeleteSubtree(tree t, int number) {
  if(t == NULL) return;
  if(t->root == NULL) return;

  treeNode* node = treeFindNode(t, number);
  treeDeleteNodeSubtree(t, node);
}

/*
* Free all memory allocated by tree.
*/
void treeFree(tree t) {
  TREE_DEBUG (NULL, " FREE TREE");
  if(t == NULL) return;
  treeDeleteNodeSubtree(t, t->root);
  //free(t->root);
  free(t->refTab);
  free(t);
}

/*
* Measure number of nodes in a tree.
*
* NOTICE: Works in O(1) time and memory
*/
int treeGetSize(tree t) {
  if(t == NULL) return 0;
  return t->size;
}

/*
* Trees interface
*/
const trees Trees = {
  .new = treeNew,
  .free = treeFree,
  .addNode = treeAddNode,
  .removeNode = treeRemoveNode,
  .getRightmostChild = treeGetRightmostChild,
  .printTree = printTree,
  .splitNode = treeSplitNode,
  .deleteSubtree = treeDeleteSubtree,
  .size = treeGetSize
};
