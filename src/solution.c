#include "tree.h"
#include <stdio.h>
#include <string.h>

int main(void) {

  tree t = treeNew();
  treeAddNode(t, 0, 0);
  treeAddNode(t, 0, 1);
  treeAddNode(t, 1, 2);
  treeAddNode(t, 0, 3);

  printTree(t);

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
