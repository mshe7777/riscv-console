#include "include/queue.h"
#include "include/memory.h"
#include <stdlib.h>

Queue* createQueue(int capacity) {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->array = (int*)malloc(sizeof(int) * capacity);
    q->capacity = capacity;
    q->front = q->rear = -1;
    q->size = 0;
    return q;
}

int isEmpty(Queue *q) {
    return q->size == 0;
}

int isFull(Queue *q) {
    return q->size == q->capacity;
}

void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        // printf("Queue is full. Cannot enqueue.\n");
        return;
    }

    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % q->capacity;
    }

    q->array[q->rear] = value;
    q->size++;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) {
        // printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    }

    int value = q->array[q->front];

    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % q->capacity;
    }

    q->size--;

    return value;
}


void destroyQueue(Queue *q) {
    free(q->array);
    free(q);
}