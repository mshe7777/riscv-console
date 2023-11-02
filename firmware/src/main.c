#include <stdint.h>
#include "include/timer.h"
#include "include/kernel.h"

volatile int global = 42;
volatile uint32_t controller_status = 0;

volatile uint32_t *CARTRIDGE=(volatile uint32_t *)(0x4000001C);
volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xF4800);
volatile uint8_t *TEXT_COLOR=(volatile uint8_t *)(0x50000000+0xF5100);
typedef void (*FunctionPtr)(void);

int main() {
    int a = 4;
    int b = 12;
    int last_global = 42;
    int x_pos = 13;

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
    // VIDEO_MEMORY[12] = 'T';
    // VIDEO_MEMORY[13] = 'X';

    // TEXT_COLOR[0]=0x0F;
    // TEXT_COLOR[1]=0x0E;
    // TEXT_COLOR[2]=0x0D;
    // TEXT_COLOR[3]=0x0C;
    // TEXT_COLOR[4]=0x0B;
    // TEXT_COLOR[5]=0x0A;
    // TEXT_COLOR[6]=0x09;
    // VIDEO_MEMORY[289]='K';
    // TEXT_COLOR[289]=0x08;

    // VIDEO_MEMORY[2303]='E';
    // TEXT_COLOR[2303]='9';


    int k=0;
    while (1)
    {
        if((*CARTRIDGE)&0x1){
            FunctionPtr Fun = (FunctionPtr)((*CARTRIDGE) & 0xFFFFFFFC);
            Fun(); 
        }
    }
    

    // while (1) {

    //     int c = a + b + global;
    //     // VIDEO_MEMORY[k++]='B';
    //     if(global != last_global){

    //         controller_status=getButtonStatus();
    //         if(controller_status){
    //             VIDEO_MEMORY[x_pos] = ' ';
    //             if(controller_status & 0x1){
    //                 if(x_pos & 0x3F){
    //                     x_pos--;
    //                 }
    //             }
    //             if(controller_status & 0x2){
    //                 if(x_pos >= 0x40){
    //                     x_pos -= 0x40;
    //                 }
    //             }
    //             if(controller_status & 0x4){
    //                 if(x_pos < 0x8C0){
    //                     x_pos += 0x40;
    //                 }
    //             }
    //             if(controller_status & 0x8){
    //                 if((x_pos & 0x3F) != 0x3F){
    //                     x_pos++;
    //                 }
    //             }
    //             // press u to clear the display
    //             if(controller_status &0x10){
    //                 for(int i=0;i<64*36;i++){
    //                     VIDEO_MEMORY[i]=0;
    //                 }                  
    //             }
    //             // cartridgae 

    //             //command interrupt stop the timer
    //             VIDEO_MEMORY[x_pos] = 'X';
    //         }
    //         last_global = global;
    //     }
    // }
    return 0;
}
