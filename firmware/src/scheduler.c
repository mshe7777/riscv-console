#include "include/scheduler.h"
#include "include/thread.h"


TStatus initScheduler(scheduler* schedule){
    schedule->ready=createQueue(MAX_QUEUE_NUM);
    schedule->finished=createQueue(MAX_QUEUE_NUM);
    schedule->waiter=createQueue(MAX_QUEUE_NUM);
    schedule->current_tid=0;// main?
    schedule->next_tid=0;

};

void interruptSwicth(scheduler* schedule){
    // switchThreadStateTo(schedule,READY);
    // ?
    if(isEmpty(schedule->ready)) return;

    ThreadID curr_tid=schedule->current_tid;
    ThreadID next_tid=dequeue(schedule->ready);

    threadArray[curr_tid]->state=READY;
    threadArray[next_tid]->state=RUNNING;
    enqueue(schedule->ready,curr_tid);

    schedule->current_tid=next_tid;
    ContextSwitch(&threadArray[curr_tid]->sp,threadArray[next_tid]->sp);
}

// reference https://github.com/XiaoxingChen/flitos/tree/chenxx/develop
void yield(scheduler* schedule){
    switchThreadStateTo(schedule,READY);
}

void suspend(scheduler* schedule){
    switchThreadStateTo(schedule,WAITING);
}

void resume(scheduler* schedule, ThreadID tid){
    
    threadArray[tid]->state=READY;
    enqueue(schedule->ready,tid);
}
void kexit(scheduler* schedule){
    switchThreadStateTo(schedule,FINISHED);
}




void startFirstThread(scheduler* schedule){
    if(isEmpty(schedule->ready)) return;
    ThreadID cur_tid=dequeue(schedule->ready);
    threadArray[cur_tid]->state=RUNNING;
    schedule->current_tid=cur_tid;
    startFirst((uint32_t)(threadArray[cur_tid]->sp));
}

void switchThreadStateTo(scheduler* schedule,const ThreadStatus new_state){
    if(new_state!=READY&&new_state!=WAITING&&new_state!=FINISHED){
        return;
    }
    if(isEmpty(schedule->ready)) return;
    ThreadID curr_tid=schedule->current_tid;
    ThreadID next_tid=dequeue(schedule->ready);

    threadArray[curr_tid]->state=new_state;
    threadArray[next_tid]->state=RUNNING;

    if(new_state==READY){
        enqueue(schedule->ready,curr_tid);
    }else if(new_state==FINISHED){
        enqueue(schedule->finished,curr_tid);
    }
    DisableInterrupts();
    schedule->current_tid=next_tid;
    ContextSwitch(threadArray[curr_tid]->sp,threadArray[next_tid]->sp);
    EnableInterrupts();
}

