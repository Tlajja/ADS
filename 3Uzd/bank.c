#include "bank.h"
#include "queue.h"

// Helper function to create a BigInt from int
BigInt *intToBigInt(int value) {
    char buffer[20];
    sprintf(buffer, "%d", value);
    return stringToBigInt(buffer);
}

void printUsage(char *programName) {
    printf("Usage: %s [params_file] [-rnd seed]\n", programName);
    printf("Options:\n");
    printf("  params_file : Read parameters from specified file (default: "
           "params.txt)\n");
    printf("  -rnd (seed) : Set random seed (default: current time)\n");
    printf(
        "  -t          : Run test with default parameters (500 5 50 40 10)\n");
    printf("If no arguments are provided, uses default params\n");
    printf("Input format:\n");
    printf("simulationTime numTellers arrivalProbability maxServiceTime");
}

Params readParams(FILE *input) {
    // Default Stats
    Params params = {500, 5, 50, 10, time(NULL)};
    if (input) {
        fscanf(input, "%d", &params.simulationTime);
        fscanf(input, "%d", &params.numTellers);
        fscanf(input, "%d", &params.arrivalProbability);
        fscanf(input, "%d", &params.maxServiceTime);
    }
    return params;
}

void initTellers(Teller *tellers, int numTellers) {
    for (int i = 0; i < numTellers; i++) {
        tellers[i].isBusy = 0;
        tellers[i].remainingTime = 0;
        tellers[i].customersServed = intToBigInt(0);
        tellers[i].totalServiceTime = intToBigInt(0);
    }
}

