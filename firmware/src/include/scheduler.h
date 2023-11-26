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
extern struct scheduler* sched;


TStatus initScheduler(struct scheduler* schedule);

// switch the thread's status
void switchThreadStateTo(scheduler* schedule,const ThreadStatus new_state);
void interruptSwicth(scheduler* schedule);
void yield(scheduler* schedule);
void suspend(scheduler* schedule);
void kexit(scheduler* schedule);
void resume(scheduler* schedule, ThreadID tid);



void startFirstThread(scheduler* schedule);







#endif