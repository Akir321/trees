#include <stdio.h>
#include <string.h>

#include "trees.h"
#include "tree_graphic_dump.h"

const char * const fileName = "printed_tree.txt";


int main()
{
    Node *node15 = createNode(strdup("hi"), NULL, NULL);
    Node *node20 = createNode(strdup("hegdehog"), NULL, NULL);
    Node *node17 = createNode(strdup("well"), node15, node20);
    Node *node5  = createNode(strdup("i'm very tired"),  NULL, NULL);
    Node *node10 = createNode(strdup("help me"), node5, node17);

    Tree tree = {};
    treeCtor(&tree, node10);
    treeGraphicDump(&tree);

    sortTreeAdd(&tree, strdup("where are you?"));
    treeGraphicDump(&tree);

    sortTreeAdd(&tree, strdup("hello"));
    treeGraphicDump(&tree);

    printTreePrefix (tree.root, stdout);
    putchar('\n');
    printTreeInfix  (tree.root, stdout);
    putchar('\n');
    printTreePostfix(tree.root, stdout);
    putchar('\n');

    FILE *f = fopen(fileName, "w");
    printTreePrefix(tree.root, f);
    fclose(f);

    Tree tree1 = {};
    treeCtor(&tree1, readTree(fileName));
    treeGraphicDump(&tree1);

    printTreePrefix(tree1.root, stdout);
    putchar('\n');
    printTreePrefix(tree.root, stdout);


    treeDtor(tree.root);
    treeDtor(tree1.root);
}



/*
int main()
{
    Node *node15 = createNode(15, NULL, NULL);
    Node *node20 = createNode(20, NULL, NULL);
    Node *node17 = createNode(17, node15, node20);
    Node *node5  = createNode(5,  NULL, NULL);
    Node *node10 = createNode(10, node5, node17);

    Tree tree = {};
    treeCtor(&tree, node10);
    treeGraphicDump(&tree);

    sortTreeAdd(&tree, 12);
    treeGraphicDump(&tree);

    sortTreeAdd(&tree, 16);
    treeGraphicDump(&tree);

    printTreePrefix (tree.root, stdout);
    putchar('\n');
    printTreeInfix  (tree.root, stdout);
    putchar('\n');
    printTreePostfix(tree.root, stdout);
    putchar('\n');

    FILE *f = fopen(fileName, "w");
    printTreePrefix(tree.root, f);
    fclose(f);

    Tree tree1 = {};
    treeCtor(&tree1, readTree(fileName));
    treeGraphicDump(&tree1);

    printTreePrefix(tree1.root, stdout);
    putchar('\n');
    printTreePrefix(tree.root, stdout);


    treeDtor(tree.root);
    treeDtor(tree1.root);
}
*/
