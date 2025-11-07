// Author: gepa1347
#include "BigInt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prints out error messages
void printError(char *errorMessage, int errorCode) {
    printf("%s\n", errorMessage);
    exit(errorCode);
}

// Creates and initializes BigInteger
BigInt *createBigInt() {
    BigInt *num = malloc(sizeof(BigInt));
    if (num == NULL)
        printError("Memory allocation error!", MEMORY_ALLOCATION_ERROR);
    num->capacity = 2;
    num->digitCount = 0;
    num->isNegative = 0;
    num->digits = calloc(num->capacity, sizeof(unsigned char));
    if (num->digits == NULL)
        printError("Memory allocation error!", MEMORY_ALLOCATION_ERROR);
    return num;
}

// Destroys BigInteger
void destroyBigInt(BigInt *num) {
    free(num->digits);
    free(num);
}

// Compares two BigIntegers, returns 1 if num1 > num2; -1 if num1 < num2; 0 if
// num1 = num2
int compare(BigInt *num1, BigInt *num2) {
    if (!num1->isNegative && num2->isNegative)
        return 1;
    if (num1->isNegative && !num2->isNegative)
        return -1;

    if (num1->digitCount > num2->digitCount)
        return num1->isNegative ? -1 : 1;
    if (num1->digitCount < num2->digitCount)
        return num1->isNegative ? 1 : -1;

    for (int i = num1->digitCount - 1; i >= 0; --i) {
        if (num1->digits[i] > num2->digits[i])
            return num1->isNegative ? -1 : 1;
        if (num1->digits[i] < num2->digits[i])
            return num1->isNegative ? 1 : -1;
    }
    return 0;
}

// Increases capacity of BigInteger array
void resize(BigInt *num, int newSize) {
    unsigned char *temp = realloc(num->digits, newSize * sizeof(unsigned char));
    if (temp == NULL)
        printError("Memory allocation error!", MEMORY_ALLOCATION_ERROR);
    memset(temp + num->digitCount, 0, newSize - num->digitCount);
    num->digits = temp;
    num->capacity = newSize;
}

// Creates and returns pointer to copy of BigInteger
BigInt *clone(BigInt *num) {
    BigInt *copy = malloc(sizeof(BigInt));
    if (copy == NULL)
        printError("Memory allocation error!", MEMORY_ALLOCATION_ERROR);
    copy->capacity = num->capacity;
    copy->digitCount = num->digitCount;
    copy->isNegative = num->isNegative;
    copy->digits = calloc(copy->capacity, sizeof(unsigned char));
    memcpy(copy->digits, num->digits, num->digitCount);
    return copy;
}

// Returns the count of digits in BigInteger number
int count(BigInt *num) { return num->digitCount; }

// Checks if BigInteger is empty
int isEmpty(BigInt *num) {
    if (count(num) == 0)
        return 1;
    else
        return 0;
}

// Checks if BigInteger is full (capacity == digitCount)
int isFull(BigInt *num) {
    if (count(num) == num->digitCount)
        return 1;
    else
        return 0;
}

// Empties number
void makeEmpty(BigInt *num) {
    num->digitCount = 0;
    num->isNegative = 0;
    num->capacity = 2;
    num->digits = realloc(num->digits, 0);
}

// Adds two BigInteger numbers and stores them as a selected base number
BigInt *addBase(BigInt *num1, BigInt *num2, int radix) {
    BigInt *copy1 = clone(num1);
    BigInt *copy2 = clone(num2);
    BigInt *sum = createBigInt();

    if (copy1->isNegative && copy2->isNegative)
        sum->isNegative = 1;

    if (copy1->isNegative) {
        copy1->isNegative = 0;
        BigInt *temp = sub(copy2, copy1);
        destroyBigInt(copy1);
        destroyBigInt(copy2);
        return temp;
    }

    if (copy2->isNegative) {
        copy2->isNegative = 0;
        BigInt *temp = sub(copy1, copy2);
        destroyBigInt(copy1);
        destroyBigInt(copy2);
        return temp;
    }

    int carry = 0;
    int maxDigits = (copy1->digitCount > copy2->digitCount) ? copy1->digitCount
                                                            : copy2->digitCount;
    for (int i = 0; i < maxDigits; ++i) {
        if (isFull(sum))
            resize(sum, sum->capacity * 2);

        int addedDigits = 0;
        if (i < copy1->digitCount)
            addedDigits += copy1->digits[i];
        if (i < copy2->digitCount)
            addedDigits += copy2->digits[i];

        addedDigits += carry;
        sum->digits[sum->digitCount++] = addedDigits % radix;
        carry = addedDigits / radix;
    }

    if (carry != 0) {
        if (isFull(sum))
            resize(sum, sum->capacity * 2);
        sum->digits[sum->digitCount++] = carry;
    }
    destroyBigInt(copy1);
    destroyBigInt(copy2);

    return sum;
}

