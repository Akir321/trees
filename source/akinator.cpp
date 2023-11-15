#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../trees/source/trees.h"
#include "../trees/source/tree_graphic_dump.h"
#include "akinator.h"
#include "stack.h"



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
            bufClear();
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
        
        case DEFINITION:
            return commandAkinatorDefinition(objectTree);
        case GRAPHIC_DUMP:
        {
            int dumpNumber = treeGraphicDump(objectTree);
            char *cmdCommand = NULL;

            __mingw_asprintf(&cmdCommand, "start gr_dump/tree_dump%d.dot.png", dumpNumber);
            system(cmdCommand);
            free(cmdCommand);

            return EXIT_SUCCESS;
        }
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
        answer   = 0;
        prevPrev = prev;
        prev     = current;

        printf("It (she/he) %s? [y/n]\n", current->data);
        while (answer != 'y' && answer != 'n') { answer = getchar(); }
        bufClear();
    
        printf("%c\n", answer);
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

        if      (prevPrev == NULL)        objectTree->root = featureNode;
        else if (prevPrev->left  == prev) prevPrev->left   = featureNode;
        else if (prevPrev->right == prev) prevPrev->right  = featureNode;
        else                              printf("ERROR: bad ptrs\n");
    }
            
    return EXIT_SUCCESS;
}

#define STACK_VERIFY(stk)                      \
    if (errorFieldToU(stackError(stk)))        \
    {                                          \
        printf("STACK CORRUPTED\n");           \
        STACK_DUMP(stk);                       \
        return errorFieldToU(stackError(stk)); \
    }

int commandAkinatorDefinition(Tree *objectTree)
{
    assert(objectTree);

    stack choiceStack = {};
    stackCtor(&choiceStack, 2);

    printf("The definition of which object do you want?\n");

    char objectName[WordLength] = {};
    scanf("%255[^\n]", objectName);
    bufClear();

    if (treeFindNode(objectTree, objectName, &choiceStack))
    {
        printf("We can say about %s that it (she/he)", objectName);

        Node *current = objectTree->root;
        size_t stackPosition = 0;

        while (stackPosition < choiceStack.size)
        {
            putchar('\n');

            if (choiceStack.data[stackPosition] == RIGHT_NO) printf(" not"); 
            printf(" %s ", current->data);

            if (choiceStack.data[stackPosition] == RIGHT_NO) current = current->right;
            else                                             current = current->left;

            stackPosition++;
        }
        printf("\n\n");

        stackDtor(&choiceStack);

        return EXIT_SUCCESS;
    }
    else
    {
        printf("Sorry,  couldn't find the object. You might've misspelled it\n");
        printf("or it is not present in the database.\n\n");

        stackDtor(&choiceStack);

        return EXIT_FAILURE;
    }
}

bool treeFindNode(Tree *objectTree, char *objectName, stack *choiceStack)
{
    assert(objectTree);
    assert(objectName);
    STACK_VERIFY(choiceStack);

    return findNode(objectTree->root, objectName, choiceStack);
}

bool findNode(Node *node, char *objectName, stack *choiceStack)
{
    if (!node)                               return false;
    if (strcmp(objectName, node->data) == 0) return true;

    stack_elem_t popValue = 0;

    stackPush(choiceStack, LEFT_YES);
    if (findNode(node->left, objectName, choiceStack)) return true;
    stackPop(choiceStack, &popValue);

    stackPush(choiceStack, RIGHT_NO);
    if (findNode(node->right, objectName, choiceStack)) return true;
    stackPop(choiceStack, &popValue);

    return false;
}

void bufClear()
{
    while (getchar() != '\n') {};
    return;
}
