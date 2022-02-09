#include "../include/Shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

static char *commands[COMMANDS_SIZE] = {
    "exit",
    "open",
    "show",
    "add",
    "delete",
    "save",
    "close",
    "help"
};

static char *commands_description[COMMANDS_SIZE] = {
    "Exit from subshell and from program as well",
    "Open mp3 file. You should write > open <filename>",
    "Show all tags we found",
    "Add tag to the file > add <tag_name> <tag_data>",
    "Delete tag > delete <tag_name>",
    "Save file > save || > save <new_filename>",
    "Close file with current tags",
    "Get help.."
};

static char *help = "\
It's a program that helps you edit tags in mp3 file\n\
there are some commands that will help you with it:\n";

char *Shell_read_line() {
    int bufsize = BUFSIZE;
    int pos = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    while (1) {        
        c = getchar();
        if (c == EOF || c == '\n') {
            buffer[pos] = '\0';
            return buffer;
        } else {
            buffer[pos] = c;
        }
        pos++;
    }
}

char **Shell_split_line(char *line) {
    int bufsize = TOK_BUFSIZE, pos = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    token = strtok(line, TOK_DELIM);
    while (token != NULL) {
        tokens[pos] = token;
        pos++;

        if (pos >= bufsize) {
            bufsize += TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
        }
        token = strtok(NULL, TOK_DELIM);
    }
    tokens[pos] = NULL;    
    return tokens;
}

int Shell_parse_commands(char **args) {
    if (args[0] == NULL)
        return CNOTHING;
    
    for (int i = 0; i < COMMANDS_SIZE; i++) {
        if (strcmp(args[0], commands[i]) == 0) {
            return i;
        }
    }
    return CERROR;
}

void Shell_wrong_command() {
    printf("I think, u wrote wrong command, try again.\n");
}

void Shell_get_help() {
    printf("%s\n", help);
    for (int i = 0; i < COMMANDS_SIZE; i++) {
        printf("%s - %s\n", commands[i], commands_description[i]);
    }
}

// int Shell_parse(char *)