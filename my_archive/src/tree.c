#include "../include/tree.h"

#include <stdlib.h>
#include <stdio.h>

void TreeNode_print_code(TreeNode* self, int len, char* code);

TreeNode* TreeNode_init(uchar value) {
    TreeNode* treenode = (TreeNode*) malloc (sizeof(TreeNode));
    treenode->value = value;
    treenode->left = NULL;
    treenode->right = NULL;
    return treenode;
}

TreeNode* TreeNode_push(TreeNode* self, TreeNode* left, TreeNode* right) {
    self->left = left;
    self->right = right;
    return self;
}

void TreeNode_print(TreeNode* self) {
    if (!self->left && !self->right) {
        printf("-1: %d\n", self->value);
    }
    char* code = (char*)malloc(256 * sizeof(char));
    for (int i = 0; i < 256; i++) {
        code[i] = 0;
    }    
    TreeNode_print_code(self, 0, code);
    free(code);   
}

void TreeNode_print_code(TreeNode* self, int len, char* code) {    
    if (!self->right && !self->left) {
        printf("%s: %d\n", code, self->value);
    }    
    if (self->right) {        
        code[len] = '1';
        TreeNode_print_code(self->right, len+1, code);
    }
    if (self->left) {        
        code[len] = '0';
        TreeNode_print_code(self->left, len+1, code);
    }
    code[len] = 0;
}

void TreeNode_free(TreeNode* self) {
    if (!self) {
        return;
    }
    if (self->right) {
        TreeNode_free(self->right);
    }
    if (self->left) {
        TreeNode_free(self->left);
    }

    free(self);
}