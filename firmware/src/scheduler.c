#include "include/scheduler.h"
#include "include/thread.h"


TStatus initScheduler(scheduler* schedule){
    schedule->ready=createQueue(MAX_QUEUE_NUM);
    schedule->finished=createQueue(MAX_QUEUE_NUM);
    schedule->waiter=createQueue(MAX_QUEUE_NUM);
    schedule->current_tid=0;// main?
    schedule->next_tid=0;

};

void switchThreadStateTo(ThreadID tid, const ThreadStatus new_state){
    struct TCB* current=threadArray[tid];
    current->state=new_state;
}

// get the tid for running
void schedule(scheduler* schedule){

    // struct Process next=dequeue;
    struct TCB* curr_thread=threadArray[schedule->current_tid];
    if(curr_thread->state==RUNNING){
        curr_thread->state=READY;
        enqueue(schedule->ready,schedule->current_tid);
    }

    schedule->next_tid=dequeue(schedule->ready);
    struct TCB* next_thread=threadArray[schedule->next_tid];
    if(next_thread->state==WAITING){
            enqueue(schedule->waiter,next_thread->tid);
    }

    while(next_thread->state!=READY)
    {    
        schedule->next_tid=dequeue(schedule->ready);
        struct TCB* next_thread=threadArray[schedule->next_tid];
        if(next_thread->state==WAITING){
            enqueue(schedule->waiter,next_thread->tid);
        }
    }
    // schedule->next_tid=(schedule->current_tid+1)%current_thread_num;
    int cur_num=schedule->ready->size;
    if(schedule->next_tid==-1){
        schedule->next_tid=schedule->current_tid;
    }
    
    switchThreadStateTo(schedule->next_tid,RUNNING);
    schedule->current_tid=schedule->next_tid;
    running_thread_id=schedule->current_tid;
    if(schedule->next_tid!=curr_thread->tid){
        ContextSwitch(&threadArray[curr_thread->tid]->sp,threadArray[schedule->next_tid]->sp);
    }

}