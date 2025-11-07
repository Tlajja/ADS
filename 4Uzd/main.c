#include "course_graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    FILE *output = fopen("results.txt", "w");
    if (!output) {
        fprintf(stderr, "Error: Could not create results.txt\n");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-test") == 0 || strcmp(argv[1], "-t") == 0) {
        if (argc != 2) {
            fprintf(stderr,
                    "Error: -test or -t requires no additional arguments\n");
            printUsage(argv[0]);
            fclose(output);
            return EXIT_FAILURE;
        }
        runTestCase(output);
        fclose(output);
        return EXIT_SUCCESS;
    }

    if (argc != 3) {
        fprintf(stderr,
                "Error: Standard mode requires filename and target course\n");
        printUsage(argv[0]);
        fclose(output);
        return EXIT_FAILURE;
    }

    char *filename = argv[1];
    char *target_course = argv[2];

    FILE *input = fopen(filename, "r");
    if (!input) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        fprintf(output, "Error: Could not open file %s\n", filename);
        printUsage(argv[0]);
        fclose(output);
        return EXIT_FAILURE;
    }

    CourseGraph graph;
    initializeGraph(&graph);

    char line[256];
    while (fgets(line, sizeof(line), input)) {
        char *name = strtok(line, ":");
        char *prereqs = strtok(NULL, "\n");
        if (name) {
            name[strcspn(name, "\r\n")] = 0;
            if (prereqs) {
                prereqs[strcspn(prereqs, "\r\n")] = 0;
                while (*prereqs == ' ')
                    prereqs++;
            } else {
                prereqs = "";
            }
            addCourse(&graph, name, prereqs);
        }
    }
    fclose(input);

    buildAdjacencyMatrix(&graph);

    printf("\n=== Course Prerequisites ===\n");
    fprintf(output, "\n=== Course Prerequisites ===\n");
    printGraph(&graph, stdout);
    printGraph(&graph, output);

    checkPrerequisites(&graph, target_course, stdout);
    checkPrerequisites(&graph, target_course, output);

    fclose(output);
    return EXIT_SUCCESS;
}
