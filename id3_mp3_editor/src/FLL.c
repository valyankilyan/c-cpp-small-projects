#include "../include/FLL.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *Node_init(Frame *frame) {
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->value = frame;
    temp->next = NULL;
    temp->prev = NULL;

    return temp;
}

void Node_free(Node *self) {
    Frame_free(self->value);
    free(self);
}

FLL *FLL_init() {
    FLL *temp = (FLL *)malloc(sizeof(FLL));
    temp->head = NULL;
    temp->tail = NULL;
    temp->size = 0;
    temp->bytes = 0;

    return temp;
}

void FLL_push(FLL *self, Frame *value) {
    self->size++;
    self->bytes +=
        TAG_LEN +
        FLAGS_LEN +
        value->data_size;

    Node *temp = Node_init(value);    
    if (self->tail == NULL) {
        self->tail = temp;
        self->head = temp;
        return;
    }

    self->tail->next = temp;
    temp->prev = self->tail;
    self->tail = temp;
}

/*
 * deletes Node from linked list
 */
void FLL_delete(FLL *self, Node *node) {
    self->size--;
    self->bytes -=
        TAG_LEN +
        FLAGS_LEN +
        node->value->data_size;

    Node *prev = node->prev;
    Node *next = node->next;
    Node_free(node);
    if (self->head == node) {
        self->head = next;
    }
    if (self->tail == node) {
        self->tail = prev;
    }
    if (prev != NULL) {
        prev->next = next;
    }
    if (next != NULL) {
        next->prev = prev;
    }
}

int FLL_tagname_exists(FLL *self, const char *value) {
    Node *cur = self->head;
    while(cur != NULL) {
        if (strcmp(cur->value->tag, value) == 0) {
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}

void FLL_delete_tagname(FLL *self, const char *value) {
    Node *cur = self->head;
    while (cur != NULL) {
        if (strcmp(cur->value->tag, value) == 0) {        
            FLL_delete(self, cur);
            printf("%s deleted.\n", value);
            return;
        }
        cur = cur->next;
    }
    printf("No %s tags found. Try another one\n", value);
}

Frame *FLL_top(const FLL *self) {
    if (self->head == NULL) 
        return NULL;
    return self->head->value;
}

void FLL_pop_front(FLL *self) {
    if (self->head == NULL) {
        return;
    }
    FLL_delete(self, self->head);
}

void FLL_print(const FLL *self) {
    Node *cur = self->head;
    while (cur != NULL) {
        Frame_print(cur->value);
        cur = cur->next;
    }
}

void FLL_free(FLL *self) {
    Node *cur = self->head;
    Node *next;
    while (cur != NULL) {
        next = cur->next;
        Node_free(cur);
        cur = next;
    }
    free(self);
}
