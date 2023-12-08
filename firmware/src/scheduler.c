#include "include/scheduler.h"
#include "include/thread.h"
#include <stdlib.h>


first_flag=1;

TStatus initScheduler(scheduler* sch){



    // 初始化其他成员
    sch->current_tid = 0;      
    sch->next_tid = 0;

    // 初始化 ready 队列
    sch->ready = (Queue *)malloc(sizeof(Queue));
    createQueue(sch->ready, MAX_QUEUE_NUM);

    // 初始化 finished 队列
    sch->finished = (Queue *)malloc(sizeof(Queue));
    createQueue(sch->finished, MAX_QUEUE_NUM);

    // 初始化 waiter 队列
    sch->waiter = (Queue *)malloc(sizeof(Queue));
    createQueue(sch->waiter, MAX_QUEUE_NUM);

};

void interruptSwicth(scheduler* schedule){
    // switchThreadStateTo(schedule,READY);
    // ?

    // first time current=0
    if(isEmpty(schedule->ready)) return;

    ThreadID curr_tid=schedule->current_tid;
    ThreadID next_tid=dequeue(schedule->ready);

    threadArray[curr_tid]->state=READY;
    threadArray[next_tid]->state=RUNNING;
    if(!first_flag){
        enqueue(schedule->ready,curr_tid);
    }
    first_flag=0;
    
    schedule->current_tid=next_tid;
    // if(curr_tid!=next_tid){
        ContextSwitch(&threadArray[curr_tid]->sp,threadArray[next_tid]->sp);
    // }
}

void yield(scheduler* schedule){
    switchThreadStateTo(schedule,READY);
}

void suspend(scheduler* schedule){
    switchThreadStateTo(schedule,WAITING);
}

void resume(scheduler* schedule, ThreadID tid){
    
    threadArray[tid]->state=READY;
    enqueue(schedule->ready,tid);
    // interruptSwicth(schedule);
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
    ContextSwitch(&threadArray[curr_tid]->sp,threadArray[next_tid]->sp);
    EnableInterrupts();
}



