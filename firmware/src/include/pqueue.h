#ifndef PQUEUE_H
#define PQUEUE_H
#include <stdint.h>
#include <stddef.h>
#include "thread.h"

// Define the PriorityQueue structure
typedef struct Process {
    ThreadID tid;
    ThreadPriority priority;
}Process;

typedef struct PriorityQueue {
    struct Process *heap;
    size_t size;
    size_t capacity;
}PriorityQueue;

struct PriorityQueue* initializePriorityQueue(size_t capacity);
void freePriorityQueue(struct PriorityQueue *pq);
void insert(struct PriorityQueue *pq, struct Process process);
struct Process extractMin(struct PriorityQueue *pq);

#endif