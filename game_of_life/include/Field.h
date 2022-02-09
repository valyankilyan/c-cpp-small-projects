#ifndef FIELD_H
#define FIELD_H

#include "../include/BMP.h"

typedef unsigned int uint;
typedef unsigned char uchar;

typedef struct Field {
    BMP* picture;
    char* dir;
    int frame;
} Field;

Field* Field_init(const char* dir);
void Field_generate_from_file(Field* self, char* filename);
char* int_to_str(int n);
char* generate_framename(Field* self);
uchar Field_get_cell(Field* self, uint x, uint y);
void Field_put_cell(Field* self, uint x, uint y, uchar value);
void Field_print(Field *self);
void Field_free(Field* self);
void Field_adjust_sides(Field* self);
void Field_make_turn(Field* self);

#endif