#ifndef THREAD_H
#define THREAD_H
#define MAX_THREAD_NUM 10
#include "kernel.h"
// also include the defination of schedule

// thread def
typedef uint32_t TInterruptState, *TInterruptStateRef;
typedef uint32_t *TStackRef;
typedef uint32_t (*TContextEntry)(void *param);
typedef uint32_t ThreadID; 

typedef uint32_t ThreadReturn;
typedef uint32_t Tick;

#define THREAD_MEMORY 2048


typedef enum{
    INIT=0,
    READY,
    RUNNING,
    WAITING,
    FINISHED
}ThreadStatus;

typedef enum{
    High=0,
    Normal,
    Low
}ThreadPriority;


typedef struct TCB
{
    ThreadID tid;
    uint32_t *gp;
    ThreadStatus state;
    ThreadPriority priority;
    uint32_t* sp; // TStackRef
    uint32_t memory_size;
    TContextEntry entry;
    void* param;
    int ticks;
    ThreadID wait_id;
    ThreadReturn ret_val;
    uint8_t *stack_base;// return value of malloc;
    const char* buffer;
    uint32_t write_size;

}TCB;





extern struct TCB** threadArray;
extern volatile ThreadID global_tid;

TStackRef ContextInitialize(TStackRef stacktop, TContextEntry entry, void *param,uint32_t gp);
void ContextSwitch(TStackRef *storecurrent, TStackRef restore);
void set_tp(ThreadID tid);
ThreadID get_tp(void);
// simple
TStatus threadInit(TContextEntry entry, void *param);
uint32_t *init_Stack(uint32_t* sp, TContextEntry function, uint32_t param, uint32_t tp);
// Thread variable
extern uint32_t ThreadStack[9][2048];
extern TStackRef ThreadPointers[10];
extern int current_thread_num;
extern int running_thread_pointer;
extern ThreadID running_thread_id;


// implement in kernel.c
// more api create delete activate terminate wait id state
ThreadID threadCreate(TContextEntry entry,void *param,uint32_t memsize,ThreadPriority prio,uint32_t gp);
TStatus threadDelete(ThreadID tid);
TStatus threadActivate(ThreadID tid);
TStatus threadTerminate(ThreadID tid,ThreadReturn retval);
TStatus threadWait(ThreadID tid,ThreadReturn* retvalref,Tick timeout );
ThreadID threadId();// get current tid
ThreadStatus threadState(ThreadID tid); //  get the thread's status
TStatus threadSleep(Tick tick); // unknow?



// system calls
ThreadID thread_create(TContextEntry entry, void* param, uint32_t  memsize,ThreadPriority prio);
TStatus thread_yield();
// exit current thread
TStatus thread_exit();












__attribute__((always_inline)) inline TInterruptState SuspendInterrupts(void)
{
    uint32_t result;
    asm volatile("csrrci %0, mstatus, 0x8"
                 : "=r"(result));
    return result;
}

__attribute__((always_inline)) inline void ResumeInterrupts(TInterruptState state)
{
    asm volatile("csrs mstatus, %0"
                 :
                 : "r"(state & 0x8));
}

__attribute__((always_inline)) inline void EnableInterrupts(void)
{
    asm volatile("csrsi mstatus, 0x8");
}

__attribute__((always_inline)) inline void DisableInterrupts(void)
{
    asm volatile("csrci mstatus, 0x8");
}




#endif