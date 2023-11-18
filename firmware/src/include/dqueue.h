#include "include/kernel.h"
#include <stddef.h>


typedef struct DQueueNode DQueueNode;
typedef struct PriorityQueue PriorityQueue;

typedef struct DQueue {
    DQueueNode *front;
    DQueueNode *back;

    PriorityQueue *pq;
    int size;
} DQueue;

typedef struct DQueueNode {
    struct DQueueNode *next;
    struct DQueueNode *prev;
    void *contents;
    struct DQueue *parent_queue;
} DQueueNode;

typedef struct Mutex Mutex;
typedef struct TCB TCB;

DQueue *createDQueue();
void destroyDQueue(DQueue *queue);

void initDQueue(DQueue *queue);
DQueueNode *makeDQueueNode(void *contents, DQueue *queue);
void deleteDQueueNode(DQueueNode *node);
DQueueNode *pushBack(DQueue *queue, void *object);
DQueueNode *pushFront(DQueue *queue, void *object);
void *popBack(DQueue *queue);
void *popFront(DQueue *queue);
