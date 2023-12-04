#include <stdint.h>
#include<stdlib.h>
#include<string.h>
#include "api.h"




void simple_medium_sprite(int16_t x, int16_t y, int16_t z);


// void memory_test(){

// }
// volatile int global = 42;
volatile int flag=0;
MutexId mid;

void switch_display(int flag){
    if(flag){
        VIDEO_MEMORY[pos1]='A';
        VIDEO_MEMORY[pos2]=' ';
    }else{
        VIDEO_MEMORY[pos1]=' ';
        VIDEO_MEMORY[pos2]='B';
    }
    // sleep(3);
    // flag=~flag;
}

void thread1(void *){
    while (1)
    {   
        // VIDEO_MEMORY[pos1]='A';
        // VIDEO_MEMORY[pos2]=' ';
        /* code */
        // switch
        // thread_yield()
        // lock(mid);
    
        // simple_medium_sprite_green(0,0,0);
        VIDEO_MEMORY[pos1]='A';
        VIDEO_MEMORY[pos2]=' ';
        // sleep(3);
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
        // simple_medium_sprite_red(0,0,0);
        // unlock(mid);
        // thread_yield();
    }
    thread_exit();
    return;
}

void thread3(void *){
    while(1){
        // lock(mid);
        switch_display(1);
        sleep(5);
        // unlock(mid);
    }
}

void thread4(void*){
    while(1){
        // lock(mid);
        switch_display(0);
        // unlock(mid);
    }
}


void memory_test(){
    // char *Buffer=malloc(32);
    char *Buffer=malloc(32);
    strcpy(Buffer,"OS TEST");
    strcpy((char *)(VIDEO_MEMORY),Buffer);

}

void video_test(){
    simple_medium_sprite_red(0,0,0);
    // setSmallSprite()
    
}

void thread_test(){
    ThreadID t1=thread_create_gp(thread1,NULL,THREAD_MEMORY,High);
    ThreadID t2=thread_create_gp(thread2,NULL,THREAD_MEMORY,High);
    // startFirstThread(sched);
    uint32_t* global_gp=get_gp();
}



void sleep_test(){
    ThreadID t3=thread_create_gp(thread3,NULL,THREAD_MEMORY,High);
    ThreadID t4=thread_create_gp(thread4,NULL,THREAD_MEMORY,High);
}
    




int main() {
    int a = 4;
    int b = 12;
    int last_global = 42;
    int x_pos = 12;
    int countdown =1;

    *MODE_REGISTER=0;
    VIDEO_MEMORY[2]='H';
    mid=initLock();
    // gp?
    // memory_test();
    // thread_test();
    // thread 包含了lock
    // video_test();
    sleep_test();
    // join_sleep_test();

    // 加上join之后会停在这里 不会显示x
    VIDEO_MEMORY[x_pos]='X';
    
    while (1) {
        // switch_display();
        // int c = a + b + global;
        // if(a == 11){
        //     b++;
        // }
        // global = getTicks();
        // if(global != last_global){
        //     controller_status = getButtonStatus();
        //     if(controller_status){
        //         VIDEO_MEMORY[x_pos] = ' ';
        //         if(controller_status & 0x1){
        //             if(x_pos & 0x3F){
        //                 x_pos--;
        //             }
        //         }
        //         if(controller_status & 0x2){
        //             if(x_pos >= 0x40){
        //                 x_pos -= 0x40;
        //             }
        //         }
        //         if(controller_status & 0x4){
        //             if(x_pos < 0x8C0){
        //                 x_pos += 0x40;
        //             }
        //         }
        //         if(controller_status & 0x8){
        //             if((x_pos & 0x3F) != 0x3F){
        //                 x_pos++;
        //             }
        //         }
        //         VIDEO_MEMORY[x_pos] = 'X';
        //     }
        //     last_global = global;
        // }
    }
    return 0;
}
