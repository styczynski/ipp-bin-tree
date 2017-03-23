#include "incremental_tree.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>

int main(void) {

  incrTree t = IncrTrees.new();
  while(treeInReadCommand(t)) {};

  /*tree t = treeNew();
  printTree(t);fflush(stdout);
  treeAddNode(t, -1, 0);
  printTree(t);fflush(stdout);
  treeAddNode(t, 0, 1);
  printTree(t);fflush(stdout);
  treeAddNode(t, 1, 2);
  printTree(t);fflush(stdout);
  treeAddNode(t, 0, 3);
  printTree(t);fflush(stdout);
  treeDeleteSubtree(t, 1);
  printTree(t);fflush(stdout);
  //printTree(t);fflush(stdout);
  //treeRemoveNode(t, 0);*/
  //printTree(t);fflush(stdout);

  //treeRemoveNode(t, 2);
  //printTree(t);

  /*char command[30];
  int k, w;
  while (scanf("%s", command) == 1) {
    if(strcmp(command, "ADD_NODE") == 0) {
      scanf("%d", &k);

    } else if(strcmp(command, "RIGHTMOST_CHILD") == 0) {
      scanf("%d", &k);

    } else if(strcmp(command, "DELETE_NODE") == 0) {
      scanf("%d", &k);

    } else if(strcmp(command, "DELETE_SUBTREE") == 0) {
      scanf("%d", &k);

    } else if(strcmp(command, "SPLIT_NODE") == 0) {
      scanf("%d", &k);
      scanf("%d", &w);

    } else {
      printf("[ERR] Unknown command: %s\n", command);
      return 1;
    }
  }*/

  return 0;
}
