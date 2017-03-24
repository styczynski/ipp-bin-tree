/*
*  Parser for testing list/trees (C99 standard)
*
*  Parser input command are each in new line.
*  And they can be one of the:
*
*  ADD_NODE <k:node>                        -> Adds new node to tree
*  RIGHTMOST_CHILD <k:node>                 -> Removes given node from tree
*  DELETE_NODE <k:node>                     -> Deletes given node
*  DELETE_SUBTREE <k:node>                  -> Delete recursively given node
*  SPLIT_NODE <parent:int> <splitter:int>   -> Splits node
*
*  For operation details see: <incremental_tree.h>
*
*  MIT LICENSE
*  @Piotr Styczyński 2017
*/
#ifndef XTREE_PARSER_H__
#define XTREE_PARSER_H__

#include "incremental_tree.h"
#include <stdarg.h>

/*
* Define parser debug symbol
*/
#define PARSER_DEBUG DBG debugInfoParser

/*
* Define needed implementation data types
*/
typedef struct treeInParser treeInParser;

/*
* Parser nterface structure
*/
struct treeInParser {
  /*
  * Reads command as specified in parser.h manner from stdin
  * Then executes it for given incremental tree.
  *
  * If vmode is set to 1 then parser works in verbose mode.
  * Then at stderr will be present debug infromation.
  * After each operation the new line (to stderr) will be printed:
  * NODES: <n>
  *
  * Where n is the number of nodes in tree after performed operation.
  */
  int (*readAndParse)( incrTree t, int vmode );
};

/*
* Parser interface object.
*/
const treeInParser TreeInParser;

#endif
