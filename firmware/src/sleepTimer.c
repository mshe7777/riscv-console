#include "include/sleepTimer.h"
#include "include/mutex.h"
#include<stdlib.h>



void doSleep(size_t cnt,scheduler* schedule,SleepTimer* sleeper){
    // size_t wake_ticks=sleeper->systicks+cnt;
    // mutexLock(schedule,mutexArray[sleeper->mutex_id]);
    // while(sleeper->systicks<wake_ticks){
    //     wait_(sleeper->mutex_id,schedule,sleeper->cond_id);
    // }
    // mutexRelease(schedule,mutexArray[sleeper->mutex_id]);
    // 基于wait比较复杂 且原理有问题，使用一个比较简单粗糙的方法
    struct TCB* cur=threadArray[sched->current_tid];
    cur->ticks=cnt;
    enqueue(sleeper->waiter,cur->tid);
    suspend(sched);
}



void updateGlobalTicks(scheduler* sched,SleepTimer* sleeper){
    // notifyAll()
    // sleeper->systicks++;
    // notifyAll_(schedule,sleeper->cond_id);
    if(!isEmpty(sleeper->waiter)){
    for(int i=0;i<sleeper->waiter->size;i++){
        ThreadID tid=dequeue(sleeper->waiter);
        struct TCB* thread=threadArray[tid];
        thread->ticks--;
        if(thread->ticks==0){
            // resume
            thread->state=READY;
            enqueue(sched->ready,tid);
        }else{
            enqueue(sleeper->waiter,tid);
        }
    }}
    else{
        return;
    }
}



void initSleepTimer(SleepTimer* new_sleep_timer){
    new_sleep_timer->cond_id=condCreate();
    new_sleep_timer->mutex_id=mutexCreate();
    new_sleep_timer->systicks=0;
    new_sleep_timer->waiter=(Queue*)malloc(sizeof(Queue));
    createQueue(new_sleep_timer->waiter,MAX_COND_NUM);
    return;
}