#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
    int *array;
    int capacity;
    int front;
    int rear;
    int size;
} Queue;

Queue* createQueue(int capacity);
int isEmpty(Queue *q);
int isFull(Queue *q);
void enqueue(Queue *q, int value);
int dequeue(Queue *q);
// void printQueue(Queue *q);
void destroyQueue(Queue *q);

#endif /* QUEUE_H */
