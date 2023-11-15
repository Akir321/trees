#ifndef  __AKINATOR__
#define  __AKINATOR__

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

int runAkinator(Tree *objectTree);

int getAkinatorCommand(void);

int processAkinatorCommand(Tree *objectTree, int command);

int commandAkinatorGuess(Tree *objectTree);

void bufClear(void);



#endif //__AKINATOR__
