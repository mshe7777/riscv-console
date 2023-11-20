#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "include/timer.h"
#include "include/kernel.h"
#include "include/video.h"
#include "include/thread.h"


// // volatile int global = 42;
// // volatile uint32_t controller_status = 0;

// // volatile uint32_t *CARTRIDGE=(volatile uint32_t *)(0x4000001C);
// // volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xF4800);
// // volatile uint8_t *TEXT_COLOR=(volatile uint8_t *)(0x50000000+0xF5100);


// // // cmd and video interrupt
// volatile int vip=0;
// volatile int cmd=0;










// volatile int global = 42;
// volatile uint32_t controller_status = 0;
// volatile uint32_t *CARTRIDGE=(volatile uint32_t *)(0x4000001C);

// volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xF4800);
// volatile uint8_t *MEDIUM_DATA = (volatile uint8_t *)(0x500D0000);
// uint8_t *medium_data;
// uint8_t *background_data;
// volatile uint32_t *MEDIUM_PALETTE = (volatile uint32_t *)(0x500F2000);
// volatile uint32_t *MEDIUM_CONTROL = (volatile uint32_t *)(0x500F5F00);
// volatile uint32_t *MODE_REGISTER = (volatile uint32_t *)(0x500F6780);
// uint32_t* PALETTE1;
// typedef void (*FunctionPtr)(void);

// uint32_t MediumControl(uint8_t palette, int16_t x, int16_t y, uint8_t z, uint8_t index);

// void changeVideoModel(){
//     cmd=getCmdInterrupted();
//     setVideoModel(cmd);
//     // test
//     *MODE_REGISTER=~(*MODE_REGISTER);
// }

// int main() {
//     int a = 4;
//     int b = 12;
//     int last_global = 42;
//     int x_pos = 12;

//     VIDEO_MEMORY[0] = 'H';
//     VIDEO_MEMORY[1] = 'e';
//     VIDEO_MEMORY[2] = 'l';
//     VIDEO_MEMORY[3] = 'l';
//     VIDEO_MEMORY[4] = 'o';
//     VIDEO_MEMORY[5] = ' ';
//     VIDEO_MEMORY[6] = 'W';
//     VIDEO_MEMORY[7] = 'o';
//     VIDEO_MEMORY[8] = 'r';
//     VIDEO_MEMORY[9] = 'l';
//     VIDEO_MEMORY[10] = 'd';
//     VIDEO_MEMORY[11] = '!';
//     VIDEO_MEMORY[12] = 'X';

//     // Fill out sprite data
//     for(int y = 0; y < 32; y++){
//         for(int x = 0; x < 32; x++){
//             medium_data[y*32+x] = 1;
//             MEDIUM_DATA[y*32+x]=1;
//         }
//     }

//     // Fill out background

//     for(int i=0;i<DISPLAY_HEIGHT;i++){
//         for(int j=0;j<DISPLAY_WITDH;j++){
//             int cnt=i*DISPLAY_HEIGHT+j;
//             background_data[cnt]=1;
//         }
//     }
//     // *PALETTE1=0xFFFF0000;
//     // setBackGround(0,background_data);
//     // setSprite(0,medium_data,Medium);
//     initSpritesPalettes(1,0xFFFFFFFF,Medium);
//     // MEDIUM_PALETTE[1] = 0xFFFF0000; // A R G B
//     MEDIUM_CONTROL[0] = MediumControl(0, 0, 0, 0, 0);
//     // setSpriteControl(0,0,0,0,0,Medium);
//     // *MODE_REGISTER = 1;
//     while (1) {
//         int c = a + b + global;
//         if(global != last_global){
//             getVideoInterrupted();

//             if((*CARTRIDGE)&0x1){
//                 *MODE_REGISTER = 0;
//                 FunctionPtr Fun = (FunctionPtr)((*CARTRIDGE) & 0xFFFFFFFC);
//                 Fun(); 
//             }
//             changeVideoModel();
//             controller_status=getButtonStatus();
//             if(controller_status){
//                 VIDEO_MEMORY[x_pos] = ' ';
//                 if(controller_status & 0x1){
//                     if(x_pos & 0x3F){
//                         x_pos--;
//                     }
//                 }
//                 if(controller_status & 0x2){
//                     if(x_pos >= 0x40){
//                         x_pos -= 0x40;
//                     }
//                 }
//                 if(controller_status & 0x4){
//                     if(x_pos < 0x8C0){
//                         x_pos += 0x40;
//                     }
//                 }
//                 if(controller_status & 0x8){
//                     if((x_pos & 0x3F) != 0x3F){
//                         x_pos++;
//                     }
//                 }
//                 VIDEO_MEMORY[x_pos] = 'X';
//                 MEDIUM_CONTROL[0] = MediumControl(0, (x_pos & 0x3F)<<3, (x_pos>>6)<<3, 0, 0);
//                 // setSpriteControl(0, (x_pos & 0x3F)<<3, (x_pos>>6)<<3, 0, 0,Medium);
//             }
//             last_global = global;
//         }
//     }
//     return 0;
// }

// uint32_t MediumControl(uint8_t palette, int16_t x, int16_t y, uint8_t z, uint8_t index){
//     return (((uint32_t)index)<<24) | (((uint32_t)z)<<21) | (((uint32_t)y+32)<<12) | (((uint32_t)x+32)<<2) | (palette & 0x3);
// }

volatile int global = 42;
volatile uint32_t controller_status = 0;

volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xF4800);
volatile int start_main_pos=0x40*2;
volatile int start_other_pos=0x40*3;


void OtherThreadFunction(void *);


TStackRef OtherThread;
TStackRef MainThread;

int main() {
    int a = 4;
    int b = 12;
    int last_global = 42;
    int x_pos = 12;
    uint32_t OtherThreadStack[128];
    char *Buffer = malloc(32);
    strcpy(Buffer,"OS STARTED");
    strcpy((char *)VIDEO_MEMORY,Buffer);
    // VIDEO_MEMORY[0] = 'H';
    // VIDEO_MEMORY[1] = 'e';
    // VIDEO_MEMORY[2] = 'l';
    // VIDEO_MEMORY[3] = 'l';
    // VIDEO_MEMORY[4] = 'o';
    // VIDEO_MEMORY[5] = ' ';
    // VIDEO_MEMORY[6] = 'W';
    // VIDEO_MEMORY[7] = 'o';
    // VIDEO_MEMORY[8] = 'r';
    // VIDEO_MEMORY[9] = 'l';
    // VIDEO_MEMORY[10] = 'd';
    // VIDEO_MEMORY[11] = '!';
    VIDEO_MEMORY[12] = 'X';

    // OtherThread = threadInit(OtherThreadStack + 128, OtherThreadFunction, NULL);
    threadInit(OtherThreadFunction,NULL);

    



    while (1) {
        int c = a + b + global;
        if(global != last_global){
            controller_status=getButtonStatus();
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
            VIDEO_MEMORY[start_main_pos]='A';
            VIDEO_MEMORY[start_other_pos]=' ';
            // ContextSwitch(&MainThread,OtherThread);
            last_global = global;
        }
    }
    return 0;
}

void OtherThreadFunction(void *){
    int last_global = global;
    while(1){
        VIDEO_MEMORY[0x40*1+0]='A';
        VIDEO_MEMORY[start_main_pos]='B';
        VIDEO_MEMORY[start_other_pos]='B';
        if(global != last_global){
            // ContextSwitch(&OtherThread,MainThread);
            last_global = global;
        }
    }
}