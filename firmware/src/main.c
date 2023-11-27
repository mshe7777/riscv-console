#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "include/kernel.h"
#include "include/video.h"
#include "include/thread.h"
#include "include/memory.h"
#include "include/scheduler.h"
#include "include/mutex.h"




// thread_test
volatile int global = 42;
volatile int pos1=0x40*1;
volatile int pos2=0x40*2;
volatile int count1=0;
volatile int count2=0;
MutexId mid;

void thread1(void *){
    while (1)
    {   
        // VIDEO_MEMORY[pos1]='A';
        // VIDEO_MEMORY[pos2]=' ';
        /* code */
        // switch
        // thread_yield()
        // lock(mid);

        VIDEO_MEMORY[pos1]='A';
        VIDEO_MEMORY[pos2]=' ';
        // unlock(mid);
        // thread_yield();
    }
    // explict
    thread_exit();
    return;
}
void thread2(void *){
    while (1)
    {
        /* code */
        // thread_yield();
        // lock(mid);
        VIDEO_MEMORY[pos2]='B';
        VIDEO_MEMORY[pos1]=' ';
        // unlock(mid);
        // thread_yield();
    }
    thread_exit();
    return;
}

void memory_test(){
    char *Buffer=malloc(32);
    strcpy(Buffer,"OS TEST");
    strcpy((char *)(VIDEO_MEMORY),Buffer);

}
// void 

int main(){
    OSinitialize(get_gp());
    mid=initLock();
    // char *Buffer = malloc(32);
    // strcpy(Buffer,"OS started!");
    // strcpy((char *)(VIDEO_MEMORY),Buffer);
    memory_test();
    // threadInit(thread1,NULL);
    // threadInit(thread2,NULL);
    // DisableInterrupts();
    ThreadID t1=thread_create(thread1,NULL,THREAD_MEMORY,High);
    ThreadID t2=thread_create(thread2,NULL,THREAD_MEMORY,High);
    startFirstThread(sched);
    
    // thread_yield(t1);
    // thread_yield(t2);



    char *Buffer2 = malloc(32);
    strcpy(Buffer2,"Thread test1 finished");
    strcpy((char *)(VIDEO_MEMORY+0x40*5),Buffer2);
    while(1){

    }
    
}



// cart test
// volatile uint32_t controller_status = 0;
// volatile int global = 42;

// // int pthread_mutex_lock(pthread_mutex_t *mutex);
// // int pthread_mutex_unlock(pthread_mutex_t *mutex);
// // to here
// // threadCreate()

// //cartridge setup
// volatile uint32_t *CartridgeStatus = (volatile uint32_t *)(0x4000001C);
// typedef void (*FunctionPtr)(void);


// int main(){
//     // simple_medium_sprite(0,0,0);
//     VIDEO_MEMORY[0]='A';

//     //loading cartridge
//     while (1){
//         if(*CartridgeStatus & 0x1){
//             FunctionPtr Fun = (FunctionPtr)((*CartridgeStatus) & 0xFFFFFFFC);
//             Fun();
//         }
//     }
    
//     return 0;
// }