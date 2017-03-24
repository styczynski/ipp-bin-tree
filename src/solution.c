/*
*  Wrapper for <parser.h>
*  Usage:
*    run solution [-v]
*
*  Application will execute <parser.h> command on an empty
*  incremental tree.
*
*  -v flag in CL options enables verbose mode
*  and logging number of tree's nodes to stderr.
*
*  MIT LICENSE
*  @Piotr Styczyński 2017
*/
#include "incremental_tree.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>


int main(int argc, char **argv) {

    /*  Parse CL arguments */
    int i;
    int vmode = 0;
    for(i = 1; i < argc; i++) {
      if(strcmp(argv[i], "-v") == 0) {
        vmode = 1;
      } else {
        printf("ERROR");
        return 1;
      }
    }

    /* Setup and run parser in continous loop */
    incrTree t = IncrTrees.new();
    while(TreeInParser.readAndParse(t, vmode)) {};


    return 0;
}