// Addition of two BigIntegers (num1 + num2)
BigInt *add(BigInt *num1, BigInt *num2) { addBase(num1, num2, RADIX); }

// Subtraction of two BigIntegers (num1 - num2)
BigInt *sub(BigInt *num1, BigInt *num2) {
    BigInt *copy1 = clone(num1);
    BigInt *copy2 = clone(num2);

    if (copy1->isNegative && copy2->isNegative) {
        destroyBigInt(copy1);
        destroyBigInt(copy2);
        return sub(num2, num1);
    }

    BigInt *result = createBigInt();
    if (copy1->isNegative && !copy2->isNegative) {
        copy1->isNegative = 0;
        destroyBigInt(result);
        result = add(copy1, copy2);
        result->isNegative = 1;
        destroyBigInt(copy1);
        destroyBigInt(copy2);
        return result;
    }

    if (!copy1->isNegative && copy2->isNegative) {
        copy2->isNegative = 0;
        BigInt *temp = add(copy1, copy2);
        destroyBigInt(copy1);
        destroyBigInt(copy2);
        return temp;
    }

    if (compare(copy1, copy2) == -1) {
        result->isNegative = 1;
        BigInt *temp = copy1;
        copy1 = copy2;
        copy2 = temp;
    }

    int borrow = 0;
    for (int i = 0; i < copy1->digitCount; ++i) {
        if (isFull(result))
            resize(result, result->capacity * 2);

        int difference =
            copy1->digits[i] - (i < copy2->digitCount ? copy2->digits[i] : 0);
        difference -= borrow;
        borrow = 0;
        if (difference < 0) {
            difference += RADIX;
            borrow = 1;
        }

        result->digits[result->digitCount++] = difference;
    }
    while (result->digitCount > 1 &&
           result->digits[result->digitCount - 1] == 0)
        result->digitCount--;

    destroyBigInt(copy1);
    destroyBigInt(copy2);
    return result;
}

// Multiplies two BigIntegers and stores them as selected base number
BigInt *mulBase(BigInt *num1, BigInt *num2, int radix) {
    BigInt *prod = createBigInt();

    for (int i = 0; i < num1->digitCount; ++i) {
        BigInt *tempProd = createBigInt();
        resize(tempProd, i + 1);
        tempProd->digitCount = i;
        int remainder = 0;

        for (int j = 0; j < num2->digitCount; ++j) {
            if (isFull(tempProd))
                resize(tempProd, tempProd->capacity * 2);
            int product = (int)num1->digits[i] * num2->digits[j];
            product += remainder;
            tempProd->digits[tempProd->digitCount++] = product % radix;
            remainder = product / radix;
        }
        if (remainder != 0) {
            if (tempProd->digitCount == tempProd->capacity)
                resize(tempProd, tempProd->capacity * 2);
            tempProd->digits[tempProd->digitCount++] = remainder;
        }

        prod = add(prod, tempProd);
        destroyBigInt(tempProd);
    }
    prod->isNegative = num1->isNegative ^ num2->isNegative;
    return prod;
}

// Multiplication of two BigIntegers (num1 * num2)
BigInt *mul(BigInt *num1, BigInt *num2) { mulBase(num1, num2, RADIX); }

