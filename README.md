# ipp-bin-tree
Written in pure C99
Student's work (individual programistic project) at Warsaw University
Project purpose was to implement a tree-like structure based on bidirectional dynamically allocated lists.

## Building
Clone the repo using `git clone https://github.com/isis97/ipp-bin-tree` 
* Build files using    `make`
* Run tests using      `make test`
* Run distribution executable using `make run`

This project is using general-purpose makefile scripts designed by me.

## Usage
Generated executable (dist/soltuton) contains expression parser (presentation purposes).
The parser allows you to input the given commands:

* `.` - print current tree structure
* `!` - terminate application
* `ADD_NODE <k>` - add new node (next number from prevoiously added) as a child of node #k
* `RIGHTMOST_CHILD <k>` - print rightmost direct child of node #k
* `DELETE_NODE <k>` - delete node #k and transfer its children to its parent
* `DELETE_SUBTREE <k>` - delete node #k and all its children (even indirect)
* `SPLIT_NODE <k> <w>` - (#k must be the parent of #w) create new node to the right of node #w, which will have all nodes to the right of #w as children.

Trees (supports adding nodes labelled with any number)  and IncrTrees (supports incrementive node numbers) support all of this operations.
See .h files for further details.

## Libraries usage
Tree usage example (full documentiation available in .h files):

```c
#include "tree.h"

int main() {                //
  tree t = Trees.new();     // Create new empty tree
                            // It already contains -1 node - root of the tree
                            //
  Trees.addNode(t, -1, 0);  // Adds node #0 to existing root (-1)
  Trees.addNode(t, 0, 1);   // Adds node #1 to node #0
  Trees.addNode(t, 1, 2);   // Adds node #2 to node #1
                            //
  Trees.removeNode(t, 0);   // Remove node #1 and transfer all its children to its parent (node #0)
                            //
  Trees.print(t);           // Print tree structure to stdout
                            //
  Trees.free(t);            // Deallocate tree
  return 0;                 //
}
```

Project contains also data structures like lists:

```c
#include "list.h"

int main() {                //
  list l = Lists.new();     // Create new empty list
                            // 
  int x = 42;               // Set some data to insert to the list.
  int b = 16;               // Note that lists captures only void* pointers to held elements.
  int c = 8;                // You must store them somewhere else
                            // (also free after detaching from list etc.)
                            //
  Lists.pushFront(l, &a);   // Push elements to the front of the list
  Lists.pushFront(l, &b);   //
  Lists.pushFront(l, &c);   //
                            //
  Lists.popBack(t);         // Remove last element
                            //
  Lists.print(t);           // Print list to stdout
                            //
  Lists.free(t);            // Deallocate list
  return 0;                 //
}
```