void simulateBank(Params params) {
    Queue *queue = create();
    Teller tellers[params.numTellers];

    // Initialize stats with BigInt
    Stats stats;
    stats.totalCustomers = intToBigInt(0);
    stats.maxQueueSize = intToBigInt(0);
    stats.totalWaitingTime = intToBigInt(0);
    stats.maxWaitingTime = intToBigInt(0);
    stats.customersWithWait = intToBigInt(0);

    initTellers(tellers, params.numTellers);
    srand(params.randomSeed);

    // Customer arrival
    for (int minute = 0; minute < params.simulationTime; minute++) {
        // Customer arrival
        if (rand() % 100 < params.arrivalProbability) {
            enqueue(queue, minute);
            BigInt *one = intToBigInt(1);
            BigInt *newTotal = add(stats.totalCustomers, one);
            destroyBigInt(stats.totalCustomers);
            stats.totalCustomers = newTotal;
            destroyBigInt(one);

            int currentSize = QueueCount(queue);
            BigInt *currentSizeBig = intToBigInt(currentSize);
            if (compare(currentSizeBig, stats.maxQueueSize) > 0) {
                destroyBigInt(stats.maxQueueSize);
                stats.maxQueueSize = clone(currentSizeBig);
            }
            destroyBigInt(currentSizeBig);
        }

        // Processing tellers
        for (int i = 0; i < params.numTellers; i++) {
            if (tellers[i].isBusy) {
                tellers[i].remainingTime--;
                if (tellers[i].remainingTime == 0) {
                    tellers[i].isBusy = 0;
                }
                continue;
            }

            // Assign customer if available
            if (!QueueisEmpty(queue)) {
                bool status;
                int readyTime = dequeue(queue, &status);
                if (minute >= readyTime) { // Customer is ready
                    int waitTime = minute - readyTime;
                    BigInt *waitTimeBig = intToBigInt(waitTime);
                    BigInt *newTotalWait =
                        add(stats.totalWaitingTime, waitTimeBig);
                    destroyBigInt(stats.totalWaitingTime);
                    stats.totalWaitingTime = newTotalWait;

                    BigInt *one = intToBigInt(1);
                    BigInt *newCustomersWithWait =
                        add(stats.customersWithWait, one);
                    destroyBigInt(stats.customersWithWait);
                    stats.customersWithWait = newCustomersWithWait;
                    destroyBigInt(one);

                    if (compare(waitTimeBig, stats.maxWaitingTime) > 0) {
                        destroyBigInt(stats.maxWaitingTime);
                        stats.maxWaitingTime = clone(waitTimeBig);
                    }
                    destroyBigInt(waitTimeBig);

                    int serviceTime = rand() % params.maxServiceTime + 1;
                    tellers[i].isBusy = true;
                    tellers[i].remainingTime = serviceTime;

                    // Update teller stats with BigInt
                    BigInt *served = tellers[i].customersServed;
                    BigInt *newServed = add(served, intToBigInt(1));
                    destroyBigInt(tellers[i].customersServed);
                    tellers[i].customersServed = newServed;

                    BigInt *service = tellers[i].totalServiceTime;
                    BigInt *newService = add(service, intToBigInt(serviceTime));
                    destroyBigInt(tellers[i].totalServiceTime);
                    tellers[i].totalServiceTime = newService;
                } else {
                    enqueue(queue, readyTime); // Not ready yet
                }
            }
        }
    }

    // Print parameters used
    printf("Parameters:\n");
    printf("Simulation time: %d\n", params.simulationTime);
    printf("Number of tellers: %d\n", params.numTellers);
    printf("Arrival probability: %d%%\n", params.arrivalProbability);
    printf("Max service time: %d\n", params.maxServiceTime);

    // Calculate and print results
    printf("\nSimulation Results:\n");
    char *totalCustomersStr = bigIntToString(stats.totalCustomers);
    printf("- Total customers: %s\n",
           totalCustomersStr ? totalCustomersStr : "0");
    if (totalCustomersStr)
        free(totalCustomersStr);

    printf("- Customers served per teller:");
    for (int i = 0; i < params.numTellers; i++) {
        char *servedStr = bigIntToString(tellers[i].customersServed);
        printf(" %s", servedStr ? servedStr : "0");
        if (servedStr)
            free(servedStr);
    }
    printf("\n");

    // Calculate average waiting time
    if (compare(stats.customersWithWait, intToBigInt(0)) > 0) {
        // First convert BigInts to integers for simpler division
        char *totalWaitStr = bigIntToString(stats.totalWaitingTime);
        char *customersWaitStr = bigIntToString(stats.customersWithWait);

        if (totalWaitStr && customersWaitStr) {
            int totalWait = atoi(totalWaitStr);
            int customersWait = atoi(customersWaitStr);

            if (customersWait > 0) {
                float avgWait = (float)totalWait / customersWait;
                printf("- Average waiting time: %.2f\n", avgWait);
            } else {
                printf("- Average waiting time: 0 (no valid waiters)\n");
            }
        } else {
            printf("- Average waiting time: N/A (calculation error)\n");
        }

        if (totalWaitStr)
            free(totalWaitStr);
        if (customersWaitStr)
            free(customersWaitStr);
    } else {
        printf("- Average waiting time: 0 (no customers had to wait)\n");
    }
    char *maxWaitStr = bigIntToString(stats.maxWaitingTime);
    printf("- Maximum waiting time: %s\n", maxWaitStr ? maxWaitStr : "0");
    if (maxWaitStr)
        free(maxWaitStr);

    char *maxQueueStr = bigIntToString(stats.maxQueueSize);
    printf("- Maximum queue size: %s\n", maxQueueStr ? maxQueueStr : "0");
    if (maxQueueStr)
        free(maxQueueStr);

    // Calculate teller utilization using double for better precision
    printf("- Teller utilization:\n");
    for (int i = 0; i < params.numTellers; i++) {
        char *serviceStr = bigIntToString(tellers[i].totalServiceTime);
        double serviceTime = serviceStr ? atof(serviceStr) : 0.0;
        if (serviceStr)
            free(serviceStr);

        double utilization = (serviceTime / params.simulationTime) * 100.0;
        printf("  Teller %d: %.1f%%\n", i + 1, utilization);
    }

    // Clean up BigInt allocations
    done(queue);
    destroyBigInt(stats.totalCustomers);
    destroyBigInt(stats.maxQueueSize);
    destroyBigInt(stats.totalWaitingTime);
    destroyBigInt(stats.maxWaitingTime);
    destroyBigInt(stats.customersWithWait);

    for (int i = 0; i < params.numTellers; i++) {
        destroyBigInt(tellers[i].customersServed);
        destroyBigInt(tellers[i].totalServiceTime);
    }
}
