#ifndef BANK_H
#define BANK_H

#include "BigInt.h"
#include "queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int simulationTime;
    int numTellers;
    int arrivalProbability;
    int maxServiceTime;
    int randomSeed;
} Params;

typedef struct {
    int isBusy;
    int remainingTime;
    BigInt *customersServed;
    BigInt *totalServiceTime;
} Teller;

typedef struct {
    BigInt *totalCustomers;
    BigInt *maxQueueSize;
    BigInt *totalWaitingTime;
    BigInt *maxWaitingTime;
    BigInt *customersWithWait;
} Stats;

Params readParams(FILE *input);
void printUsage(char *programName);
void initTellers(Teller *tellers, int numTellers);
void simulateBank(Params params);
#endif
