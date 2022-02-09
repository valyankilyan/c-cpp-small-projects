#include "../include/BMP.h"
#include "string.h"

void BMP_from8to1(BMP* self) {
    if (self->info_header->BitCount != 8) {
        printf("an Error in BMP_from8to1 bitcount = %d\n",
               self->info_header->BitCount);
        return;
    }    

    self->info_header->BitCount = 1;
    BMP_calc_dimensions(self);
    self->file_header->FileSize -= self->info_header->ImageSize;
    self->info_header->ImageSize = self->info_header->Height * self->info_header->WidthBytes;
    self->file_header->FileSize += self->info_header->ImageSize;

    unsigned char** new_image = (unsigned char**)malloc(self->info_header->Height * sizeof(unsigned char*));
    for (unsigned int i = 0; i < self->info_header->Height; i++) {
        new_image[i] = (unsigned char*)malloc((self->info_header->WidthBytes + 1) * sizeof(unsigned char));
        for (unsigned int j = self->info_header->WidthBytes - 4; j <= self->info_header->WidthBytes; j++) {
            new_image[i][j] = '\0';
        }
    }

    // In case there is colors table
    if (self->info_header->ColorsUsed != 0) {
        self->file_header->FileSize -= self->info_header->ColorsUsed * 4;
        self->file_header->DataOffset -= self->info_header->ColorsUsed * 4;
        for (unsigned int i = 0; i < self->info_header->ColorsUsed; i++) {
            free(self->color_used[i]);
        }
    }
    free(self->color_used);
    self->color_used = NULL;

    // Adding information about colour table
    self->info_header->ColorsUsed = 2;
    self->info_header->ColorsImportant = 2;
    self->file_header->FileSize += self->info_header->ColorsUsed * 4;
    self->file_header->DataOffset += self->info_header->ColorsUsed * 4;

    // Filling color table with two colors
    self->color_used = (unsigned char**)malloc(self->info_header->ColorsUsed * sizeof(unsigned char*));
    for (unsigned int i = 0; i < self->info_header->ColorsUsed; i++) {
        self->color_used[i] = (unsigned char*)malloc((3 + 1) * sizeof(unsigned char));
        self->color_used[i][3] = '\0';        
        for (int j = 0; j < 3; j++) {
            self->color_used[i][j] = i * 255;            
        }        
    }

    short int lim = 255;
    short int vertical_matrix[self->info_header->Height][self->info_header->Width];
    for (unsigned int i = 0; i < self->info_header->Width; i++) {
        short int carry = 0;
        for (unsigned int j = 0; j < self->info_header->Height; j++) {
            carry += self->image[j][i];
            vertical_matrix[j][i] = carry >= lim;
            carry -= carry >= lim ? lim : 0;
        }
    }
    short int gorizontal_matrix[self->info_header->Height][self->info_header->Width];
    for (unsigned int i = 0; i < self->info_header->Height; i++) {
        short int carry = 0;
        for (unsigned int j = 0; j < self->info_header->Width; j++) {
            carry += self->image[i][j];
            gorizontal_matrix[i][j] = carry >= lim;
            carry -= carry >= lim ? lim : 0;
        }
    }

    for (unsigned int i = 0; i < self->info_header->Height; i++) {
        for (unsigned int j = 0; j < self->info_header->Width; j++) {
            if (j % 8 == 0) {
                new_image[i][j/8] = 0;
            }
            if (gorizontal_matrix[i][j] && vertical_matrix[i][j]) {
                new_image[i][j/8] += (1 << (7 - j % 8));
            }
        }
    }    

    BMP_image_free(self);
    self->image = new_image;
}

void BMP_from24to8(BMP* self) {
    if (self->info_header->BitCount != 24) {
        printf("ERROR in BMP_from24to8 BitCount = %d \n", self->info_header->BitCount);
        return;
    }

    // Saving old value
    unsigned int oldWidthBytes = self->info_header->WidthBytes;

    // Recalculating dimensions and Size variables
    self->info_header->BitCount = 8;
    BMP_calc_dimensions(self);
    self->file_header->FileSize -= self->info_header->ImageSize;
    self->info_header->ImageSize = self->info_header->Height * self->info_header->WidthBytes;
    self->file_header->FileSize += self->info_header->ImageSize;

    // Initializing new image
    unsigned char** new_image = (unsigned char**)malloc(self->info_header->Height * sizeof(unsigned char*));
    for (unsigned int i = 0; i < self->info_header->Height; i++) {
        new_image[i] = (unsigned char*)malloc(self->info_header->WidthBytes * sizeof(unsigned char) + 1);
        new_image[i][self->info_header->WidthBytes] = '\0';
    }

    // In case there is colors table
    if (self->info_header->ColorsUsed != 0) {
        self->file_header->FileSize -= self->info_header->ColorsUsed * 4;
        self->file_header->DataOffset -= self->info_header->ColorsUsed * 4;
        for (unsigned int i = 0; i < self->info_header->ColorsUsed; i++) {
            free(self->color_used[i]);
        }
    }
    free(self->color_used);
    self->color_used = NULL;

    // Adding information about color table
    self->info_header->ColorsUsed = 256;
    self->info_header->ColorsImportant = 256;
    self->file_header->FileSize += self->info_header->ColorsUsed * 4;
    self->file_header->DataOffset += self->info_header->ColorsUsed * 4;

    // Filling color table with all grayscale
    self->color_used = (unsigned char**)malloc(256 * sizeof(unsigned char*));
    for (int i = 0; i < 256; i++) {
        self->color_used[i] = (unsigned char*)malloc((3 + 1) * sizeof(unsigned char));
        self->color_used[i][3] = '\0';
        for (int j = 0; j < 3; j++) {
            self->color_used[i][j] = i;
        }
    }

    // Filling new image by middle value of three rgb bytes
    for (unsigned int i = 0; i < self->info_header->Height; i++) {
        for (unsigned int j = 0; j < oldWidthBytes; j += 3) {
            unsigned short int mid = 0;
            for (unsigned int b = 0; b < 3; b++) {
                mid += (unsigned short int)self->image[i][j + b];
            }
            mid /= 3;
            new_image[i][j / 3] = mid;
        }
    }

    // Freeing and replacing
    BMP_image_free(self);
    self->image = new_image;
}