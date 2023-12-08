#include "include/queue.h"
#include "include/memory.h"
#include <stdlib.h>

void createQueue(Queue* q,int capacity) {
    q->array = (int*)malloc(sizeof(int) * capacity);
    q->capacity = capacity;
    q->front = q->rear = -1;
    q->size = 0;
    // return q;
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

// only remove the first value
int erase(Queue *q, int value) {
    if (isEmpty(q)) {
        return -1; // Queue is empty, nothing to erase.
    }

    int count = 0; // Variable to keep track of the number of occurrences erased.

    while (q->size > 0 && q->array[q->front] == value) {
        // Remove the value from the front of the queue.
        dequeue(q);
        count++;
    }

    if (isEmpty(q)) {
        return count; // Queue is now empty or had only the specified value.
    }

    // Search for the specified value in the rest of the queue.
    int index = q->front;
    while (index != q->rear) {
        index = (index + 1) % q->capacity;

        if (q->array[index] == value) {
            // Remove the value from the queue.
            for (int i = index; i != q->rear; i = (i + 1) % q->capacity) {
                q->array[i] = q->array[(i + 1) % q->capacity];
            }
            q->rear = (q->rear - 1 + q->capacity) % q->capacity;
            q->size--;
            count++;
            index--; // Check the same index again as the next element has shifted.
        }
    }

    return count;
}

void destroyQueue(Queue *q) {
    free(q->array);
    free(q);
}