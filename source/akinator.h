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
int commandAkinatorComparison(Tree *objectTree);

int writeObjectFeatures   (Tree *objectTree, Node *current, stack *choiceStack, size_t stackPosition);
int writeObjectsComparison(Tree *objectTree, 
                           const char *objectName1, stack *choiceStack1,
                           const char *objectName2, stack *choiceStack2);


bool treeFindNode(Tree *objectTree, const char *objectName, stack *choiceStack);
bool findNode    (Node *node,       const char *objectName, stack *choiceStack);

void bufClear(void);



#endif //__AKINATOR__
