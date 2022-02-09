#include "../include/archivator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void Archive_make_chartree(Archive* self);
void Archive_make_wordcode(Archive* self);
void Archive_calc_arced_length(Archive* self);

ArcFile* ArcFile_init(char* filename) {
    ArcFile* arcfile = (ArcFile*)malloc(sizeof(ArcFile));
    arcfile->filename_length = strlen(filename);
    arcfile->filename = (char*)malloc(sizeof(char) * strlen(filename) + 1);
    arcfile->filename[strlen(filename)] = 0;
    arcfile->filename = strcpy(arcfile->filename, filename);

    arcfile->freq = (ull*)malloc(sizeof(ull) * 256);
    for (int i = 0; i < 256; i++) {
        arcfile->freq[i] = 0;
    }

    arcfile->actual_length = 0;
    arcfile->arced_length = 0;

    return arcfile;
}

Archive* Archive_init(int filec, char** files) {
    Archive* arc = (Archive*)malloc(sizeof(Archive));
    arc->filec = filec;
    arc->files = (ArcFile**)malloc(sizeof(ArcFile*) * filec);
    for (int i = 0; i < filec; i++) {
        arc->files[i] = ArcFile_init(files[i]);
    }
    arc->freq = (ull*)malloc(FREQNUM * sizeof(FREQTYPE));
    arc->wordmap = NULL;
    for (int i = 0; i < FREQNUM; i++) {
        arc->freq[i] = 0;
    }
    arc->archive_filename = NULL;
    Archive_make_chartree(arc);
    Archive_make_wordcode(arc);
    Archive_calc_arced_length(arc);
    for (uint i = 0; i < arc->filec; i++) {
        printf("%s: before = %lld, after = %lld\n", arc->files[i]->filename, arc->files[i]->actual_length, arc->files[i]->arced_length);
    }
    return arc;
}

void Archive_get_freq(Archive* self);
void Archive_make_tree(Archive* self);

void Archive_make_chartree(Archive* self) {
    Archive_get_freq(self);
    Archive_make_tree(self);
}

void Archive_get_freq(Archive* self) {
    for (unsigned int i = 0; i < self->filec; i++) {
        FILE* file = fopen(self->files[i]->filename, "rb");
        if (!file) {
            printf("ERROR file %s doesn't exist\n", self->files[i]->filename);
            exit(EXIT_FAILURE);
        }

        struct stat sb;
        if (stat(self->files[i]->filename, &sb) == -1) {
            perror("stat");
            exit(EXIT_FAILURE);
        }

        self->files[i]->actual_length = sb.st_size;
        size_t size = sb.st_size;
        while (size--) {
            uchar c = getc(file);
            self->files[i]->freq[c]++;
            self->freq[c]++;
        }
        fclose(file);
    }
}

void Archive_make_tree(Archive* self) {
    Queue* q = Queue_init();
    for (int i = 0; i < 256; i++) {
        if (self->freq[i]) {
            printf("%d: %lld\n", i, self->freq[i]);
            // TreeNode_print(TreeNode_init(i));
            Queue_push(q, self->freq[i], TreeNode_init(i));
        }
    }

    while (q->size > 1) {
        int lp = 0, rp = 0;
        TreeNode* left = Queue_pop(q, &lp);
        TreeNode* right = Queue_pop(q, &rp);
        TreeNode* newtree = TreeNode_push(TreeNode_init(0), left, right);
        Queue_push(q, lp + rp, newtree);
    }

    self->chartree = Queue_top(q);
    Queue_free(q);
    TreeNode_print(self->chartree);
}

void rec_make_wordcode(TreeNode* cur, WordCode cur_code, WordCode* wordmap);
void WordCode_printf(WordCode self);

void Archive_make_wordcode(Archive* self) {
    if (!self->chartree) {
        printf("ERROR, TRYING TO MAKE WordCode WITHOUT CHARTREE\n");
        exit(1);
    }

    WordCode code;
    code.code = 0;
    code.len = 0;
    self->wordmap = (WordCode*)malloc(sizeof(WordCode) * 256);
    for (int i = 0; i < 256; i++) {
        self->wordmap[i].code = 0;
        self->wordmap[i].len = 0;
    }
    rec_make_wordcode(self->chartree, code, self->wordmap);
    printf("\n\n");
    for (int i = 0; i < 256; i++) {
        if (self->wordmap[i].len > 0) {
            printf("%d: ", i);
            WordCode_printf(self->wordmap[i]);
            printf("\n");
        }
    }
}

