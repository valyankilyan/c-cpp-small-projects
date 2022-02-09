#ifndef SHELL_H
#define SHELL_H

#define COMMANDS_SIZE 8
#define CNOTHING -2
#define CERROR -1
#define CEXIT 0
#define COPEN 1
#define CSHOW 2
#define CADD 3
#define CDEL 4
#define CSAVE 5
#define CCLOSE 6
#define CHELP 7


char *Shell_read_line();
char **Shell_split_line(char *line);
int Shell_parse_commands(char **args);
void Shell_wrong_command();
void Shell_get_help();

#endif