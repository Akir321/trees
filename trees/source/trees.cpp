#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>

#include "trees.h"

Node *createNode(elem_t data, Node *left, Node *right)
{
    Node *node = (Node *)calloc(1, sizeof(Node));
    if (!node) return NULL;

    node->data  = data;
    node->left  = left;
    node->right = right;

    return node;
}

int destroyNode(Node **nodePtr)
{
    assert(nodePtr);

    Node *node = *nodePtr;
    
    #if __USE_TYPE__ == STR
    free (node->data);
    #endif

    node->data  = Poison;
    node->left  = PtrPoison;
    node->right = PtrPoison;

    free(node);
    *nodePtr = PtrPoison;

    return EXIT_SUCCESS;
}

int printNode(Node *node, FILE *f)
{
    assert(node);
    assert(f);

    fprintf(f,  ElemFormat, node->data);
    return EXIT_SUCCESS;
}

int treeCtor(Tree *tree, Node *root)
{
    assert(root);

    tree->root = root;
    tree->size = treeSize(root);

    return EXIT_SUCCESS;
}

int treeSize(Node *root)
{
    if (root == NULL) return 0;

    return treeSize(root->left) + treeSize(root->right);
}

int treeDtor(Node *root)
{
    if (root == NULL) return 0;

    treeDtor(root->left);
    treeDtor(root->right);
    destroyNode(&root);

    return EXIT_SUCCESS;
}

int printTreePrefix(Node *root, FILE *f)
{
    assert(f);

    if (!root) 
    {
        fprintf(f, "nil");
        return EXIT_SUCCESS;
    }

    putc('(', f);

    printNode(root, f);  putc(' ', f);

    printTreePrefix(root->left, f);
    putc(' ', f);
    printTreePrefix(root->right, f);

    putc(')', f);
    return EXIT_SUCCESS;
}

int printTreeInfix(Node *root, FILE *f)
{
    assert(f);

    if (!root) 
    {
        printf("nil");
        return EXIT_SUCCESS;
    }

    putc('(', f);

    printTreeInfix(root->left, f);
    putc(' ', f);
    
    printNode(root, f);
    putc(' ', f);

    printTreeInfix(root->right, f);
    putc(')', f);

    return EXIT_SUCCESS;
}

int printTreePostfix(Node *root, FILE *f)
{
    assert(f);

    if (!root) 
    {
        printf("nil");
        return EXIT_SUCCESS;
    }

    putc('(', f);

    printTreePostfix(root->left, f);
    putc(' ', f);

    printTreePostfix(root->right, f);
    putc(' ', f);

    printNode(root, f);
    putc(')', f);

    return EXIT_SUCCESS;
}

int fileSize(const char *name)
{
    assert(name);

    struct stat stats = {};
    if (stat(name, &stats) == -1)  return -1;

    int size = stats.st_size;
    return size;
}

Node *readTree(const char *fileName)
{
    assert(fileName);
    
    int size = fileSize(fileName);

    char *buffer = (char *)calloc(size, sizeof(char));
    if  (!buffer)  return NULL;

    FILE *f = fopen(fileName, "r");
    if (!f) return NULL;

    fread(buffer, sizeof(char), size, f);
    fclose(f);

    int position = 0;

    Node *root = readNode(buffer, &position);
    free(buffer);

    return root;
}

Node *readNode(const char *buffer, int *position)
{
    assert(buffer);
    assert(position);

    char word[WordLength] = {};
    int shift             = 0;

    sscanf(buffer + *position, "%s%n", word, &shift);
    printf("word = %s\n", word);

    if (strncmp(word, "nil", 3) == 0)
    {
        (*position) += shift;
        return NULL;
    }

    while (buffer[*position] != '(') { (*position)++; }
    (*position)++;

    #if __USE_TYPE__ == STR
    elem_t data = word;

    if (!sscanf(buffer + *position, "%255[^*]%n", data, &shift)) return NULL;
    printf("data = %s\n", data);
    (*position) += shift + 1;

    Node *node  = createNode(strdup(data), NULL, NULL);

    #else
    elem_t data = 0;
    if (!sscanf(buffer + *position, ElemFormat "%n", &data, &shift)) return NULL;
    (*position) += shift;

    Node *node  = createNode(data, NULL, NULL);

    #endif

    node->left  = readNode(buffer, position);
    node->right = readNode(buffer, position);

    return node;
}

int sortTreeAdd(Tree *tree, elem_t value)
{
    assert(tree);

    Node *prev    = tree->root;
    Node *current = tree->root;

    while (current)
    {
        prev = current;

        if (value == current->data) return EXIT_FAILURE;
        else if (value < current->data) current = current->left;
        else if (value > current->data) current = current->right;
    }

    if (value < prev->data) prev->left  = createNode(value, NULL, NULL);
    else                    prev->right = createNode(value, NULL, NULL);

    return EXIT_SUCCESS;
}
