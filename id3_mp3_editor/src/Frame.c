#include "../include/Frame.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Frame_print(const Frame *self) {
    printf("Frame %.*s: ", TAG_LEN, self->tag);
    for (int i = 0; i < self->data_size; i++) {
        if (self->data[i] != 0)
            printf("%c", self->data[i]);
    }
    printf("\n");
}

Frame *Frame_init() {
    Frame *frame = (Frame *)malloc(sizeof(Frame));
    frame->tag = (char *)calloc(TAG_LEN + 1, sizeof(char));
    frame->flags = (char *)calloc(FLAGS_LEN + 1, sizeof(char));

    return frame;
}

void Frame_cpy(Frame *self, const char *tag, const char *flags,
               int data_size, const char *data) {    
    self->data_size = data_size;
    self->data = (char *)calloc(data_size + 1, sizeof(char));


    strcpy(self->tag, tag);
    strcpy(self->flags, flags);
    strcpy(self->data, data);
}

void Frame_free(Frame *self) {
    free(self->tag);
    free(self->flags);
    free(self->data);
    free(self);
}
// add TTTT yyyyyyyyyyyyyyyyyyyyyyyyy