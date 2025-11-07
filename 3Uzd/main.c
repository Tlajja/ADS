#include "bank.h"

Params setDefaults() {
    Params defaults = {500, 5, 50, 10, time(NULL)};
    return defaults;
}

int main(int argc, char *argv[]) {
    Params params;
    FILE *input = NULL;
    int useDefaults = 0;
    int randomSeed = time(NULL);
    char *filename = "params.txt";

    // Parse command line arguments
    if (argc == 1) {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    } else {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-t") == 0) {
                useDefaults = 1;
            } else if (strcmp(argv[i], "-rnd") == 0 && i + 1 < argc) {
                randomSeed = atoi(argv[++i]);
            } else {
                filename = argv[i];
            }
        }
    }

    if (useDefaults) {
        params = setDefaults();
    } else {
        // Try to open input file
        input = fopen(filename, "r");
        if (!input && argc > 1 && strcmp(argv[1], "-rnd") != 0 &&
            strcmp(argv[1], "-t") != 0) {
            fprintf(stderr, "Error: Could not open file %s\n", filename);
            printUsage(argv[0]);
            return EXIT_FAILURE;
        }
        params = readParams(input);
        if (input)
            fclose(input);
    }
    params.randomSeed = randomSeed;

    simulateBank(params);

    return 0;
}
