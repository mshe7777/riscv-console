#include "include/pqueue.h"
#include "include/memory.h"
#include <stdlib.h>



struct PriorityQueue* initializePriorityQueue(size_t capacity) {
    struct PriorityQueue *pq = (struct PriorityQueue*)kmalloc(sizeof(struct PriorityQueue));
    pq->heap = (struct Process*)kmalloc((capacity + 1) * sizeof(struct Process)); // Index starts from 1
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void freePriorityQueue(struct PriorityQueue *pq) {
    free(pq->heap);
    free(pq);
}

void insert(struct PriorityQueue *pq, struct Process process) {
    if (pq->size == pq->capacity) {
        // printf("Priority queue is full. Cannot insert.\n");
        return;
    }

    pq->size++;
    pq->heap[pq->size] = process;

    size_t i = pq->size;
    while (i > 1 && pq->heap[i].priority < pq->heap[i / 2].priority) {
        struct Process temp = pq->heap[i];
        pq->heap[i] = pq->heap[i / 2];
        pq->heap[i / 2] = temp;
        i /= 2;
    }
}

struct Process extractMin(struct PriorityQueue *pq) {
    if (pq->size == 0) {
        // printf("Priority queue is empty. Returning invalid process.\n");
        return (struct Process){-1, -1};
    }

    struct Process minProcess = pq->heap[1];
    pq->heap[1] = pq->heap[pq->size];
    pq->size--;

    size_t i = 1;
    while (1) {
        size_t leftChild = 2 * i;
        size_t rightChild = 2 * i + 1;
        size_t smallest = i;

        if (leftChild <= pq->size && pq->heap[leftChild].priority < pq->heap[smallest].priority) {
            smallest = leftChild;
        }
        if (rightChild <= pq->size && pq->heap[rightChild].priority < pq->heap[smallest].priority) {
            smallest = rightChild;
        }

        if (smallest != i) {
            struct Process temp = pq->heap[i];
            pq->heap[i] = pq->heap[smallest];
            pq->heap[smallest] = temp;
            i = smallest;
        } else {
            break;
        }
    }

    return minProcess;
}