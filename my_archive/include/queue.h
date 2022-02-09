
#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>


#include "../include/tree.h"

typedef struct Node {    
    TreeNode *tree;
    struct Node *next;    
} Node;

typedef struct PNode {
    int priority;
    Node *ntop;
    struct PNode *next;
} PNode;

typedef struct Queue {
    PNode *front;
    size_t size;
} Queue;

// Node* Node_init(TreeNode* tree);
// PNode* PNode_init(int priority);
Queue* Queue_init();
void Queue_push(Queue *self, int priority, TreeNode *tree);
TreeNode* Queue_top(Queue *self);
TreeNode* Queue_pop(Queue *self, int *priority);
void Queue_free(Queue* self);

#endif