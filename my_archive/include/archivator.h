#ifndef ARCHIVATOR_H
#define ARCHIVATOR_H

#include "../include/queue.h"
#include "../include/tree.h"

#define NODE_SIZE 1 // bytes to read and make aliases 

#define ID_LEN 5
#define ID_STR "MyArc"
#define VERSION 1
#define SUBVERSION 0
#define FREQNUM 256
#define FREQTYPE ull

typedef unsigned long long ull;
typedef unsigned int uint;

typedef struct WordCode {
    uchar len;
    uint code;
} WordCode;

typedef struct ArcFile {
    ull arced_length;
    ull actual_length;
    uint filename_length;
    ull* freq;
    char* filename;
} ArcFile;

typedef struct Archive {
    uint filec;
    ArcFile** files;
    char* archive_filename;
    ull* freq;
    TreeNode* chartree;
    WordCode* wordmap;    
} Archive;

Archive* Archive_init(int filec, char** files);
void Archive_fwrite(Archive* self, char* filename);
void Archive_free(Archive* self);

void deArchive(char* arcfilename);

#endif