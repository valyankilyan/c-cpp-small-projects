#include "../include/archivator.h"
#include "../include/queue.h"
#include "../include/tree.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {    


    if (argc <= 2) {
        printf("Inapropriate way of executing.\n");
        exit(1);
    }

    if (strcmp(argv[1], "-a") == 0){
        char* files[argc - 2];
        for (int i = 2; i < argc; i++) {
            files[i - 2] = argv[i];
            Archive* arc = Archive_init(argc - 2, files);
            Archive_fwrite(arc, "out.arc");
            return 0;
        }
    } else if (strcmp(argv[1], "-d") == 0) {
        char* arcname = argv[2];
        deArchive(arcname);
        return 0;
    } else {
        printf("You suppose to write either -a or -d");
        exit(1);
    }

    return 0;
}