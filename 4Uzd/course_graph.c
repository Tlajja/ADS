#include "course_graph.h"
#include <stdlib.h>
#include <string.h>

void initializeGraph(CourseGraph *graph) {
    graph->course_count = 0;
    for (int i = 0; i < MAX_COURSES; i++) {
        for (int j = 0; j < MAX_COURSES; j++) {
            graph->adjacency_matrix[i][j] = 0;
        }
    }
}

void addCourse(CourseGraph *graph, const char *name,
               const char *prerequisites) {
    int index = findCourseIndex(graph, name);
    if (index != -1)
        return;

    if (graph->course_count >= MAX_COURSES) {
        fprintf(stderr, "Error: Maximum number of courses (%d) reached\n",
                MAX_COURSES);
        return;
    }

    strncpy(graph->courses[graph->course_count].name, name,
            MAX_NAME_LENGTH - 1);
    graph->courses[graph->course_count].name[MAX_NAME_LENGTH - 1] = '\0';
    strncpy(graph->courses[graph->course_count].prerequisites, prerequisites,
            MAX_NAME_LENGTH - 1);
    graph->courses[graph->course_count].prerequisites[MAX_NAME_LENGTH - 1] =
        '\0';
    graph->course_count++;
}

int findCourseIndex(CourseGraph *graph, const char *name) {
    for (int i = 0; i < graph->course_count; i++) {
        if (strcmp(graph->courses[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void buildAdjacencyMatrix(CourseGraph *graph) {
    for (int i = 0; i < graph->course_count; i++) {
        if (strlen(graph->courses[i].prerequisites) > 0) {
            char temp[MAX_NAME_LENGTH];
            strcpy(temp, graph->courses[i].prerequisites);
            char *prereq = strtok(temp, ",");
            while (prereq != NULL) {
                // Trim leading spaces
                while (*prereq == ' ')
                    prereq++;
                int prereq_idx = findCourseIndex(graph, prereq);
                if (prereq_idx != -1) {
                    graph->adjacency_matrix[i][prereq_idx] = 1;
                }
                prereq = strtok(NULL, ",");
            }
        }
    }
}

void dfsPrerequisiteChain(CourseGraph *graph, int course_idx,
                          char prereq_chain[][MAX_NAME_LENGTH],
                          int *chain_index, int *visited) {
    if (visited[course_idx])
        return; // Prevent infinite loops

    visited[course_idx] = 1;

    // Explore ALL prerequisites recursively
    for (int i = 0; i < graph->course_count; i++) {
        if (graph->adjacency_matrix[course_idx][i]) {
            dfsPrerequisiteChain(graph, i, prereq_chain, chain_index, visited);
        }
    }

    // Add the course to the chain after all its prerequisites are processed
    strcpy(prereq_chain[*chain_index], graph->courses[course_idx].name);
    (*chain_index)++;
}

void printGraph(CourseGraph *graph, FILE *output) {
    fprintf(output, "\n%-30s %-50s\n", "Course", "Prerequisites");
    fprintf(output, "%-30s %-50s\n", "------", "-------------");
    for (int i = 0; i < graph->course_count; i++) {
        fprintf(output, "%-30s %-50s\n", graph->courses[i].name,
                strlen(graph->courses[i].prerequisites) > 0
                    ? graph->courses[i].prerequisites
                    : "None");
    }
}

void checkPrerequisites(CourseGraph *graph, const char *course, FILE *output) {
    int course_idx = findCourseIndex(graph, course);
    if (course_idx == -1) {
        fprintf(output, "\nError: Target course '%s' not found\n", course);
        return;
    }

    fprintf(output, "\nPrerequisite Path to %s:\n", course);

    // Collect all prerequisites
    char prereq_chain[MAX_COURSES][MAX_NAME_LENGTH];
    int chain_index = 0;
    int visited[MAX_COURSES] = {0};
    dfsPrerequisiteChain(graph, course_idx, prereq_chain, &chain_index,
                         visited);

    if (chain_index <= 1) {
        fprintf(output, "No prerequisites required.\n");
        return;
    }

    // Find direct prerequisites of the target course
    int direct_prereqs[MAX_COURSES];
    int direct_count = 0;
    for (int i = 0; i < graph->course_count; i++) {
        if (graph->adjacency_matrix[course_idx][i]) {
            direct_prereqs[direct_count++] = i;
        }
    }

    if (direct_count == 0) {
        fprintf(output, "No prerequisites required.\n");
        return;
    }

    // Print a chain for each direct prerequisite
    for (int i = 0; i < direct_count; i++) {
        int prereq_idx = direct_prereqs[i];
        char temp_chain[MAX_COURSES][MAX_NAME_LENGTH];
        int temp_index = 0;
        int temp_visited[MAX_COURSES] = {0};
        dfsPrerequisiteChain(graph, prereq_idx, temp_chain, &temp_index,
                             temp_visited);

        // Print the chain for this direct prerequisite
        for (int j = 0; j < temp_index; j++) {
            fprintf(output, "%s", temp_chain[j]);
            if (j < temp_index - 1) {
                fprintf(output, " -> ");
            }
        }
        fprintf(output, " -> %s\n", course);
    }

    // Print nested prerequisite chains for prerequisites with their own
    // dependencies
    for (int i = 0; i < chain_index; i++) {
        int prereq_idx = findCourseIndex(graph, prereq_chain[i]);
        if (prereq_idx == course_idx)
            continue; // Skip the target course
        if (strlen(graph->courses[prereq_idx].prerequisites) > 0) {
            char nested_chain[MAX_COURSES][MAX_NAME_LENGTH];
            int nested_index = 0;
            int nested_visited[MAX_COURSES] = {0};
            dfsPrerequisiteChain(graph, prereq_idx, nested_chain, &nested_index,
                                 nested_visited);
            if (nested_index > 1) { // Only print if there are prerequisites
                fprintf(output, "\n%s: \n", prereq_chain[i]);
                for (int j = 0; j < nested_index - 1; j++) {
                    fprintf(output, "%s", nested_chain[j]);
                    if (j < nested_index - 2) {
                        fprintf(output, " -> ");
                    }
                }
                fprintf(output, " -> %s\n", prereq_chain[i]);
            }
        }
    }
}

void printUsage(const char *programName) {
    fprintf(stderr, "Usage: %s [-|filename] target_course [-test/-t]\n",
            programName);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  filename: Read course-prerequisite pairs from file\n");
    fprintf(stderr, "  target_course: Course to check prerequisites for (e.g., "
                    "\"Optimizavimo metodai\")\n");
    fprintf(stderr, "  -test: Run built-in test cases\n");
    fprintf(stderr, "Input file format:\n");
    fprintf(stderr, "  Each line: course: prerequisite\n");
    fprintf(stderr,
            "  Use empty prerequisite for none (e.g., 'Mat. analize:')\n");
    fprintf(stderr, "  Example:\n");
    fprintf(stderr, "    Optimizavimo metodai: Mat. analize\n");
    fprintf(stderr, "    Statistika: Tikimybiu teorija\n");
    fprintf(stderr, "    Mat. analize:\n");
}

void runTestCase(FILE *output) {
    printf("\n=== Running Test Case ===\n");
    fprintf(output, "\n=== Running Test Case ===\n");

    CourseGraph graph;
    initializeGraph(&graph);

    addCourse(&graph, "Mat. analize", "");
    addCourse(&graph, "Linearine algebra", "");
    addCourse(&graph, "Optimizavimo metodai", "Mat. analize,Linearine algebra");
    addCourse(&graph, "Statistika", "Tikimybiu teorija");
    addCourse(&graph, "Tikimybiu teorija", "Mat. analize");

    buildAdjacencyMatrix(&graph);

    printGraph(&graph, stdout);
    printGraph(&graph, output);

    checkPrerequisites(&graph, "Optimizavimo metodai", stdout);
    checkPrerequisites(&graph, "Optimizavimo metodai", output);
}