void rec_make_wordcode(TreeNode* cur, WordCode cur_code, WordCode* wordmap) {
    if (!cur->left && !cur->right) {
        wordmap[cur->value] = cur_code;
        return;
    }

    if (cur->left) {
        cur_code.len++;
        rec_make_wordcode(cur->left, cur_code, wordmap);
        cur_code.len--;
    }
    if (cur->right) {
        cur_code.code += (1 << (cur_code.len++));
        rec_make_wordcode(cur->right, cur_code, wordmap);
    }
}

void WordCode_printf(WordCode self) {
    for (int i = 0; i < self.len; i++) {
        // printf("self->len = %d", self->len);
        printf("%d", (self.code & (1 << i)) != 0);
    }
}

void Archive_calc_arced_length(Archive* self) {
    for (uint i = 0; i < self->filec; i++) {
        for (int j = 0; j < 256; j++) {
            self->files[i]->arced_length += self->files[i]->freq[j] * self->wordmap[j].len;
        }
        self->files[i]->arced_length = (self->files[i]->arced_length + 7) / 8;
    }
}

void Archive_write_header(Archive* self, FILE* arcfile);
void Archive_write_frequency(Archive* self, FILE* arcfile);
void Archive_write_file(Archive* self, FILE* arcfile, ArcFile* file);

void Archive_fwrite(Archive* self, char* filename) {
    FILE* arcfile = fopen(filename, "wb");
    if (!arcfile) {
        printf("SOMETHING WRONG WITH OPENING THE FILE\n");
        exit(1);
    }

    Archive_write_header(self, arcfile);
    Archive_write_frequency(self, arcfile);
    for (unsigned int i = 0; i < self->filec; i++) {
        Archive_write_file(self, arcfile, self->files[i]);
    }

    fclose(arcfile);
}

void Archive_write_header(Archive* self, FILE* arcfile) {
    fwrite(ID_STR, 1, ID_LEN, arcfile);
    char version = VERSION;
    fwrite(&version, 1, 1, arcfile);
    char subversion = SUBVERSION;
    fwrite(&subversion, 1, 1, arcfile);
    fwrite(&self->filec, 4, 1, arcfile);
    int freqsize = FREQNUM * sizeof(FREQTYPE);
    fwrite(&freqsize, 4, 1, arcfile);
}

void Archive_write_frequency(Archive* self, FILE* arcfile) {
    for (int i = 0; i < FREQNUM; i++) {
        fwrite(&self->freq[i], sizeof(FREQTYPE), 1, arcfile);
    }
}

void Archive_write_file(Archive* self, FILE* arcfile, ArcFile* file) {
    fwrite(&file->arced_length, sizeof(file->arced_length), 1, arcfile);
    fwrite(&file->actual_length, sizeof(file->actual_length), 1, arcfile);
    fwrite(&file->filename_length, sizeof(file->filename_length), 1, arcfile);
    fwrite(file->filename, 1, file->filename_length, arcfile);

    uchar cur = 0, len = 0;
    FILE* infile = fopen(file->filename, "rb");
    for (ull i = 0; i < file->actual_length; i++) {
        WordCode cur_code = self->wordmap[getc(infile)];
        uchar ind = 0;
        while (ind <= cur_code.len - 1) {
            if (len >= 8) {
                // printf("\nwrite ");
                // for (int j = 0; j < len; j++) {
                //     printf("%d", (cur & (1 << j)) != 0);
                // }
                // printf("\n");
                fwrite(&cur, 1, 1, arcfile);
                cur = 0;
                len = 0;
            }
            // printf("(%d)", len);
            if ((1 << ind) & cur_code.code) {
                // printf("1");
                cur += (1 << len);
            }            
            len++;
            ind++;
        }
    }
    fwrite(&cur, 1, 1, arcfile);
    fclose(infile);
}

void Archive_read_header(Archive* self, FILE* arcfile);
void Archive_read_freq(Archive* self, FILE* arcfile);
void Archive_dearchive_files(Archive* self, FILE* arcfile);

void deArchive(char* arcfilename) {
    Archive* arc = (Archive*)malloc(sizeof(Archive));
    arc->archive_filename = arcfilename;
    arc->files = NULL;
    arc->wordmap = NULL;
    arc->chartree = NULL;    

    FILE* arcfile = fopen(arcfilename, "rb");
    Archive_read_header(arc, arcfile);
    Archive_read_freq(arc, arcfile);

    for (int i = 0; i < FREQNUM; i++) {
        if (arc->freq[i]) {
            printf("%d: %lld\n", i, arc->freq[i]);
        }
    }

    Archive_make_tree(arc);
    Archive_dearchive_files(arc, arcfile); 
    arc->archive_filename = NULL;
    Archive_free(arc);
    fclose(arcfile);
}

