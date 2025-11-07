// Author: ulva0857

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

// Mazgo struktūra
typedef struct Node {
    int value;
    struct Node *next;
} Node;

// Eilės struktūra
typedef struct {
    Node *head;
    Node *tail;
    int size;
} Queue;

// Funkcijų deklaracijos
Queue *create();
void done(Queue *queue);
int QueueCount(Queue *queue);
bool QueueisEmpty(Queue *queue);
bool QueueisFull(Queue *queue);
int peek(Queue *queue, bool *status);
void enqueue(Queue *queue, int value);
int dequeue(Queue *queue, bool *status);
Queue *QueueClone(Queue *queue);
void QueueMakeEmpty(Queue *queue);
void toString(Queue *queue);

#endif
