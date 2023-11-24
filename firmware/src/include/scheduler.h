#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "kernel.h"
#include "pqueue.h"
#include "queue.h"
#include "thread.h"


#define MAX_QUEUE_NUM 100

typedef struct scheduler
{
    /* data */
    ThreadID next_tid;
    Queue* ready;
    // PriorityQueue* ready;
    Queue* finished;
    ThreadID current_tid;
    Queue* waiter;
}scheduler;



TStatus initScheduler(struct scheduler* schedule);

// get the tid for running
void schedule(struct scheduler* schedule);
// switch the thread's status
void switchThreadStateTo(ThreadID tid, const ThreadStatus new_state);





#endif