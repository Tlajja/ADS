#ifndef COURSE_GRAPH_H
#define COURSE_GRAPH_H

#include <stdio.h>

#define MAX_COURSES 100
#define MAX_NAME_LENGTH 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    char prerequisites[MAX_NAME_LENGTH];
} Course;

typedef struct {
    Course courses[MAX_COURSES];
    int course_count;
    int adjacency_matrix[MAX_COURSES][MAX_COURSES];
} CourseGraph;

void initializeGraph(CourseGraph *graph);
void addCourse(CourseGraph *graph, const char *name, const char *prerequisites);
int findCourseIndex(CourseGraph *graph, const char *name);
void buildAdjacencyMatrix(CourseGraph *graph);
void dfsPrerequisiteChain(CourseGraph *graph, int course_idx,
                          char prereq_chain[][MAX_NAME_LENGTH],
                          int *chain_index, int *visited);
void printGraph(CourseGraph *graph, FILE *output);
void checkPrerequisites(CourseGraph *graph, const char *course, FILE *output);
void printUsage(const char *programName);
void runTestCase(FILE *output);

#endif
