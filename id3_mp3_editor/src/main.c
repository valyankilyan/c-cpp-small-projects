#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/FLL.h"
#include "../include/Frame.h"
#include "../include/ID3.h"
#include "../include/Shell.h"

ID3* open_file(ID3* id3, char* filename, int *changed);
void show_file(ID3* id3);
void add_tag(ID3* id3, char** commands);
void del_tag(ID3* id3, char* tagname);
ID3* save_file(ID3* id3, char* filename);
void close_file(ID3* id3, int* changed);
void id3_open_error();

int main() {
    char* line;
    char** commands;
    int status = 1;
    int changed = 0;
    ID3* id3 = NULL;

    do {
        printf("id3-editor");
        if (id3 != NULL) {
            printf("/%s", id3->filename);
        }
        printf("> ");
        line = Shell_read_line();
        commands = Shell_split_line(line);
        status = Shell_parse_commands(commands);

        switch (status) {
            case CNOTHING:
                continue;
                break;
            case CERROR:
                Shell_wrong_command();
                break;
            case CEXIT:
                break;
            case COPEN:
                id3 = open_file(id3, commands[1], &changed);
                break;
            case CSHOW:
                show_file(id3);
                break;
            case CADD:
                add_tag(id3, commands);
                changed = 1;
                break;
            case CDEL:
                del_tag(id3, commands[1]);
                changed = 1;
                break;
            case CSAVE:
                id3 = save_file(id3, commands[1]);
                changed = 0;
                break;
            case CCLOSE:
                close_file(id3, &changed);
                if (!changed)
                    id3 = NULL;
                break;
            case CHELP:
                Shell_get_help();
                break;
            default:
                printf("that mustn't happen.. what did u do");
                break;
        }

        free(line);
        free(commands);
    } while (status != 0);

    if (id3 != NULL)
        ID3_free(id3);
    return 0;
}

ID3* open_file(ID3* id3, char* filename, int *changed) {
    if (id3 != NULL && *changed) {
        printf("One unclosed file still here.\n");
        printf("Are you sure, you want, to open another file without saving current? [y/n]\n");
        char* line = Shell_read_line();
        char** commands = Shell_split_line(line);
        if (commands[0] == NULL || strcmp(commands[0], "y") == 0 || strcmp(commands[0], "Y") == 0) {
            printf("Okey, i'm closing the file without changing..\n");
        } else if (strcmp(commands[0], "n") == 0 || strcmp(commands[0], "N") == 0) {
            printf("Sure, you need to save file first\n");
            return id3;
        } else {
            return open_file(id3, filename, changed);
        }
    }
    *changed = 0;
    if (filename == NULL) {
        printf("Open requires filename. Use help if you don't know what are u doing.\n");
        id3 = NULL;
        return NULL;
    }
    id3 = ID3_init(filename);
    if (id3 != NULL) {
        ID3_print(id3);
    }
    return id3;
}

void show_file(ID3* id3) {
    if (id3 == NULL) {
        id3_open_error();
        return;
    }
    ID3_print(id3);
}

void add_tag(ID3* id3, char** commands) {
    if (id3 == NULL) {
        id3_open_error();
        return;
    }
    if (commands[1] == NULL) {
        printf("You didn't specify tag name. Use help.\n");
        return;
    }
    if (strlen(commands[1]) != 4) {
        printf("Tag lenght must be 4 characters.\n");
        return;
    }
    if (FLL_tagname_exists(id3->frames, commands[1])) {
        printf("Tag %s already exist. Try harder.\n", commands[1]);
        return;
    }
    if (commands[2] == NULL) {
        printf("You didn't specify data of that tag. Use help.\n");
        return;
    }

    char* data = (char*)malloc(strlen(commands[2]) + 1);
    strcpy(data, commands[2]);
    for (int i = 3; commands[i] != NULL; i++) {
        data = realloc(data, strlen(data) + strlen(commands[i]) + 2);
        strcat(data, " ");
        strcat(data, commands[i]);
    }

    Frame* frame = Frame_init();
    Frame_cpy(frame, commands[1], "\0\0", strlen(data), data);
    FLL_push(id3->frames, frame);
    printf("Added frame: %s %s\n", frame->tag, frame->data);
}

void del_tag(ID3* id3, char* tagname) {
    if (id3 == NULL) {
        id3_open_error();
        return;
    }
    if (tagname == NULL) {
        printf("You didn't specify tag name. Use help.\n");
        return;
    }
    if (strlen(tagname) != 4) {
        printf("Tag lenght must be 4 characters.\n");
        return;
    }
    FLL_delete_tagname(id3->frames, tagname);
}

ID3* save_file(ID3* id3, char* filename) {
    if (id3 == NULL) {
        id3_open_error();
        return NULL;
    }
    ID3_make_file(id3, filename);
    char* old_filename = malloc(strlen(id3->filename) + 1);
    strcpy(old_filename, id3->filename);
    ID3_free(id3);

    id3 = ID3_init(old_filename);
    free(old_filename);
    printf("File %s successfully saved.\n",
           (filename == NULL ? id3->filename : filename));
    return id3;
}

void close_file(ID3* id3, int* changed) {
    if (id3 == NULL) {
        id3_open_error();
        return;
    }
    if (*changed) {
        printf("Are you sure, you want, to close file without saving? [y/n]\n");
        char* line = Shell_read_line();
        char** commands = Shell_split_line(line);
        if (commands[0] == NULL || strcmp(commands[0], "y") == 0 || strcmp(commands[0], "Y") == 0) {
            printf("Okey, i'm closing the file without changing..\n");
        } else if (strcmp(commands[0], "n") == 0 || strcmp(commands[0], "N") == 0) {
            printf("Sure, you need to save file first\n");
            return;
        } else {
            return close_file(id3, changed);
        }
    }
    *changed = 0;
    printf("File %s closed\n", id3->filename);
    ID3_free(id3);
}

void id3_open_error() {
    printf("You didn't open the file. If you don't know what are u doing, use help.\n");
}
