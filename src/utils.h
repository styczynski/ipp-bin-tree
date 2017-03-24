/*
*  Various utilities. (C99 standard)
*
*  MIT LICENSE
*  @Piotr Styczyński 2017
*/
#ifndef XTREE_UTILS_H__
#define XTREE_UTILS_H__

/*
* Debug symbol definitions
*
* Use DEBUG 0 to disable debug macro DBG
* Use DEBUG 1 to enable debug macro DBG
*/
#define DEBUG 0
#define DBG if(DEBUG)

/*
* Print debug info to stdio.
* Works as printf(format + format_prepend, ...)
* Use as printf:
*    debugInfo("%d", ", %d", 42, 42); // -> Output: 42, 42
*
*/
void debugInfo(const char* format, const char* format_prepend, ...);

#endif
