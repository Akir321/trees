#ifndef  __TREES_H__
#define  __TREES_H__

typedef int elem_t;
#define ElemFormat "%d"

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

const int Poison    = -1111111;
Node * const PtrPoison = (Node *)42;

const int WordLength = 64;



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
