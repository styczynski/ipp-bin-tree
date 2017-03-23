#include "incremental_tree.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>


int main(int argc, char **argv) {
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

    incrTree t = IncrTrees.new();
    while(treeInReadCommand(t, vmode)) {};


    return 0;
}
