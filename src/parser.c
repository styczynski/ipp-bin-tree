#include "utils.h"
#include "parser.h"
#include <stdarg.h>
#include <string.h>

void debugInfoParser(const char* command, const char* format, ...) {
  va_list arg;
  va_start (arg, format);
  debugInfo(format, " PARSER: COMMAND                                  -> ", arg);
  va_end (arg);
}

void treeInLogDebug(incrTree t) {

}

int treeInParse(incrTree t, char* command, ...) {
  va_list vl;
  va_start(vl, command);
  if(strcmp(command, "ADD_NODE") == 0) {
    int k = va_arg(vl, int);
    PARSER_DEBUG (command, "COMMAND PARSE_ARGS: %d", k);
    IncrTrees.addNode(t, k);
    #ifdef DEBUG
      printf("OK\n");
    #else
      PARSER_DEBUG (command, "RESULT -> OK");
    #endif
  } else if(strcmp(command, "RIGHTMOST_CHILD") == 0) {
    int k = va_arg(vl, int);
    PARSER_DEBUG (command, "COMMAND PARSE_ARGS: %d", k);
    #ifdef DEBUG
      printf("%d\n", IncrTrees.getRightmostChild(t, k));
    #else
      PARSER_DEBUG (command, "RESULT -> %d", IncrTrees.getRightmostChild(t, k));
    #endif
  } else if(strcmp(command, "DELETE_NODE") == 0) {
    int k = va_arg(vl, int);
    PARSER_DEBUG (command, "COMMAND PARSE_ARGS: %d", k);
    IncrTrees.removeNode(t, k);
    #ifdef DEBUG
      printf("OK\n");
    #else
      PARSER_DEBUG (command, "RESULT -> OK");
    #endif
  } else if(strcmp(command, "DELETE_SUBTREE") == 0) {
    int k = va_arg(vl, int);
    PARSER_DEBUG (command, "COMMAND PARSE_ARGS: %d", k);
    IncrTrees.deleteSubtree(t, k);
    #ifdef DEBUG
      printf("OK\n");
    #else
      PARSER_DEBUG (command, "RESULT -> OK");
    #endif
  } else if(strcmp(command, "SPLIT_NODE") == 0) {
    int k = va_arg(vl, int);
    int w = va_arg(vl, int);
    PARSER_DEBUG (command, "COMMAND PARSE_ARGS: %d %d", k, w);
    IncrTrees.splitNode(t, k, w);
    #ifdef DEBUG
      printf("OK\n");
    #else
      PARSER_DEBUG (command, "RESULT -> OK");
    #endif
  } else {
    PARSER_DEBUG (command, "[ERROR] COMMAND ERROR UNKNOWN COMMAND");
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
    if(strcmp(command, "!") == 0) {
      return 0;
    } if(strcmp(command, ".") == 0) {
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
