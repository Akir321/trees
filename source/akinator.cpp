#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../trees/source/trees.h"
#include "../trees/source/tree_graphic_dump.h"
#include "akinator.h"



int runAkinator(Tree *objectTree)
{
    assert(objectTree);

    int command = 0;

    while (command != 's' && command != 'w')
    {
        command = getAkinatorCommand();
        processAkinatorCommand(objectTree, command);
    }

    return EXIT_SUCCESS;
}

int getAkinatorCommand()
{
    printf("What do you want to do?\n\n");

    bool gotCommand = false;
    char command     = 0;

    do 
    {
        printf("The program can [g]uess an object, make a [d]efinition of one object,\n");
        printf("[c]ompare two objects, show a picture of the [o]bject tree,\n\n");
        printf("You can also exit with [s]ave or exit [w]ithout save.\n\n");

        if (scanf("%c", &command) == 1)
        {
            gotCommand = command == GUESS     || command == DEFINITION   || command == COMPARE ||
                         command == EXIT_SAVE || command == EXIT_NO_SAVE || command == GRAPHIC_DUMP;

        }

        if (!gotCommand)
        {
            printf("A wrong command is typed.\n\n");
        }
    } 
    while (!gotCommand);

    return command;
}

int processAkinatorCommand(Tree *objectTree, int command)
{
    assert(objectTree);

    switch(command)
    {
        case GUESS:
            return commandAkinatorGuess(objectTree);
        
        case EXIT_SAVE:
        {
            FILE *f = fopen(dataBaseName, "w");
            printTreePrefix(objectTree->root, f);
            fclose(f);

            printf("DataBase successfully saved\n");
            return EXIT_SUCCESS;
        }

        case EXIT_NO_SAVE:
            return EXIT_SUCCESS;

        default:
            printf("ERROR: unknown command %c\n", command);
            return EXIT_FAILURE;
        
    }
}

int commandAkinatorGuess(Tree *objectTree)
{
    printf("Answer some questions about your object:\n");

    Node *prevPrev = NULL;
    Node *prev     = NULL;
    Node *current  = objectTree->root;
    int  answer    = 0;

    while (current != NULL)
    {
        prevPrev = prev;
        prev     = current;
        printf("It (she/he) %s? [y/n]\n", current->data);
        while (answer != 'y' && answer != 'n') { answer = getchar(); }
        bufClear();
    
        if (answer == 'y') current = current->left;
        else               current = current->right;
    }

    if (answer == 'y')
    {
        printf("I knew it! Artificial intelligence is a lot smarter than humankind!\n");
    }
    else
    {
        char word[WordLength] = {};

        printf("So then I'm wrong. But what was it?\n");
        scanf("%255[^\n]", word);
        bufClear();
        printf("object = %s\n", word);

        Node *objectNode = createNode(strdup(word), NULL, NULL);
        printNode(objectNode, stdout);

        printf("How is it different from %s? It (she/he) ...\n", prev->data);
        scanf("%255[^\n]", word);
        bufClear();
        printf("feature = %s\n", word);

        Node *featureNode = createNode(strdup(word), objectNode, prev);
        printNode(featureNode, stdout);

        if      (prevPrev == NULL)       objectTree->root = featureNode;
        else if (prevPrev->left == prev) prevPrev->left   = featureNode;
        else                             prevPrev->right  = featureNode;
    }
            
    return EXIT_SUCCESS;
}

void bufClear()
{
    while (getchar() != '\n') {};
    return;
}
