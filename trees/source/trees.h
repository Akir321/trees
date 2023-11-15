#ifndef  __TREES_H__
#define  __TREES_H__

#define INT    1
#define DOUBLE 2
#define STR    3

#define __USE_TYPE__ STR

#if __USE_TYPE__ == INT
typedef int elem_t;
const int Poison = -1111111;
#define ElemFormat "%d"

#elif __USE_TYPE__ == DOUBLE
typedef double elem_t;
const double Poison = NAN;
#define ElemFormat "%lg"

#elif __USE_TYPE__ == STR
typedef char* elem_t;
char * const Poison = (char *)42;
#define ElemFormat "%s*"

#else
typedef int elem_t;
const int Poison = -1111111;
#define ElemFormat "%d"

#endif

struct Node
{
    elem_t data;

    Node *left;
    Node *right;
};

struct Tree
{
    Node *root;
    int size;
};

Node * const PtrPoison = (Node *)42;

const int WordLength = 256;



Node *createNode(elem_t data, Node *left, Node *right);
int destroyNode (Node **nodePtr);
int printNode   (Node *node, FILE *f);

int treeCtor(Tree *tree, Node *root);

int treeSize(Node *root);
int treeDtor(Node *root);

int printTreePrefix (Node *root, FILE *f);
int printTreeInfix  (Node *root, FILE *f);
int printTreePostfix(Node *root, FILE *f);

int sortTreeAdd(Tree *tree, elem_t value);

Node *readTree(const char *fileName);
Node *readNode(const char *buffer, int *position);

int fileSize(const char *name);

#endif //__TREES_H__
