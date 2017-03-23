#include "parser.h"
#include <stdarg.h>
#include <string.h>

void treeInLogDebug(incrTree t) {

}

int treeInParse(incrTree t, char* command, ...) {
  va_list vl;
  va_start(vl, command);
  fflush(stdout);
  if(strcmp(command, "ADD_NODE") == 0) {
    int k = va_arg(vl, int);
    IncrTrees.addNode(t, k);
    printf("OK\n");
  } else if(strcmp(command, "RIGHTMOST_CHILD") == 0) {
    int k = va_arg(vl, int);
    printf("%d\n", IncrTrees.getRightmostChild(t, k));
  } else if(strcmp(command, "DELETE_NODE") == 0) {
    int k = va_arg(vl, int);
    IncrTrees.removeNode(t, k);
    printf("OK\n");
  } else if(strcmp(command, "DELETE_SUBTREE") == 0) {
    int k = va_arg(vl, int);
    IncrTrees.deleteSubtree(t, k);
    printf("OK\n");
  } else if(strcmp(command, "SPLIT_NODE") == 0) {
    int k = va_arg(vl, int);
    int w = va_arg(vl, int);
    IncrTrees.splitNode(t, k, w);
    printf("OK\n");
  } else {
    printf("[ERR] Unknown command: %s\n", command);
    va_end(vl);
    return 0;
  }
  va_end(vl);
  return 1;
}


int treeInReadCommand(incrTree t) {
  char command[30];
  int k, w;
  int code = scanf("%s", command);
  if (code == 1) {
    if(strcmp(command, ".") == 0) {
      IncrTrees.printTree(t);
    } else if(strcmp(command, "ADD_NODE") == 0) {
      scanf("%d", &k);
      treeInParse(t, command, k);
    } else if(strcmp(command, "RIGHTMOST_CHILD") == 0) {
      scanf("%d", &k);
      treeInParse(t, command, k);
    } else if(strcmp(command, "DELETE_NODE") == 0) {
      scanf("%d", &k);
      treeInParse(t, command, k);
    } else if(strcmp(command, "DELETE_SUBTREE") == 0) {
      scanf("%d", &k);
      treeInParse(t, command, k);
    } else if(strcmp(command, "SPLIT_NODE") == 0) {
      scanf("%d", &k);
      scanf("%d", &w);
      treeInParse(t, command, k, w);
    } else {
      printf("[ERR] Unknown command: %s\n", command);
      return -1;
    }
    return 1;
  }
  return 0;
}
