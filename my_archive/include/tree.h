#ifndef TREE_H
#define TREE_H

typedef unsigned char uchar;

typedef struct TreeNode {
    struct TreeNode *left, *right;
    uchar value;
    int priority;
} TreeNode;

TreeNode* TreeNode_init(uchar value);
TreeNode* TreeNode_push(TreeNode* self, TreeNode* left, TreeNode* right);
void TreeNode_print(TreeNode* self);
void TreeNode_free(TreeNode* self);

#endif