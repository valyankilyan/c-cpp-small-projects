#ifndef FVECTOR_H
#define FVECTOR_H

#include "../include/Frame.h"

typedef struct Node {
    Frame *value;
    struct Node *next, *prev;
} Node;

typedef struct FLL {
    Node *head, *tail;
    int size;
    int bytes;
} FLL;

/*
* Initialize Frame Linked List and make
* head = tail = NULL
* size = bytes = 0
*/
FLL* FLL_init();

/*
* Pushes Frame into linked list
* also increases size on 1 and bytes on data length
*/
void FLL_push(FLL *self, Frame *value);


/*
* Searched tag in linked list with name <VALUE>
* return 1 if found -- 0 if not
*/
int FLL_tagname_exists(FLL *self, const char *value);

/*
* Searches tag in linked list with name <value>
* and deleting it.
* If tag wasn't found -- printing about it into stdout
* also changing bytes and size value
*/
void FLL_delete_tagname(FLL *self, const char* value);

/*
* Returns head value of linked list
* Use wisely!
*/
Frame* FLL_top(const FLL *self);


/*
* deletes head element of linked list
*/
void FLL_pop_front(FLL *self);

/*
* Prints all the frames into stdout
*/
void FLL_print(const FLL *self);

/*
* Frees linked list and all its nodes
*/
void FLL_free(FLL *self);

#endif