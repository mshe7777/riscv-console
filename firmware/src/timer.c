#include "include/timer.h"



extern volatile char *VIDEO_MEMORY;


unsigned int x=0;


unsigned time_count=0;

uint32_t video_flag=1;
#define TICK_NUM 1
#define MTIME_LOW       (*((volatile uint32_t *)0x40000008))
#define MTIME_HIGH      (*((volatile uint32_t *)0x4000000C))
#define MTIMECMP_LOW    (*((volatile uint32_t *)0x40000010))
#define MTIMECMP_HIGH   (*((volatile uint32_t *)0x40000014))


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
    if((++time_count%TICK_NUM)==0){
        if(video_flag){
        VIDEO_MEMORY[x]='A';
        x++;
        }
    }
}

