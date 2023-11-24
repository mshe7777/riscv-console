#include <stdint.h>
#include <stddef.h>
volatile int global = 42;
volatile uint32_t controller_status = 0;

volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xF4800);

typedef void (*TThreadEntry)(void *);
typedef uint32_t *TThreadContext;

void OtherThreadFunction(void *);
TThreadContext InitThread(uint32_t *stacktop, TThreadEntry entry,void *param);
void SwitchThread(TThreadContext *oldcontext, TThreadContext newcontext);

TThreadContext OtherThread;
TThreadContext MainThread;
TThreadContext MainThread_copy;

int count=0;

int main() {
    int a = 4;
    int b = 12;
    int last_global = 42;
    int x_pos = 12;
    uint32_t OtherThreadStack[128];
    

    VIDEO_MEMORY[0] = 'H';
    VIDEO_MEMORY[1] = 'e';
    VIDEO_MEMORY[2] = 'l';
    VIDEO_MEMORY[3] = 'l';
    VIDEO_MEMORY[4] = 'o';
    VIDEO_MEMORY[5] = ' ';
    VIDEO_MEMORY[6] = 'W';
    VIDEO_MEMORY[7] = 'o';
    VIDEO_MEMORY[8] = 'r';
    VIDEO_MEMORY[9] = 'l';
    VIDEO_MEMORY[10] = 'd';
    VIDEO_MEMORY[11] = '!';
    VIDEO_MEMORY[12] = 'X';

    OtherThread = InitThread(OtherThreadStack + 128, OtherThreadFunction, NULL);


    while (1) {
        int c = a + b + global;
        if(global != last_global){
            if(controller_status){
                VIDEO_MEMORY[x_pos] = ' ';
                if(controller_status & 0x1){
                    if(x_pos & 0x3F){
                        x_pos--;
                    }
                }
                if(controller_status & 0x2){
                    if(x_pos >= 0x40){
                        x_pos -= 0x40;
                    }
                }
                if(controller_status & 0x4){
                    if(x_pos < 0x8C0){
                        x_pos += 0x40;
                    }
                }
                if(controller_status & 0x8){
                    if((x_pos & 0x3F) != 0x3F){
                        x_pos++;
                    }
                }
                VIDEO_MEMORY[x_pos] = 'X';
            }
            MainThread_copy=MainThread;
            SwitchThread(&MainThread,OtherThread);
            MainThread_copy=MainThread;
            last_global = global;
        }
    }
    return 0;
}

void OtherThreadFunction(void *){
    int last_global = global;
    while(count<40){
        VIDEO_MEMORY[0x40*1+count++]='A';
        if(global != last_global){
            SwitchThread(&OtherThread,MainThread);
            last_global = global;
        }
    }
    SwitchThread(&OtherThread,MainThread);
    return;
}
