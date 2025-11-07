// Author: gepa1347
#ifndef BIGINT_H
#define BIGINT_H

#define RADIX 256

#define MEMORY_ALLOCATION_ERROR -1
#define ZERO_DIVISION_ERROR -2
#define INVALID_INPUT_ERROR -3

typedef struct {
    unsigned char *digits;
    int capacity;
    int digitCount;
    int isNegative;
} BigInt;

BigInt *createBigInt();
void destroyBigInt(BigInt *num);
int compare(BigInt *num1, BigInt *num2);
void resize(BigInt *num, int newSize);
BigInt *clone(BigInt *num);
int count(BigInt *num);
int isEmpty(BigInt *num);
int isFull(BigInt *num);
void makeEmpty(BigInt *num);
BigInt *add(BigInt *num1, BigInt *num2);
BigInt *sub(BigInt *num1, BigInt *num2);
BigInt *mul(BigInt *num1, BigInt *num2);
BigInt *divide(BigInt *num1, BigInt *num2);
BigInt *mod(BigInt *num1, BigInt *num2);
char *bigIntToString(BigInt *num);
BigInt *stringToBigInt(char *number);

#endif
