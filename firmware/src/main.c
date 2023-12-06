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
    char *source = "Wellcome to Group4 OS! Now the OS has started, you can insert your cartridge :)";
    kmemcpy((char *)VIDEO_MEMORY, source, 80); 

    //loading cartridge
    while (1){
        if(*CartridgeStatus & 0x1){
            FunctionPtr Fun = (FunctionPtr)((*CartridgeStatus) & 0xFFFFFFFC);
            Fun();
        }
    }
    
    return 0;
}