#include "include/kernel.h"
#include "include/thread.h"
#include "include/scheduler.h"
#include "include/memory.h"
#include <stdlib.h>



volatile ThreadID global_tid =0;
uint32_t *global_gp;
struct TCB** threadArray;
struct scheduler* sched;
ThreadID running_thread_id=0;



// run before main.c need to change the ctr0.s
TStatus OSinitialize(uint32_t *gp){
    threadArray=malloc(sizeof(void*)*MAX_THREAD_NUM);
    // struct TCB* mainThread;
    sched=malloc(sizeof(struct scheduler*));
    initScheduler(sched);
    // init main
    struct TCB* main_thread=malloc(sizeof(struct TCB));
    main_thread->tid=global_tid;
    main_thread->state=RUNNING;
    main_thread->priority=Normal;
    threadArray[global_tid]=main_thread;
    set_tp(main_thread->tid);
    sched->current_tid=main_thread->tid;
    global_tid++;
    current_thread_num++;
    global_gp=gp;
    running_thread_id=sched->current_tid;
    if(global_gp==0){
        return STATUS_FAILURE;
    }
    else{
        return STATUS_SUCCESS;
    }
}


ThreadID threadCreate(TContextEntry entry,void *param,uint32_t memsize,ThreadPriority prio){
    if(entry==NULL){
        return INVALD_THREAD_ID;
    }else{
        if(current_thread_num>=MAX_THREAD_NUM){
            // number of threads exceeds current 
            return INVALD_THREAD_ID;
        }
        else{
            struct TCB* new_thread=kmalloc(sizeof(TCB));
            uint8_t *sb=kmalloc(memsize);
            new_thread->entry=entry;
            new_thread->param=param;
            new_thread->memory_size=memsize;
            new_thread->tid=global_tid;
            new_thread->stack_base=sb;
            new_thread->state=INIT;
            new_thread->priority=prio;
            
            new_thread->sp=
            ContextInitialize(
                (TStackRef)(new_thread->stack_base + memsize),
                (TContextEntry)entry,(void *)param);
            threadArray[global_tid]=new_thread;
            // new_thread->sp=ThreadPointers[global_tid];
            current_thread_num++;
            global_tid++;
            return new_thread->tid;
        }
    }
}


TStatus threadDelete(ThreadID tid){
    if(tid>=MAX_THREAD_NUM){
        return STATUS_INVALD_ID;
    }
    struct TCB* cur_thread= threadArray[tid];
    if(cur_thread->state!=FINISHED){
        return STATUS_INVALD_ID;
    }else{
        current_thread_num--;
        free(cur_thread->stack_base);
        free(cur_thread);
        threadArray[tid]=NULL;
        return STATUS_SUCCESS;
    }
}

TStatus threadActivate(ThreadID tid){
    if(tid>=MAX_THREAD_NUM){
        return STATUS_INVALD_ID;
    }
    struct TCB* act_thread=threadArray[tid];
    act_thread->state=READY;
    enqueue(sched->ready,act_thread->tid);
    int cur_num=sched->ready->size;
    struct  TCB* cur_thread=threadArray[sched->current_tid];
    schedule(sched);
    return STATUS_SUCCESS;
}

TStatus threadTerminate(ThreadID tid,ThreadReturn retval){
    if(tid>=MAX_THREAD_NUM){
        return STATUS_INVALD_ID;
    }
    struct TCB* curr_thread=threadArray[tid];

    curr_thread->state=FINISHED;
    curr_thread->ret_val=retval;
    if(sched->current_tid==tid){
        schedule(sched);
    }
    threadDelete(tid);
    return STATUS_SUCCESS;
}

TStatus threadWait(ThreadID tid,ThreadReturn* retvalref,Tick timeout){

}

ThreadID threadId(){
    return sched->current_tid;
}

ThreadStatus threadState(ThreadID tid){
    return threadArray[tid]->state;
}

TStatus threadSleep(Tick tick){

}

void set_timer(uint64_t timestamp){


    uint64_t h=MTIME_HIGH<<32;
    uint64_t l=MTIME_LOW;
    uint64_t cmp_h=MTIMECMP_HIGH<<32;
    uint64_t cmp_l=MTIME_LOW;
    uint64_t now=h|l;
    uint64_t NewCompare=cmp_h |cmp_l;

    if(NewCompare<=now){
        // when current time arrives the set time
        // unkown clock frequency not accurate timer
        NewCompare+=timestamp;
    }
    MTIMECMP_HIGH = NewCompare>>32;
    MTIMECMP_LOW = NewCompare;


}

void handle_time_interrupt(){

    set_timer(1000);

    if (current_thread_num >= 2)
    {
        int current_num=sched->ready->size;
        uint32_t mepc = csr_mepc_read();
        // printf("\n");
        TInterruptState PrevState = SuspendInterrupts();
        // int t1, t2;
        // t1 = running_thread_pointer;
        // t2 = (running_thread_pointer + 1) % current_thread_num;
        // running_thread_pointer = t2;
        schedule(sched);
        csr_write_mepc(mepc);
        ResumeInterrupts(PrevState);
    }
    

}