// Division algorithm of two BigIntegers
BigInt *division(BigInt *num1, BigInt *num2, int mod) {
    if (num2->digitCount == 1 && num2->digits[0] == 0)
        printError("Division by zero error!", ZERO_DIVISION_ERROR);

    BigInt *copy1 = clone(num1);
    BigInt *copy2 = clone(num2);
    BigInt *quotient = createBigInt();
    BigInt *remainder = createBigInt();

    quotient->isNegative = copy1->isNegative ^ copy2->isNegative;

    copy1->isNegative = 0, copy2->isNegative = 0;
    int i = copy1->digitCount - 1;
    while (i >= 0) {
        int notEnoughLeft = 0;
        BigInt *base = createBigInt();
        base->digitCount = 2;
        base->digits[0] = 0;
        base->digits[1] = 1;

        BigInt *num = createBigInt();
        num->digitCount = 1;
        while (compare(remainder, copy2) == -1) {
            if (i < 0) {
                notEnoughLeft = 1;
                break;
            }

            num->digits[0] = copy1->digits[i];
            remainder = add(mul(remainder, base), num);
            --i;
        }
        if (notEnoughLeft)
            break;

        int times = 1;
        BigInt *subtract = clone(copy2);

        while (compare(subtract, remainder) != 1) {
            subtract = add(subtract, copy2);
            ++times;
        }

        num->digits[0] = times - 1;
        quotient = add(mul(quotient, base), num);
        remainder = add(sub(remainder, subtract), copy2);
        destroyBigInt(subtract);
        destroyBigInt(base);
        destroyBigInt(num);
    }
    destroyBigInt(copy1);
    destroyBigInt(copy2);
    if (mod)
        return remainder;
    else
        return quotient;
}

// Returns result of division of two BigIntegers (num1 / num2)
BigInt *divide(BigInt *num1, BigInt *num2) { return division(num1, num2, 0); }

// Returns modulo of division of two BigIntegers (num1 % num2)
BigInt *mod(BigInt *num1, BigInt *num2) { return division(num1, num2, 1); }

// Converts BigInteger to string for output
char *bigIntToString(BigInt *num) {
    BigInt *baseTenNum = createBigInt();
    BigInt *multiplier = createBigInt();
    BigInt *times256 = createBigInt();
    multiplier->digits[multiplier->digitCount++] = 1;
    resize(times256, 3);
    times256->digits[times256->digitCount++] = 6;
    times256->digits[times256->digitCount++] = 5;
    times256->digits[times256->digitCount++] = 2;
    for (int i = 0; i < num->digitCount; i++) {
        BigInt *numberFromDig = createBigInt();
        resize(numberFromDig, 3);
        int temp = num->digits[i];
        while (temp != 0) {
            numberFromDig->digits[numberFromDig->digitCount++] = temp % 10;
            temp /= 10;
        }
        BigInt *a = mulBase(multiplier, numberFromDig, 10);

        baseTenNum = addBase(baseTenNum, a, 10);
        multiplier = mulBase(multiplier, times256, 10);
        destroyBigInt(numberFromDig);
    }
    int sign = num->isNegative;
    char *converted = malloc(baseTenNum->digitCount + 1 + sign * sizeof(char));
    if (converted == NULL)
        printError("Memory allocation error!", MEMORY_ALLOCATION_ERROR);
    if (sign)
        converted[0] = '-';
    for (int i = baseTenNum->digitCount - 1; i >= 0; i--)
        converted[baseTenNum->digitCount - 1 - i + sign] =
            baseTenNum->digits[i] + '0';

    converted[baseTenNum->digitCount + sign] = '\0';
    return converted;
}

// Converts string to BigInteger
BigInt *stringToBigInt(char *number) {
    BigInt *bigInt = createBigInt();
    int i = 0;
    if (number[0] == '-')
        i = 1;
    BigInt *base = createBigInt();
    base->digitCount = 1;
    base->digits[0] = 10;
    for (i; number[i] != '\0'; i++) {
        if (number[i] > '9' || number[i] < '0') {
            destroyBigInt(bigInt);
            printError("Invalid input error!", INVALID_INPUT_ERROR);
        }
        BigInt *digit = createBigInt();
        digit->digitCount = 1;
        digit->digits[0] = number[i] - '0';
        bigInt = add(mul(bigInt, base), digit);
        destroyBigInt(digit);
    }
    if (number[0] == '-')
        bigInt->isNegative = 1;
    destroyBigInt(base);

    return bigInt;
}
