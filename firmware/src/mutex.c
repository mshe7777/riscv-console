#include "include/mutex.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

MutexId global_mutex_id=0;


MutexId mutexCreate(){
    Mutex* m=(Mutex*)malloc(sizeof(Mutex));
    m->waiting_list=(Queue*)malloc(sizeof(Queue));
    createQueue(m->waiting_list,MAX_MUTEX_NUM);
    m->owner=INVALD_MUTEX_OWNER;
    mutexArray[global_mutex_id]=m;
    return global_mutex_id++;
}
TStatus mutexLock(scheduler* schedule,Mutex* m){
    if(isLocked(m)){
        // lock twice
        if(schedule->current_tid==m->owner){
            // do nothing
        }else{
            enqueue(m->waiting_list,schedule->current_tid);
            suspend(schedule);
        }
    }else{
        m->owner=schedule->current_tid;
    }
}

TStatus mutexRelease(scheduler* schedule,Mutex* m){
    if(isLocked(m)){
        if(isEmpty(m->waiting_list)){
            if(schedule->current_tid==m->owner){
                m->owner=INVALD_MUTEX_OWNER;
            }else{
                // do nothing
            }
        }else{
            // waiting all waiters to finish
            m->owner=dequeue(m->waiting_list);
            resume(schedule,m->owner);
        }
    }else{
        // error?

    }
}



int isLocked(Mutex* m){
    return m->owner!=INVALD_MUTEX_OWNER;
}