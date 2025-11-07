#include <stdio.h>
#include <string.h>
#include "Cryptarithmetic.h"

int main(int argc, char *argv[]) {

    FILE *input = stdin; // By default it uses standart input
    if (argc > 1) {
        if (strcmp(argv[1], "-") != 0) {
            input = fopen(argv[1], "r");
            if (!input) {
                fprintf(stderr, "Klaida: nepavyko atidaryti failo %s\n", argv[1]);
                return 1;
            }
        }
    } else {
        FILE *default_file = fopen("data.txt", "r");
        if (default_file) {
            input = default_file; // If "duom.txt" exists, it uses it
        }
    }
    read_input(input);
    if (input != stdin) {
        fclose(input);
    }

    return 0;
}
