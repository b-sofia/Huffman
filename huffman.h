#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CODE_SIZE 256
#define BIT8 8
typedef struct node {
    unsigned char symb;
    unsigned char isSymb;
    unsigned int freq;
    unsigned char code[CODE_SIZE];
    int level;
    struct node *left, *right, *next;
} NODE;
NODE* MakeNodeFromNode(const NODE* left, const NODE* right);
NODE* MakeTreeFromList(NODE* head);
void Add2List(NODE** head, NODE* newNode);