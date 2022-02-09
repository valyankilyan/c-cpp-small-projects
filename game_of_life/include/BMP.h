#include <stdio.h>
#include <stdlib.h>

#ifndef BMP_H
#define BMP_H

#define FILEHEADER_SIGNATURE_L 2
#define FILEHEADER_FILESIZE_L 4
#define FILEHEADER_RESERVED_L 4
#define FILEHEADER_DATAOFFSET_L 4

#define INFOHEADER_SIZE_L 4
#define INFOHEADER_WIDTH_L 4
#define INFOHEADER_HEIGHT_L 4
#define INFOHEADER_PLANES_L 2
#define INFOHEADER_BITCOUNT_L 2
#define INFOHEADER_COMPRESSION_L 4
#define INFOHEADER_IMAGESIZE_L 4
#define INFOHEADER_XPIXELSPERM_L 4
#define INFOHEADER_YPIXELSPERM_L 4
#define INFOHEADER_COLORSUSED_L 4
#define INFOHEADER_COLORSIMPORTANT_L 4

#define COLOR_SIZE 4
// typedef struct color {
//     unsigned char r, g, b;
// } color;

typedef struct BITMAPFILEHEADER {
    char* Signature;
    unsigned int FileSize;
    char* Reserved;
    unsigned int DataOffset;
} BITMAPFILEHEADER;

typedef struct BITMAPINFOHEADER {
    unsigned int Size;
    unsigned int Width;
    unsigned int Height;
    unsigned int WidthBytes;    
    unsigned short int Planes;
    unsigned short int BitCount;
    unsigned int Compression;
    unsigned int ImageSize;
    unsigned int XpixelsPerM;
    unsigned int YpixelsPerM;
    unsigned int ColorsUsed;
    unsigned int ColorsImportant;
    char* OtherData;
} BITMAPINFOHEADER;

// typedef struct ColorTable {

// } ColorTable;
typedef struct BMP {
    FILE* file;
    char* filename;

    unsigned char** image;

    BITMAPFILEHEADER* file_header;
    BITMAPINFOHEADER* info_header;
    unsigned char** color_used;
} BMP;

BMP* BMP_init();
void BMP_read(BMP* self, char* filename);
void BMP_write(BMP* self, char* filename);
void BMP_print(BMP* self);
void BMP_free(BMP* self);

void BMP_calc_dimensions(BMP* self);
void BMP_image_free(BMP* self);

void BMP_from24to8(BMP* self);
void BMP_from8to1(BMP* self);

#endif