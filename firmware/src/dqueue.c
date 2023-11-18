#include <stdlib.h>
#include "include/memory.h"
#include "include/dqueue.h"
#include "include/scheduler.h"
#include "include/kernel.h"

DQueue *createDQueue() {
    DQueue *queue = (DQueue *)malloc(sizeof(DQueue));
    
    if (queue != NULL) {
        initDQueue(queue);
    }
    return queue;
}

void destroyDQueue(DQueue *queue) {
    if (queue != NULL) {
        while (queue->size > 0) {
            popFront(queue);
        }
        free(queue);
    }
}

void initDQueue(DQueue *queue) {
    if (queue != NULL) {
        queue->front = NULL;
        queue->back = NULL;
        queue->pq = NULL;
        queue->size = 0;
    }
}

DQueueNode *makeDQueueNode(void *contents, DQueue *queue) {
    DQueueNode *node = (DQueueNode *)malloc(sizeof(DQueueNode));
    if (node != NULL) {
        node->next = NULL;
        node->prev = NULL;
        node->contents = contents;
        node->parent_queue = queue;
    }
    return node;
}

void deleteDQueueNode(DQueueNode *node) {
    free(node);
}

DQueueNode *pushBack(DQueue *queue, void *object) {
    DQueueNode *node = makeDQueueNode(object, queue);
    if (node != NULL) {
        if (queue->back == NULL) {
            queue->front = node;
            queue->back = node;
        } else {
            node->prev = queue->back;
            queue->back->next = node;
            queue->back = node;
        }
        queue->size++;
    }
    return node;
}

DQueueNode *pushFront(DQueue *queue, void *object) {
    DQueueNode *node = makeDQueueNode(object, queue);
    if (node != NULL) {
        if (queue->front == NULL) {
            queue->front = node;
            queue->back = node;
        } else {
            node->next = queue->front;
            queue->front->prev = node;
            queue->front = node;
        }
        queue->size++;
    }
    return node;
}

void *popBack(DQueue *queue) {
    if (queue->size == 0) {
        return NULL;
    }
    DQueueNode *node = queue->back;
    void *contents = node->contents;

    if (queue->size == 1) {
        queue->front = NULL;
        queue->back = NULL;
    } else {
        queue->back = node->prev;
        queue->back->next = NULL;
    }

    deleteDQueueNode(node);
    queue->size--;
    return contents;
}

void *popFront(DQueue *queue) {
    if (queue->size == 0) {
        return NULL;
    }
    DQueueNode *node = queue->front;
    void *contents = node->contents;

    if (queue->size == 1) {
        queue->front = NULL;
        queue->back = NULL;
    } else {
        queue->front = node->next;
        queue->front->prev = NULL;
    }

    deleteDQueueNode(node);
    queue->size--;
    return contents;
}
