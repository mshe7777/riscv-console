#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include "api.h"

volatile uint32_t  running_flag=1; 

extern uint32_t color_palette[10];
extern uint8_t frog_img[32*32];
extern uint8_t wood_left_img[32*32];
extern uint8_t wood_mid_img[32*32];
extern uint8_t wood_right_img[32*32];
extern uint8_t background_img[512*288];
extern uint8_t background_color_palette[4*16];

void initVideoSetting();

struct position {
    uint32_t x;
    uint32_t y;
    uint8_t step;
    MutexId mtx;
};

int main() {
    initVideoSetting();
    int last_global = 0;
    int countdown = 0;
    struct position frog;

    frog.x = 240;
    frog.y = 256;
    frog.step = 0;
    frog.mtx = initLock();

    int wood_index_1 = 208;
    int wood_index_2 = wood_index_1 + 80;
    int wood_index_3 = wood_index_1 - 40;

    while(running_flag){

        ////Wood move thread
        global = getTicks();
        if(global != last_global){
            //wood move sp eed
            wood_index_1-=5;
            wood_index_2+=7;
            wood_index_3-=10;

            //position reset over screen
            if(wood_index_1 <= 0) wood_index_1 = 512;
            if(wood_index_2 >= 512) wood_index_2 = 0;
            if(wood_index_3 <= 0) wood_index_3 = 512;
            
            //moving
            setSpriteControl(2, 2, wood_index_1 - 32, 205, 1, 1, Medium);
            setSpriteControl(3, 3, wood_index_1, 205, 1, 1, Medium);
            setSpriteControl(4, 4, wood_index_1 + 32, 205, 1, 1, Medium);

            setSpriteControl(5, 5, wood_index_2 - 32, 145, 1, 1, Medium);
            setSpriteControl(6, 6, wood_index_2, 145, 1, 1, Medium);
            setSpriteControl(7, 7, wood_index_2 + 32, 145, 1, 1, Medium);

            setSpriteControl(8, 8, wood_index_3 - 32, 85, 1, 1, Medium);
            setSpriteControl(9, 9, wood_index_3, 85, 1, 1, Medium);
            setSpriteControl(10, 10, wood_index_3 + 32, 85, 1, 1, Medium);

            last_global = global;
        }
        
        //Frog move thread
        if(countdown > 50000){
            controller_status = getButtonStatus();
            if(controller_status){
                if(controller_status & 0x1){
                    frog.x-=32;
                }

                if(controller_status & 0x2){
                    frog.y-=60;
                    frog.step++;
                }

                if(controller_status & 0x4){
                    frog.y+=60;
                    frog.step--;
                }

                if(controller_status & 0x8){
                    frog.x+=32;
                }
                
            }
            lock(frog.mtx);
            setSpriteControl(1, 1, frog.x, frog.y, 2, 1, Medium);
            unlock(frog.mtx);
            countdown = 0;
        }
        countdown++;


        //Game over check thread
        if(frog.step == 4){
            running_flag = 0;
        }

        if(frog.step == 3){
            if(abs(frog.x-wood_index_3) >= 64) running_flag = 0;
        }

        if(frog.step == 2){
            if(abs(frog.x-wood_index_2) >= 64) running_flag = 0;
        }

        if(frog.step == 1){
            if(abs(frog.x-wood_index_1) >= 64) running_flag = 0;
        }
    }

    //Game over graph
    while(!running_flag){
        setSpriteControl(1, 1, 240, 162, 2, 1, Medium);
        setSpriteControl(2, 2, 240 - 32, 205, 1, 1, Medium);
        setSpriteControl(3, 3, 240, 205, 1, 1, Medium);
        setSpriteControl(4, 4, 240 + 32, 205, 1, 1, Medium);

        setSpriteControl(5, 5, 240 - 32, 145, 1, 1, Medium);
        setSpriteControl(6, 6, 240, 145, 1, 1, Medium);
        setSpriteControl(7, 7, 240 + 32, 145, 1, 1, Medium);

        setSpriteControl(8, 8, 240 - 32, 85, 1, 1, Medium);
        setSpriteControl(9, 9, 240, 85, 1, 1, Medium);
        setSpriteControl(10, 10, 240 + 32, 85, 1, 1, Medium);
    }
    return 0;
}

void initVideoSetting(){
    *MODE_REGISTER=0x01;
    //initialize background
    setBackGround(1, background_img);
    setBackGroundControl(1, 1, 90, 90, 0, 1);
    initBackGroundPalettes(1, color_palette);

    //initialize frog
    initSpritesPalettes(1, color_palette, Medium);      //palette index 1
    setSprite(1, frog_img, Medium);                     //sprite index 1 for frog
    setSpriteControl(1, 1, 240, 256, 2, 1, Medium);     //control index 1 for frog, z=2

    //initialize wood
    //first set 2,3,4
    setSprite(2, wood_left_img, Medium);
    setSpriteControl(2, 2, 240, 210, 1, 1, Medium);
    setSprite(3, wood_mid_img, Medium);
    setSpriteControl(3, 3, 208, 210, 1, 1, Medium);
    setSprite(4, wood_right_img, Medium);
    setSpriteControl(4, 4, 272, 210, 1, 1, Medium);

    //second set 5,6,7
    setSprite(5, wood_left_img, Medium);
    setSpriteControl(5, 5, 240+80, 150, 1, 1, Medium);
    setSprite(6, wood_mid_img, Medium);
    setSpriteControl(6, 6, 208+80, 150, 1, 1, Medium);
    setSprite(7, wood_right_img, Medium);
    setSpriteControl(7, 7, 272+80, 150, 1, 1, Medium);

    //third set 8,9,10
    setSprite(8, wood_left_img, Medium);
    setSpriteControl(8, 8, 240-40, 85, 1, 1, Medium);
    setSprite(9, wood_mid_img, Medium);
    setSpriteControl(9, 9, 208-40, 85, 1, 1, Medium);
    setSprite(10, wood_right_img, Medium);
    setSpriteControl(10, 10, 272-40, 85, 1, 1, Medium);
    
}