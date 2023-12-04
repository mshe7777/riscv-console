#include "include/condition.h"
#include "include/mutex.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>



CondID global_cond_id=0;
void wait(MutexId mid,scheduler* schedule,ConditionVariable* cond){
    mutexRelease(schedule,mutexArray[mid]);
    enqueue(cond->waiting_list,schedule->current_tid);
    suspend(schedule);
    mutexLock(schedule,mutexArray[mid]);
}

void wait_(MutexId mid,scheduler* schedule, CondID cond_id){
    if(cond_id==INVALD_COND_ID){
        return;
    }
    ConditionVariable* cond=condArray[cond_id];
    wait(mid,schedule,cond);
}
void notifyOne(scheduler* schedule,ConditionVariable* cond){
    if(isEmpty(cond->waiting_list)) return;
    ThreadID tid=dequeue(cond->waiting_list);
    resume(schedule,tid);
}


void notifyAll(scheduler* schedule,ConditionVariable* cond){
    while(!isEmpty(cond->waiting_list)){
        notifyOne(schedule,cond);
    }
}

void notifyAll_(scheduler* schedule,CondID cond_id){
    notifyAll(schedule,condArray[cond_id]);
}


CondID condCreate(){
    ConditionVariable* cond=(ConditionVariable*)malloc(sizeof(ConditionVariable));
    cond->waiting_list=(Queue*)malloc(sizeof(Queue));
    createQueue(cond->waiting_list,MAX_QUEUE_NUM);

    cond->cond_id=global_cond_id;
    condArray[global_cond_id]=cond;
    return global_cond_id++;
}

