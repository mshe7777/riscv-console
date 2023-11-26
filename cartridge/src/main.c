#include <stdint.h>
#include<stdlib.h>
#include<string.h>
#include "api.h"


volatile int global = 42;
volatile uint32_t controller_status = 0;
volatile uint32_t *MODE_REGISTER = (volatile uint32_t *)(0x500F6780);


volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xF4800);

void simple_medium_sprite(int16_t x, int16_t y, int16_t z);


// void memory_test(){

// }
// volatile int global = 42;
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
    // char *Buffer=malloc(32);
    char *Buffer=malloc(32);
    strcpy(Buffer,"OS TEST");
    strcpy((char *)(VIDEO_MEMORY),Buffer);

}

void video_test(){
    simple_medium_sprite(0,0,0);
}

void thread_test(){
    ThreadID t1=thread_create(thread1,NULL,THREAD_MEMORY,High);
    ThreadID t2=thread_create(thread2,NULL,THREAD_MEMORY,High);
    // startFirstThread(sched);
    uint32_t* global_gp=get_gp();
}


int main() {
    int a = 4;
    int b = 12;
    int last_global = 42;
    int x_pos = 12;
    int countdown =1;

    // *MODE_REGISTER=0;
    VIDEO_MEMORY[0]="H";
    // memory_test();
    // video_test();
    
    thread_test();

    // simple_medium_sprite(0,0,0);


    

    while (1) {

    }
    return 0;
}
