// Author: ulva0857

#include "queue.h"
#include <stdlib.h>

// Sukuria tuščią eilę
Queue *create() {
    Queue *queue = malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    return queue;
}

// Sunaikina eilę ir atlaisvia atmintį
void done(Queue *queue) {
    QueueMakeEmpty(queue);
    free(queue);
}

// Grąžina eilės elementų skaičių
int QueueCount(Queue *queue) { return queue->size; }

// Patikrina ar eilė tuščia
bool QueueisEmpty(Queue *queue) { return queue->size == 0; }

// Patikrina ar eilė pilna
bool QueueisFull(Queue *queue) { return false; }

// Gauna pirmo eilės elemento duomenis, neišimant jo iš eilės
int peek(Queue *queue, bool *status) {
    if (QueueisEmpty(queue)) {
        *status = false;
        return -1;
    }
    *status = true;
    return queue->head->value;
}

// Įdeda naują elementą į eilę
void enqueue(Queue *queue, int value) {
    Node *newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    if (QueueisEmpty(queue)) {
        queue->head = newNode;
        queue->tail = newNode;
    } else {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
    queue->size++;
}

// Pašalina eilės elementą
int dequeue(Queue *queue, bool *status) {
    if (QueueisEmpty(queue)) {
        *status = false;
        return -1;
    }

    *status = true;
    int value = queue->head->value;
    Node *oldHead = queue->head;
    queue->head = queue->head->next;

    if (queue->head == NULL) {
        queue->tail = NULL;
    }

    free(oldHead);
    queue->size--;

    return value;
}

void QueueMakeEmpty(Queue *queue) {
    while (!QueueisEmpty(queue)) {
        bool status;
        dequeue(queue, &status);
    }
}
