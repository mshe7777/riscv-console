#ifndef CONDITION_H
#define CONDITION_H


#include <stdint.h>
#include "kernel.h"
#include "thread.h"
#include "queue.h"
#include "scheduler.h"
#include "mutex.h"



#define MAX_COND_NUM 10
#define INVALD_COND_ID -1
typedef struct ConditionVariable{
    CondID cond_id;
    Queue* waiting_list;
}ConditionVariable;

extern CondID global_cond_id;
extern struct ConditionVariable** condArray;

// function

void wait(MutexId mid,scheduler* schedule, ConditionVariable* cond);
void wait_(MutexId mid,scheduler* schedule, CondID cond_id);
void notifyOne(scheduler* schedule,ConditionVariable* cond);
void notifyAll_(scheduler* schedule,CondID cond_id);
void notifyAll(scheduler* schedule,ConditionVariable* cond);

CondID condCreate();





// system call
CondID createCond();
TStatus destoryCond(CondID cond_id);
TStatus condWait(CondID cond_id,MutexId mutex_id);
TStatus condSignal(CondID cond_id);
TStatus condBroadcast(CondID cond_id);



#endif