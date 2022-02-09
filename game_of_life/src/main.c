#include <string.h>
#include <time.h>

#include "../include/Field.h"

#define DEFAULT_DIR "out/"
#define DEFAULT_COUNT 100
#define DEFAULT_FREQ 0

#define ARGUMENTS_COUNT 3

#define OUTPUT 0
#define ITER 1
#define FREQ 2

char* arguments[ARGUMENTS_COUNT] = {
    "--output",
    "--max_iter",
    "--dump_freq"};

int get_argument(char* arg) {
    for (int i = 0; i < ARGUMENTS_COUNT; i++) {
        if (strcmp(arguments[i], arg) == 0) {
            return i;
        }
    }
    return -1;
}

int str_to_int(char* str) {
    int out = 0;
    for (int i = 0; i < (int)strlen(str); i++) {
        if (str[i] < '0' || str[i] > '9') {
            printf("ERROR You are suppose to put integer here");
            exit(1);
        }
        out *= 10;
        out += str[i] - '0';
    }
    return out;
}

int main(int argc, char** argv) {
    if (argc == 1) {
        printf("ERROR filename required\n");
        exit(1);
    }

    int freq = DEFAULT_FREQ;
    int count = DEFAULT_COUNT;
    char* dir = DEFAULT_DIR;

    Field* field;
    if (argc >= 3) {
        for (int i = 2; i < argc; i++) {
            int arg = get_argument(argv[i]);            
            if (argc == i + 1) {
                printf("ERROR I think you are suppose to put information after %s\n", argv[i]);
                exit(1);
            }
            switch (arg) {
                case OUTPUT:
                    dir = argv[++i];
                    break;
                case ITER:
                    count = str_to_int(argv[++i]);
                    break;
                case FREQ:
                    freq = str_to_int(argv[++i]);
                    break;
                default:
                    printf("ERROR Can't recognize argument %s\n", argv[i]);
                    break;
            };
        }
    }

    printf("GAME OF LIFE\nFREQ = %d\nITER = %d\nDIR = %s\n",
           freq, count, dir);

    field = Field_init(dir);
    Field_generate_from_file(field, argv[1]);
    // BMP_print(field->picture);

    clock_t delta = freq ? (clock_t)(1000000 / freq) : 0;
    clock_t prev_clock = clock();
    count += field->frame;
    while (field->frame < count) {        
        if (clock() - prev_clock >= delta) {            
            Field_make_turn(field);
            prev_clock = clock();
        }
    }

    Field_free(field);
    return 0;
}