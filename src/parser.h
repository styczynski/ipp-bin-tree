#ifndef XTREE_PARSER_H__
#define XTREE_PARSER_H__

#include "incremental_tree.h"
#include <stdarg.h>

#define PARSER_DEBUG DBG debugInfoParser

typedef struct treeInParser treeInParser;

int treeInParse(incrTree t, int vmode, char* command, ...);
void treeInLogDebug(incrTree t);
int treeInReadCommand(incrTree t, int vmode);
void debugInfoParser(const char* command, const char* format, ...);

#endif
