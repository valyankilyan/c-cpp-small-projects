#include "../include/BMP.h"

#include "string.h"

BMP* BMP_init() {
    BMP* bmp = (BMP*)malloc(sizeof(BMP));
    bmp->file = NULL;
    bmp->filename = NULL;

    bmp->file_header = NULL;
    bmp->info_header = NULL;
    bmp->color_used = NULL;
    bmp->image = NULL;

    return bmp;
}

void BMP_read_fileheader(BMP* self);
void BMP_read_infoheader(BMP* self);
void BMP_read_colorsused(BMP* self);
void BMP_read_image(BMP* self);
void BMP_calc_dimensions(BMP* self);

void BMP_read(BMP* self, char* filename) {
    self->filename = realloc(self->filename, strlen(filename) + 1);
    strcpy(self->filename, filename);
    self->file = fopen(filename, "rb");
    BMP_read_fileheader(self);
    BMP_read_infoheader(self);
    BMP_calc_dimensions(self);

    BMP_read_colorsused(self);
    BMP_read_image(self);
}

void BMP_read_fileheader(BMP* self) {
    BITMAPFILEHEADER* file_header = (BITMAPFILEHEADER*)malloc(sizeof(BITMAPFILEHEADER));

    file_header->Signature = malloc(FILEHEADER_SIGNATURE_L + 1);
    file_header->Signature[FILEHEADER_SIGNATURE_L] = '\0';
    fread(file_header->Signature, 1, FILEHEADER_SIGNATURE_L, self->file);
    fread(&file_header->FileSize, FILEHEADER_FILESIZE_L, 1, self->file);
    file_header->Reserved = malloc(FILEHEADER_RESERVED_L + 1);
    file_header->Reserved[FILEHEADER_RESERVED_L] = '\0';
    fread(file_header->Reserved, 1, FILEHEADER_RESERVED_L, self->file);
    fread(&file_header->DataOffset, FILEHEADER_DATAOFFSET_L, 1, self->file);

    self->file_header = file_header;
}

void BMP_read_infoheader(BMP* self) {
    BITMAPINFOHEADER* info_header = (BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER));

    fread(&info_header->Size, INFOHEADER_SIZE_L, 1, self->file);
    fread(&info_header->Width, INFOHEADER_WIDTH_L, 1, self->file);
    fread(&info_header->Height, INFOHEADER_HEIGHT_L, 1, self->file);
    fread(&info_header->Planes, INFOHEADER_PLANES_L, 1, self->file);
    fread(&info_header->BitCount, INFOHEADER_BITCOUNT_L, 1, self->file);
    fread(&info_header->Compression, INFOHEADER_COMPRESSION_L, 1, self->file);
    fread(&info_header->ImageSize, INFOHEADER_IMAGESIZE_L, 1, self->file);
    fread(&info_header->XpixelsPerM, INFOHEADER_XPIXELSPERM_L, 1, self->file);
    fread(&info_header->YpixelsPerM, INFOHEADER_YPIXELSPERM_L, 1, self->file);
    fread(&info_header->ColorsUsed, INFOHEADER_COLORSUSED_L, 1, self->file);
    fread(&info_header->ColorsImportant, INFOHEADER_COLORSIMPORTANT_L, 1, self->file);

    info_header->OtherData = malloc(info_header->Size - 40 + 1);
    info_header->OtherData[info_header->Size - 40] = '\0';
    fread(info_header->OtherData, 1, info_header->Size - 40, self->file);

    self->info_header = info_header;
}

void BMP_calc_dimensions(BMP* self) {
    unsigned int wbits = self->info_header->Width * self->info_header->BitCount;
    unsigned int s = 32 - wbits % 32;
    self->info_header->WidthBytes = (s % 32 + wbits) / 8;    
}

void BMP_read_colorsused(BMP* self) {
    self->color_used = (unsigned char**)malloc(self->info_header->ColorsUsed * sizeof(unsigned char*));

    for (unsigned int i = 0; i < self->info_header->ColorsUsed; i++) {
        self->color_used[i] = malloc(COLOR_SIZE);
        fread(self->color_used[i], 1, COLOR_SIZE, self->file);
    }
}

void BMP_read_image(BMP* self) {
    self->image = (unsigned char**)malloc(self->info_header->Height * sizeof(unsigned char*));
    for (unsigned int i = 0; i < self->info_header->Height; i++) {
        self->image[i] = (unsigned char*)malloc(self->info_header->WidthBytes * sizeof(unsigned char) + 1);
        self->image[i][self->info_header->WidthBytes] = '\0';
        for (unsigned int j = 0; j < self->info_header->WidthBytes; j++) {
            fread(&self->image[i][j], 1, 1, self->file);
        }
    }
}

void BMP_write_fileheader(BMP* self, FILE* file);
void BMP_write_infoheader(BMP* self, FILE* file);
void BMP_write_colorsused(BMP* self, FILE* file);
void BMP_write_image(BMP* self, FILE* file);

void BMP_write(BMP* self, char* filename) {
    FILE* file = fopen(filename, "wb");
    BMP_write_fileheader(self, file);
    BMP_write_infoheader(self, file);
    BMP_write_colorsused(self, file);
    BMP_write_image(self, file);
    fclose(file);
}

void BMP_write_fileheader(BMP* self, FILE* file) {
    if (self->file_header == NULL) {
        printf("ERROR file_header = NULL\n");
        return;
    }    
    fwrite(self->file_header->Signature, 1, FILEHEADER_SIGNATURE_L, file);
    fwrite(&self->file_header->FileSize, FILEHEADER_FILESIZE_L, 1, file);
    fwrite(self->file_header->Reserved, 1, FILEHEADER_RESERVED_L, file);
    fwrite(&self->file_header->DataOffset, FILEHEADER_DATAOFFSET_L, 1, file);
}

