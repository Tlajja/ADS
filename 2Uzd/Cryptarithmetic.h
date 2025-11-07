#ifndef CRYPTARITHMETIC_H
#define CRYPTARITHMETIC_H

#include <stdio.h>

#define MAX_LETTERS 15
#define MAX_LINE 256

int solve(int pos, int used_digits[]);
int word_to_number(const char *word);
int get_value(char c);
int leading_zero_check();
void print_solution();
void read_input(FILE *input);
void run_test(const char *word1, const char *word2, const char *res);

extern char letters[MAX_LETTERS];
extern int values[MAX_LETTERS];
extern const char **words;
extern const char *result;
extern int letter_count;

#endif 
