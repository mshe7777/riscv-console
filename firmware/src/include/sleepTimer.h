#ifndef SLEEPTIMER_H
#define SLEEPTIMER_H
#include <stdint.h>
#include "mutex.h"
#include "condition.h"
#include "scheduler.h"
#include "queue.h"


typedef struct SleepTimer {
    MutexId mutex_id;
    CondId cond_id;
    volatile size_t systicks;
    Queue* waiter;
} SleepTimer;

extern struct SleepTimer* global_sleep_timer;





void doSleep(size_t cnt,scheduler* schedule,SleepTimer* sleeper);

void updateGlobalTicks(scheduler* schedule,SleepTimer* sleeper);
void initSleepTimer(SleepTimer* sleeper);

// system calls



void sleep(size_t ticks);
#endif