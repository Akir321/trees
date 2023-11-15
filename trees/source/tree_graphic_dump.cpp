#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "tree_graphic_dump.h"
#include "trees.h"

int treeGraphicDump(Tree *tree)
{
    assert(tree);

    static int dumpNumber = 1;

    char *fileName = NULL;
    __mingw_asprintf(&fileName, "gr_dump/tree_dump%d.dot", dumpNumber++);

    FILE *f = fopen(fileName, "w");

    writeTreeToDotFile(tree, f);
    fclose(f);

    char *command = NULL;
    __mingw_asprintf(&command, "dot %s -T png -o %s.png", fileName, fileName);

    system(command);
    free(fileName);
    free(command);

    return 0;
}

#define dotWrite(...) fprintf(f, __VA_ARGS__)

int writeTreeToDotFile(Tree *tree, FILE *f)
{
    assert(tree);
    assert(f);

    dotWrite("digraph\n{\n");
    dotWrite("node [shape = Mrecord, color = \"navy\"];\n\n");

    dotWrite("nodeL [label = \"L\", style = filled, fillcolor = \"cornFlowerBlue\"];\n");
    dotWrite("nodeR [label = \"R\", style = filled, fillcolor = \"salmon\"];\n\n");

    dotWriteNodes(tree->root, f, 0);
    dotWrite("\n");
    dotWriteEdges(tree->root, f);
    dotWrite("}");

    return EXIT_SUCCESS;
}

int dotWriteNodes(Node *node, FILE *f, int rank)
{
    assert(f);
    if (!node) return 0;

    dotWrite("node%p [label = \"" ElemFormat "\", rank = %d];\n", node, node->data, rank);

    dotWriteNodes(node->left,  f, rank + 1);
    dotWriteNodes(node->right, f, rank + 1);

    return EXIT_SUCCESS;
}

int dotWriteEdges(Node *node, FILE *f)
{
    assert(f);
    if (!node) return 0;

    if (node->left)  dotWrite("node%p -> node%p [color = \"cornFlowerBlue\"];\n", node, node->left);
    if (node->right) dotWrite("node%p -> node%p [color = \"salmon\"];\n",         node, node->right);

    dotWriteEdges(node->left,  f);
    dotWriteEdges(node->right, f);

    return 0;
}

#undef dotWrite
