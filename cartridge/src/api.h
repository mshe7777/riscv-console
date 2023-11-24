#ifndef API_H
#define API_H
#include<stdint.h>
#include<stddef.h>

typedef uint32_t ThreadID; 
typedef uint32_t TStatus;// total status

// system calls
ThreadID thread_create(TContextEntry entry, void* param, uint32_t  memsize,ThreadPriority prio);
TStatus thread_yield(ThreadID tid);
// exit current thread
TStatus thread_exit();



// video








#endif