void Archive_read_header(Archive* self, FILE* arcfile) {
    char identifier[ID_LEN];
    fread(identifier, 1, ID_LEN, arcfile);
    for (int i = 0; i < ID_LEN; i++) {
        if (identifier[i] != ID_STR[i]) {
            printf("IT'S NOT MYARC FILE\n");
            exit(EXIT_FAILURE);
        }
    }

    uchar version, subversion;
    fread(&version, 1, 1, arcfile);
    fread(&subversion, 1, 1, arcfile);
    if (version != VERSION || subversion != SUBVERSION) {
        printf("Can't provide dearchivation for %d.%d version\n", version, subversion);
        exit(EXIT_FAILURE);
    }

    fread(&self->filec, 4, 1, arcfile);
    int freqsize;
    fread(&freqsize, 4, 1, arcfile);
    if (freqsize != FREQNUM * sizeof(FREQTYPE)) {
        printf("SOMETHING WENT WRONG. Can't provede dearchivation for this file\n");
        exit(EXIT_FAILURE);
    }
}

void Archive_read_freq(Archive* self, FILE* arcfile) {
    self->freq = (ull*)malloc(sizeof(ull) * FREQNUM);
    fread(self->freq, sizeof(ull), FREQNUM, arcfile);
}

void Archive_dearchive_file(Archive* self, FILE* arcfile, char* foldername);

void Archive_dearchive_files(Archive* self, FILE* arcfile) {
    char* foldername = (char*)malloc(strlen(self->archive_filename) + 1);
    foldername[strlen(self->archive_filename)] = 0;
    foldername = strcpy(foldername, self->archive_filename);
    int i = 0;
    while (foldername[i] != '.')
        i++;
    foldername[i] = '/';
    foldername[i + 1] = 0;
    printf("%s\n", foldername);
    mkdir(foldername, 0700);
    Archive_dearchive_file(self, arcfile, foldername);
    free(foldername);
}

void Archive_dearchive_file(Archive* self, FILE* arcfile, char* foldername) {
    self->files = (ArcFile**)malloc(sizeof(ArcFile*) * self->filec);
    for (uint i = 0; i < self->filec; i++) {        
        self->files[i] = (ArcFile*)malloc(sizeof(ArcFile));
        self->files[i]->freq = NULL;
        fread(&self->files[i]->arced_length, sizeof(ull), 1, arcfile);
        fread(&self->files[i]->actual_length, sizeof(ull), 1, arcfile);
        fread(&self->files[i]->filename_length, sizeof(uint), 1, arcfile);
        self->files[i]->filename = (char*)malloc(self->files[i]->filename_length + 1);
        for (uint j = 0; j <= self->files[i]->filename_length; j++) {
            self->files[i]->filename[j] = 0;
        }
        fread(self->files[i]->filename, 1, self->files[i]->filename_length, arcfile);
        uint filepathlen = strlen(foldername) + strlen(self->files[i]->filename) + 1;
        char* filepath = (char*)malloc(filepathlen);
        for (uint i = 0; i < filepathlen; i++) {
            filepath[i] = 0;
        }
        filepath = strcat(filepath, foldername);
        filepath = strcat(filepath, self->files[i]->filename);
        FILE* outfile = fopen(filepath, "wb");
        free(filepath);

        TreeNode* cur = self->chartree;
        uint act = 0;
        uint ind = 0;
        for (uint arc = 0; arc < self->files[i]->arced_length && act < self->files[i]->actual_length; arc++) {
            uchar c = getc(arcfile);
            ind = 0;
            while (ind < 8) {
                if (!cur->left && !cur->right) {
                    // printf(": %d\n", cur->value);
                    fwrite(&cur->value, 1, 1, outfile);
                    act++;
                    if (act >= self->files[i]->actual_length) {
                        ind = 0;
                        break;
                    }
                    cur = self->chartree;
                }
                uint bit = (uint)c & (1 << (uint)ind);
                // printf("%d", bit > 0);
                // printf("%d\n", bit);
                if (bit) {
                    cur = cur->right;
                } else {
                    cur = cur->left;
                }
                ind++;
            }
        }
        if (ind) {
            fwrite(&cur->value, 1, 1, outfile);
        }
        fclose(outfile);
    }
}

void ArcFile_free(ArcFile* self);

void Archive_free(Archive* self) {
    if (self->freq)
        free(self->freq);
    if (self->chartree)
        TreeNode_free(self->chartree);
    if (self->wordmap)
        free(self->wordmap);
    if (self->filec) {
        for (unsigned int i = 0; i < self->filec; i++) {
            ArcFile_free(self->files[i]);
        }
    }
    if (self->files) {
        free(self->files);
    }
    if (self->archive_filename) {
        free(self->archive_filename);
    }
    free(self);
}

void ArcFile_free(ArcFile* self) {
    if (self->freq) {
        free(self->freq);
    }
    free(self->filename);
    free(self);
}