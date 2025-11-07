#include "Cryptarithmetic.h"
#include <stdio.h>
#include <string.h>


char letters[MAX_LETTERS];       
int values[MAX_LETTERS];         
int letter_count;                
const char **words;            
const char *result;              

int get_value(char c) {
    for (int i = 0; i < letter_count; i++) {
        if (letters[i] == c) return values[i];
    }
    return -1;
}

int word_to_number(const char *word) {
    long num = 0;
    while (*word) {
        num = num * 10 + get_value(*word);
        word++;
    }
    return num;
}

int leading_zero_check() {
    for (int i = 0; i < 2; i++) {
        if (get_value(words[i][0]) == 0) return 0;
    }
    if (get_value(result[0]) == 0) return 0;
    return 1;
}

void print_solution() {
    printf("\nSprendinys:\n");
    for (int i = 0; i < letter_count; i++) {
        printf("%c = %d,  ", letters[i], values[i]);
    }
    printf("\n\n");

    int max_len = strlen(result);

    for (int i = 0; i < 2; i++) {
        int word_len = strlen(words[i]);
        int spaces = max_len - word_len;
        printf("  ");

        for (int s = 0; s < spaces; s++)
            printf(" ");
        printf("%s\n  ", words[i]);
        
        for (int s = 0; s < spaces; s++)
            printf(" ");
        
        for (int j = 0; j < word_len; j++) {
            printf("%d", get_value(words[i][j]));
        }
        if(i == 0)
            printf("\n+\n");
        else
            printf("\n");
    }
    
        
    for (int i = 0; i < max_len + 2; i++)
        printf("-");
    printf("\n  %s\n  ", result);
    
    for (int i = 0; i < strlen(result); i++) {
        printf("%d", get_value(result[i]));
    }
    
    printf("\n");
}

int solve(int pos, int used_digits[]) { 
    // pos - position in letters[], shows which letter is currently being considered
    // used_digits[] - tracks which digits are already used

    if (pos == letter_count) {
        if (!leading_zero_check())
            return 0;

        long sum = word_to_number(words[0]) + word_to_number(words[1]);

        if (sum == word_to_number(result)) {
            print_solution();
            return 1;
        }

        return 0;
    }
    
    // Finding the digits by recursion using bactracking
    // It tries all different digits for a letter and if it doesnt't
    // find a solution it bactracks to the previous iteration
    for (int digit = 0; digit <= 9; digit++) {
        if (!used_digits[digit]) {  // If the digit is not used
            used_digits[digit] = 1;  // Mark it as used
            values[pos] = digit;
            if (solve(pos + 1, used_digits))  // Recurse with the updated used_digits
                return 1;
            used_digits[digit] = 0;  // Backtrack: mark the digit as unused
        }
    }
    return 0;
}

void read_input(FILE *input) {
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), input)) {
        char word1[MAX_LINE], word2[MAX_LINE], result[MAX_LINE];
        if (sscanf(line, "%s %s %s", word1, word2, result) == 3) {
            printf("Word1: %s, Word2: %s, Result: %s\n", word1, word2, result);
                run_test(word1, word2, result);
        } else {
            fprintf(stderr, "Neteisingas įvesties formatas: %s", line);
        }
    }
}

void run_test(const char *word1, const char *word2, const char *res) {
    words = (const char *[]){word1, word2};
    result = res;
    letter_count = 0;
    int used_letters[26] = {0};
    int used_digits[10] = {0};
    
    // Finding unique letters
    for (int i = 0; i < 2; i++) {
        for (const char *p = words[i]; *p; p++) {
            if (!used_letters[*p - 'A']) {
                letters[letter_count++] = *p;
                used_letters[*p - 'A'] = 1;
            }
        }
    }

    for (const char *p = result; *p; p++) {
        if (!used_letters[*p - 'A']) {
            letters[letter_count++] = *p;
            used_letters[*p - 'A'] = 1;
        }
    }
    
    // Printing the Cryptarithm Problem 
    printf("\n%s\n+\n%s\n----------\n%s\n\n", word1, word2, res);
    if (letter_count > MAX_LETTERS) {
        printf("Per daug raidžių (daugiau nei %d).\n", MAX_LETTERS);
        return;
    }
    // Printing the solution or lack thereof
    if (!solve(0, used_digits)) {
        printf("Sprendinio nerasta.\n");
    }

    printf("===================\n");
}