void BMP_write_infoheader(BMP* self, FILE* file) {
    if (self->info_header == NULL) {
        printf("ERROR info_header = NULL\n");
        return;
    }

    fwrite(&self->info_header->Size, INFOHEADER_SIZE_L, 1, file);
    fwrite(&self->info_header->Width, INFOHEADER_WIDTH_L, 1, file);
    fwrite(&self->info_header->Height, INFOHEADER_HEIGHT_L, 1, file);
    fwrite(&self->info_header->Planes, INFOHEADER_PLANES_L, 1, file);
    fwrite(&self->info_header->BitCount, INFOHEADER_BITCOUNT_L, 1, file);
    fwrite(&self->info_header->Compression, INFOHEADER_COMPRESSION_L, 1, file);
    fwrite(&self->info_header->ImageSize, INFOHEADER_IMAGESIZE_L, 1, file);
    fwrite(&self->info_header->XpixelsPerM, INFOHEADER_XPIXELSPERM_L, 1, file);
    fwrite(&self->info_header->YpixelsPerM, INFOHEADER_YPIXELSPERM_L, 1, file);
    fwrite(&self->info_header->ColorsUsed, INFOHEADER_COLORSUSED_L, 1, file);
    fwrite(&self->info_header->ColorsImportant, INFOHEADER_COLORSIMPORTANT_L, 1, file);
    fwrite(self->info_header->OtherData, 1, self->info_header->Size - 40, file);
}

void BMP_write_colorsused(BMP* self, FILE* file) {
    if (self->color_used == NULL) {
        printf("ERROR color_used = NULL\n");
        return;
    }
    for (unsigned int i = 0; i < self->info_header->ColorsUsed; i++) {
        fwrite(self->color_used[i], 1, COLOR_SIZE, file);
    }
}

void BMP_write_image(BMP* self, FILE* file) {
    if (self->image == NULL) {
        printf("ERROR self->image = NULL\n");
        return;
    }
    for (unsigned int i = 0; i < self->info_header->Height; i++) {
        for (unsigned int j = 0; j < self->info_header->WidthBytes; j++) {
            // printf("%d-%d ", i, j);
            fwrite(&self->image[i][j], 1, 1, file);
        }
    }
}

void print_binary(int in);

void BITMAPFILEHEADER_print(BITMAPFILEHEADER* self) {
    printf("Signature = %s\n", self->Signature);
    printf("FileSize = %d\n", self->FileSize);
    printf("Reserved = ");
    for (int i = 0; i < FILEHEADER_RESERVED_L; i++) {
        printf("%d ", self->Reserved[i]);
    }
    printf("\n");
    printf("DataOffset = %d\n", self->DataOffset);
}

void BITMAPINFOHEADER_print(BITMAPINFOHEADER* self) {
    printf("Size = %d\n", self->Size);
    printf("Width = %d\n", self->Width);
    printf("Height = %d\n", self->Height);
    printf("Planes = %d\n", self->Planes);
    printf("BitCount = %d\n", self->BitCount);
    printf("Compression = %d\n", self->Compression);
    printf("ImageSize = %d\n", self->ImageSize);
    printf("XpixelsPerM = %d\n", self->XpixelsPerM);
    printf("YpixelsPerM = %d\n", self->YpixelsPerM);
    printf("ColorsUsed = %d\n", self->ColorsUsed);
    printf("ColorsImportant = %d\n", self->ColorsImportant);
    printf("WidthBytes = %d\n", self->WidthBytes);

    if (self->Size > 40) {
        printf("OtherData(?) = ");
        for (unsigned int i = 0; i < self->Size - 40; i++) {
            printf("%d ", self->OtherData[i]);
        }
        printf("\n");
    }
}

void BMP_print_image(BMP* self) {
    if (self->image == NULL) {
        printf("some troble with image (BMP.c 181)");
        return;
    }
    for (unsigned int i = 0; i < self->info_header->Height; i++) {
        for (unsigned int j = 0; j < self->info_header->WidthBytes; j++) {
            printf("%d ", self->image[i][j]);
        }
    }
}

void BMP_print(BMP* self) {
    printf("FILE %s\n", self->filename);
    BITMAPFILEHEADER_print(self->file_header);
    printf("\n");
    BITMAPINFOHEADER_print(self->info_header);
    printf("\n");

    // for (unsigned int i = 0; i < self->info_header->ColorsUsed; i++) {
    //     printf("%d %d %d\n", self->color_used[i][0],
    //            self->color_used[i][1], self->color_used[i][2]);
    // }

    // BMP_print_image(self);
    printf("\n");
}

void BMP_image_free(BMP* self) {
    for (unsigned int i = 0; i < self->info_header->Height; i++) {
        free(self->image[i]);
    }
    free(self->image);
    self->image = NULL;
}

void BMP_colorused_free(BMP* self) {
    for (unsigned int i = 0; i < self->info_header->ColorsUsed; i++) {
        free(self->color_used[i]);
    }
    free(self->color_used);
}

void BITMAPFILEHEADER_free(BITMAPFILEHEADER* self) {
    free(self->Signature);
    free(self->Reserved);
    free(self);
}

void BMP_free(BMP* self) {
    if (self->file != NULL)
        fclose(self->file);
    free(self->filename);
    BMP_image_free(self);
    BMP_colorused_free(self);
    BITMAPFILEHEADER_free(self->file_header);
    free(self->info_header->OtherData);
    free(self->info_header);
    free(self);
}

void print_binary(int in) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", ((in & (1 << i)) == 0 ? 0 : 1));
    }
}