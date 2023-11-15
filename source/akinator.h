#ifndef  __AKINATOR__
#define  __AKINATOR__

#include "stack.h"

const char * const dataBaseName = "data_base.txt";

enum AkinatorCommands
{
    GUESS        = 'g',
    DEFINITION   = 'd',
    COMPARE      = 'c',
    EXIT_SAVE    = 's',
    EXIT_NO_SAVE = 'w',
    GRAPHIC_DUMP = 'o',
};

enum DirectionChoice
{
    RIGHT_NO = 1,
    LEFT_YES = 2,
};

int runAkinator(Tree *objectTree);

int getAkinatorCommand(void);

int processAkinatorCommand(Tree *objectTree, int command);

int commandAkinatorGuess     (Tree *objectTree);
int commandAkinatorDefinition(Tree *objectTree);

bool treeFindNode(Tree *objectTree, char *objectName, stack *choiceStack);
bool findNode    (Node *node,       char *objectName, stack *choiceStack);

void bufClear(void);



#endif //__AKINATOR__
