#include "../include/ID3.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEW_FILE "file.temp"

void ID3_get_header(ID3 *self);
void ID3_get_frames(ID3 *self);
void ID3_read_tag(ID3 *self, char *tag_name, int *count, char *info);
void ID3_read_tag_header(ID3 *self, char tag_name[], int *count, char flags[]);
char *ID3_read_tag_data(ID3 *self, int *data_len, char *data);
void ID3_print(const ID3 *self);

ID3 *ID3_init(char *filename) {
    FILE *file;
    file = fopen(filename, "rb");

    if (file == NULL) {
        printf("File doesn't exist or empty.\n");
        return NULL;
    }

    ID3 *id3 = (ID3 *)malloc(sizeof(ID3));
    id3->filename = (char *)malloc(strlen(filename) + 1);
    strcpy(id3->filename, filename);
    id3->file = file;
    id3->frames = FLL_init();

    ID3_get_header(id3);
    ID3_get_frames(id3);

    return id3;
}

void ID3_get_header(ID3 *self) {
    fread(self->identifier, 1, ID3_ID_LENGTH, self->file);
    fread(self->version, 1, ID3_VERSION_LENGTH, self->file);
    fread(&self->flag, 1, 1, self->file);

    unsigned char csize[ID3_SIZE_LENGTH];
    self->size = 0;
    fread(csize, 1, ID3_SIZE_LENGTH, self->file);
    for (int i = ID3_SIZE_LENGTH - 1; i >= 0; i--) {
        self->size += csize[i] << ((ID3_SIZE_LENGTH - 1 - i) * 8);
    }
}

void ID3_get_frames(ID3 *self) {
    int ind = 0;
    while (ind < self->size) {
        Frame *frame = Frame_init();
        ID3_read_tag_header(self, frame->tag, &frame->data_size, frame->flags);
        frame->data = ID3_read_tag_data(self, &frame->data_size, frame->data);

        FLL_push(self->frames, frame);

        ind += frame->data_size + TAG_LEN + FLAGS_LEN + FRAME_SIZE_LEN;
    }
}

void ID3_read_tag_header(ID3 *self, char *tag_name, int *data_len, char *flags) {
    fread(tag_name, 1, TAG_LEN, self->file);

    unsigned char csize[ID3_SIZE_LENGTH];
    *data_len = 0;
    fread(csize, 1, FRAME_SIZE_LEN, self->file);
    for (int i = ID3_SIZE_LENGTH - 1; i >= 0; i--) {
        *data_len += (int)csize[i] << ((ID3_SIZE_LENGTH - 1 - i) * 8);
    }

    fread(flags, 1, FLAGS_LEN, self->file);
}

char *ID3_read_tag_data(ID3 *self, int *data_len, char *data) {
    data = malloc(*data_len + 1);
    fread(data, 1, *data_len, self->file);
    return data;
}

void ID3_write_header(ID3 *self, FILE *file);
void ID3_write_frames(ID3 *self, FILE *file);
void ID3_write_other_data(ID3 *self, FILE *file);

void ID3_make_file(ID3 *self, char *filename) {
    char new_name = (filename != NULL);
    if (!new_name) {
        filename = NEW_FILE;
    }
    FILE *new_file = fopen(filename, "wb");

    self->size = self->frames->bytes;
    ID3_write_header(self, new_file);
    ID3_write_frames(self, new_file);

    ID3_write_other_data(self, new_file);
    fclose(new_file);

    if (!new_name) {
        remove(self->filename);
        rename(filename, self->filename);
    }
}

void ID3_write_header(ID3 *self, FILE *file) {
    char size[4];
    for (int i = 3; i >= 0; i--) {
        size[i] = self->size % 256;
        self->size /= 256;
    }

    for (int i = 0; i < 3; i++) {
        putc(self->identifier[i], file);
    }
    for (int i = 0; i < 2; i++) {
        putc(self->version[i], file);
    }
    putc(self->flag, file);
    for (int i = 0; i < 4; i++) {
        putc(size[i], file);
    }
}

void ID3_write_frames(ID3 *self, FILE *file) {
    while (FLL_top(self->frames) != NULL) {
        Frame *cur = FLL_top(self->frames);
        for (int i = 0; i < TAG_LEN; i++) {
            putc(cur->tag[i], file);
        }

        int frame_size = cur->data_size;
        char frame_size_str[FRAME_SIZE_LEN];
        for (int i = FRAME_SIZE_LEN - 1; i >= 0; i--) {
            frame_size_str[i] = frame_size % 256;
            frame_size /= 256;
        }
        for (int i = 0; i < FRAME_SIZE_LEN; i++) {
            putc(frame_size_str[i], file);
        }

        for (int i = 0; i < FLAGS_LEN; i++) {
            putc(cur->flags[i], file);
        }

        for (int i = 0; i < cur->data_size; i++) {
            putc(cur->data[i], file);
        }
        FLL_pop_front(self->frames);
    }
}

void ID3_write_other_data(ID3 *self, FILE *file) {
    size_t n, m;
    unsigned char buff[8192];
    do {
        n = fread(buff, 1, sizeof buff, self->file);
        if (n) {
            m = fwrite(buff, 1, n, file);
        } else {
            m = 0;
        }
    } while ((n > 0) && (n == m));
}

void ID3_print(const ID3 *self) {
    printf("File: %s\n", self->filename);
    FLL_print(self->frames);
}

void ID3_free(ID3 *self) {
    fclose(self->file);
    FLL_free(self->frames);
    free(self->filename);
    free(self);
}