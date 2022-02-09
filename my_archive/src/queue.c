#include "../include/queue.h"

#include <stdio.h>
#include <stdlib.h>

Node* Node_init(TreeNode* tree) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->tree = tree;
    node->next = NULL;
    return node;
}

PNode* PNode_init(int priority) {
    PNode* pnode = (PNode*)malloc(sizeof(PNode));
    pnode->priority = priority;
    pnode->ntop = NULL;
    pnode->next = NULL;
    return pnode;
}

Queue* Queue_init() {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->size = 0;
    return queue;    
}

PNode* Queue_search_pnode(Queue *self, int priority);
void PNode_push(PNode* self, Node* node);


void Queue_push(Queue *self, int priority, TreeNode *tree) {
    Node* new_node = Node_init(tree);
    PNode* pnode = Queue_search_pnode(self, priority);
    PNode_push(pnode, new_node);
    self->size++;
}

PNode* Queue_search_pnode(Queue *self, int priority) {
    if (!self->front) {
        PNode* new_pnode = PNode_init(priority);
        self->front = new_pnode;
        return new_pnode;
    }
    if (self->front->priority > priority) {
        PNode* new_front = PNode_init(priority);
        new_front->next = self->front;
        self->front = new_front;
        return new_front;
    }

    PNode *cur = self->front;
    while (cur->next != NULL && cur->next->priority <= priority) {
        cur = cur->next;
    }

    if (cur->priority == priority) {
        return cur;
    } else {
        PNode *new_pnode = PNode_init(priority);
        new_pnode->next = cur->next;
        cur->next = new_pnode;
        return new_pnode;
    }
}

void PNode_push(PNode* self, Node* node) {
    if (!self->ntop) {
        self->ntop = node;
        return;
    }
    Node* cur = self->ntop;
    while (cur->next) {
        cur = cur->next;
    }
    cur->next = node;
}

TreeNode* Queue_top(Queue *self) {
    if (!self->front) {
        return NULL;
    }
    return self->front->ntop->tree;
}

void Node_free(Node* self);

TreeNode* Queue_pop(Queue *self, int *priority) {
    if (!self->front) {
        printf("ERROR QUEUE IS EMPTY!!");
        return NULL;
    }
    if (!self->front->ntop) {
        printf("ERROR unexpected behaviour!!\n");
        exit(1);
        return NULL;
    }
    TreeNode *out = self->front->ntop->tree;
    *priority = self->front->priority;
    if (!self->front->ntop->next) {
        free(self->front->ntop);
        PNode *new_front = self->front->next;
        free(self->front);
        self->front = new_front;
        self->size--;
    } else {
        Node* new_ntop = self->front->ntop->next;
        free(self->front->ntop);
        self->front->ntop = new_ntop;
        self->size--;
    }
    return out;
}

void Queue_free(Queue* self) {
    if (self->front->ntop){
        Node_free(self->front->ntop);
    }
    if (self->front) {
        free(self->front);
    }
    free(self);
}

void Node_free(Node* self) {    
    free(self);
}