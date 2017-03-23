#ifndef XTREE_PARSER_H__
#define XTREE_PARSER_H__

#include "incremental_tree.h"
#include <stdarg.h>

typedef struct treeInParser treeInParser;

int treeInParse(incrTree t, char* command, ...);
void treeInLogDebug(incrTree t);
int treeInReadCommand(incrTree t);

#endif
