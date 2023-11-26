#ifndef MUTEX_H
#define MUTEX_H

#include <stdint.h>
#include "kernel.h"
#include "thread.h"
#include "queue.h"
#include "scheduler.h"
typedef struct Mutex{
    ThreadID owner;
    Queue* waiting_list;        
}Mutex;

// global mutex id
#define MAX_MUTEX_NUM 10
#define INVALD_MUTEX_OWNER -1
// not lock
extern MutexId global_mutex_id;
extern struct Mutex** mutexArray;


// function
MutexId mutexCreate();
TStatus mutexLock(scheduler* schedule,Mutex* m);
TStatus mutexRelease(scheduler* schedule, Mutex* m);
int isLocked(Mutex* m);

// system call
void lock(MutexId mid);
void unlock(MutexId mid);
MutexId initLock();
TStatus destroyLock(MutexId mid);



#endif