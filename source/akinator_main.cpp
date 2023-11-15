#include  <stdio.h>

#include "../trees/source/trees.h"
#include "akinator.h"

int main()
{
    printf("## This program guesses objects based on their features\n");
    printf("## It can also make a definition of object or compare two objects\n\n");

    Node *root = readTree(dataBaseName);
    if (!root) { perror("dataBase"); return 0; }

    Tree objectTree = {};
    treeCtor(&objectTree, root);

    runAkinator(&objectTree);

    treeDtor(objectTree.root);

    printf("\n## Hope to see you soon!\n");
}
