#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "include/kernel.h"
#include "include/video.h"
#include "include/thread.h"
#include "include/memory.h"
#include "include/scheduler.h"
#include "include/mutex.h"

volatile int global = 42;

//cartridge setup
volatile uint32_t *CartridgeStatus = (volatile uint32_t *)(0x4000001C);
typedef void (*FunctionPtr)(void);


int main(){
    VIDEO_MEMORY[0]='O';
    VIDEO_MEMORY[1]='S';
    VIDEO_MEMORY[2]=' ';
    VIDEO_MEMORY[3]='S';
    VIDEO_MEMORY[4]='T';
    VIDEO_MEMORY[5]='A';
    VIDEO_MEMORY[6]='R';
    VIDEO_MEMORY[7]='T';
    VIDEO_MEMORY[8]='!';

    //loading cartridge
    while (1){
        if(*CartridgeStatus & 0x1){
            FunctionPtr Fun = (FunctionPtr)((*CartridgeStatus) & 0xFFFFFFFC);
            Fun();
        }
    }
    
    return 0;
}