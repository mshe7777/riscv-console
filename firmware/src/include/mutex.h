#ifndef MUTEX_H
#define MUTEX_H

#include <stdint.h>
#include "kernel.h"
#include "thread.h"
#include "queue.h"

typedef struct Mutex{
    ThreadID owner;
    Queue* waiting_list;        
}Mutex;



TStatus mutexLock();
TStatus mutexRelease();



#endif