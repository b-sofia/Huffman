#include "huffman.h"
NODE* MakeNodeFromNode(const NODE* left, const NODE* right) {
    NODE* res = (NODE*)malloc(sizeof(NODE));
    res->freq = left->freq + right->freq;
    res->isSymb = 0;
    res->symb = 0;
    res->left = (NODE*)left;
    res->right = (NODE*)right;
    res->next = 0;
    return res;
}
NODE* MakeTreeFromList(NODE* head) {
    while (head && head->next) {
        NODE* left = head;
        NODE* right = head->next;
        Add2List(&(head->next->next), MakeNodeFromNode(left, right));
        head = head->next->next;
    }
    return head;
}