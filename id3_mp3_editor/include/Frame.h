#ifndef FRAME_H
#define FRAME_H

#define TAG_LEN 4
#define FRAME_SIZE_LEN 4
#define FLAGS_LEN 2

typedef struct Frame {
    char* tag;
    char* flags;
    int data_size;
    char* data;
} Frame;

void Frame_print(const Frame* self);
Frame* Frame_init();
void Frame_cpy(Frame *self, const char *tag, const char *flags,
               int data_size, const char *data);
void Frame_free(Frame* self);

#endif