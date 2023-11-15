#ifndef  __TREE_GRAPHIC_DUMP__
#define  __TREE_GRAPHIC_DUMP__

#include <stddef.h>
#include "trees.h"

int treeGraphicDump   (Tree *tree);
int writeTreeToDotFile(Tree *tree, FILE *f);

int dotWriteNodes(Node *node, FILE *f, int  rank);
int dotWriteEdges(Node *node, FILE *f);

#endif //__TREE_GRAPHIC_DUMP__
