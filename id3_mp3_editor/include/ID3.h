#ifndef ID3_H
#define ID3_H

#include <stdio.h>
#include "FLL.h"

#define ID3_HEADER_SIZE 10

#define ID3_ID_LENGTH 3
#define ID3_VERSION_LENGTH 2
#define ID3_SIZE_LENGTH 4

typedef struct ID3 {
    char* filename;
    FILE* file;

    char identifier[3];
    char version[2];
    char flag;
    int size;    

    FLL *frames;
} ID3;

ID3* ID3_init(char* filename);
void ID3_print(const ID3 *self);
void ID3_make_file(ID3 *self, char* filename);
void ID3_free(ID3 *self);

#endif