#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "systemCalls.h"
#include "VideoSystemCalls.h"
#include "threads.h"


typedef enum { RUN = 0, WIN, LOSE } Status;
Status status = RUN;


/*
void cmdListener() {
  // define cmd listener
}
void videoListener() {
  // define video listener
}
void registerListeners() {
  // set call back handlers with listeners
}
*/


uint32_t global = 0;
uint32_t last_global = 0;
uint8_t step = 0;
uint8_t last_move = 0;
int wood1_dir = -1;
int wood2_dir = 1;
int wood3_dir = -1;
uint32_t light_green = 0xFF0EB037;
uint32_t wood_brown = 0xFF994C1C;
uint32_t river_blue = 0xFF0A1F94;


int main() {
  // set mode to video
  setModeRegister(1);

  // init background data
  Background back;
  uint32_t *background = (uint32_t *)malloc(sizeof(Background));
  background = &back;
  back.mode = 0;
  back.color = river_blue;
  back.typeMode = 0;
  back.position.x = 0;
  back.position.y = 0;
  back.position.z = 0;
  back.index = 0;
  backgroundInit(background);

  // draw the land for background
  SpriteObj land1;
  land1.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  land1.spriteInt = &land1.sprite;
  land1.sprite.type = LARGE;
  land1.sprite.position.x = 0;
  land1.sprite.position.y = -25;
  land1.sprite.position.z = 1;
  land1.sprite.index = 1;
  land1.sprite.color = wood_brown;
  initSprite(land1.spriteInt);

  SpriteObj land2;
  land2.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  land2.spriteInt = &land2.sprite;
  land2.sprite.type = LARGE;
  land2.sprite.position.x = 64;
  land2.sprite.position.y = -25;
  land2.sprite.position.z = 1;
  land2.sprite.index = 2;
  land2.sprite.color = wood_brown;
  initSprite(land2.spriteInt);

  SpriteObj land3;
  land3.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  land3.spriteInt = &land3.sprite;
  land3.sprite.type = LARGE;
  land3.sprite.position.x = 128;
  land3.sprite.position.y = -25;
  land3.sprite.position.z = 1;
  land3.sprite.index = 3;
  land3.sprite.color = wood_brown;
  initSprite(land3.spriteInt);

  SpriteObj land4;
  land4.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  land4.spriteInt = &land4.sprite;
  land4.sprite.type = LARGE;
  land4.sprite.position.x = 192;
  land4.sprite.position.y = -25;
  land4.sprite.position.z = 1;
  land4.sprite.index = 4;
  land4.sprite.color = wood_brown;
  initSprite(land4.spriteInt);

  SpriteObj land5;
  land5.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  land5.spriteInt = &land5.sprite;
  land5.sprite.type = LARGE;
  land5.sprite.position.x = 256;
  land5.sprite.position.y = -25;
  land5.sprite.position.z = 1;
  land5.sprite.index = 5;
  land5.sprite.color = wood_brown;
  initSprite(land5.spriteInt);

  SpriteObj land6;
  land6.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  land6.spriteInt = &land6.sprite;
  land6.sprite.type = LARGE;
  land6.sprite.position.x = 320;
  land6.sprite.position.y = -25;
  land6.sprite.position.z = 1;
  land6.sprite.index = 6;
  land6.sprite.color = wood_brown;
  initSprite(land6.spriteInt);

  SpriteObj land7;
  land7.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  land7.spriteInt = &land7.sprite;
  land7.sprite.type = LARGE;
  land7.sprite.position.x = 384;
  land7.sprite.position.y = -25;
  land7.sprite.position.z = 1;
  land7.sprite.index = 7;
  land7.sprite.color = wood_brown;
  initSprite(land7.spriteInt);

  SpriteObj land8;
  land8.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  land8.spriteInt = &land8.sprite;
  land8.sprite.type = LARGE;
  land8.sprite.position.x = 448;
  land8.sprite.position.y = -25;
  land8.sprite.position.z = 1;
  land8.sprite.index = 8;
  land8.sprite.color = wood_brown;
  initSprite(land8.spriteInt);

  SpriteObj land9;
  land9.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  land9.spriteInt = &land9.sprite;
  land9.sprite.type = LARGE;
  land9.sprite.position.x = 0;
  land9.sprite.position.y = 260;
  land9.sprite.position.z = 1;
  land9.sprite.index = 9;
  land9.sprite.color = wood_brown;
  initSprite(land9.spriteInt);

  SpriteObj land10;
  land10.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  land10.spriteInt = &land10.sprite;
  land10.sprite.type = LARGE;
  land10.sprite.position.x = 64;
  land10.sprite.position.y = 260;
  land10.sprite.position.z = 1;
  land10.sprite.index = 10;
  land10.sprite.color = wood_brown;
  initSprite(land10.spriteInt);

  SpriteObj land11;
  land11.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  land11.spriteInt = &land11.sprite;
  land11.sprite.type = LARGE;
  land11.sprite.position.x = 128;
  land11.sprite.position.y = 260;
  land11.sprite.position.z = 1;
  land11.sprite.index = 11;
  land11.sprite.color = wood_brown;
  initSprite(land11.spriteInt);

  SpriteObj land12;
  land12.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  land12.spriteInt = &land12.sprite;
  land12.sprite.type = LARGE;
  land12.sprite.position.x = 192;
  land12.sprite.position.y = 260;
  land12.sprite.position.z = 1;
  land12.sprite.index = 12;
  land12.sprite.color = wood_brown;
  initSprite(land12.spriteInt);

  SpriteObj land13;
  land13.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  land13.spriteInt = &land13.sprite;
  land13.sprite.type = LARGE;
  land13.sprite.position.x = 256;
  land13.sprite.position.y = 260;
  land13.sprite.position.z = 1;
  land13.sprite.index = 13;
  land13.sprite.color = wood_brown;
  initSprite(land13.spriteInt);

  SpriteObj land14;
  land14.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  land14.spriteInt = &land14.sprite;
  land14.sprite.type = LARGE;
  land14.sprite.position.x = 320;
  land14.sprite.position.y = 260;
  land14.sprite.position.z = 1;
  land14.sprite.index = 14;
  land14.sprite.color = wood_brown;
  initSprite(land14.spriteInt);

  SpriteObj land15;
  land15.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  land15.spriteInt = &land15.sprite;
  land15.sprite.type = LARGE;
  land15.sprite.position.x = 384;
  land15.sprite.position.y = 260;
  land15.sprite.position.z = 1;
  land15.sprite.index = 15;
  land15.sprite.color = wood_brown;
  initSprite(land15.spriteInt);

  SpriteObj land16;
  land16.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  land16.spriteInt = &land16.sprite;
  land16.sprite.type = LARGE;
  land16.sprite.position.x = 448;
  land16.sprite.position.y = 260;
  land16.sprite.position.z = 1;
  land16.sprite.index = 16;
  land16.sprite.color = wood_brown;
  initSprite(land16.spriteInt);


  // init frog data
  SpriteObj frog1;
  frog1.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  frog1.spriteInt = &frog1.sprite;
  frog1.sprite.type = SMALL;
  frog1.sprite.position.x = 240;
  frog1.sprite.position.y = 256;
  frog1.sprite.position.z = 3;
  frog1.sprite.index = 1;
  frog1.sprite.color = light_green;
  initSprite(frog1.spriteInt);

  SpriteObj frog2;
  frog2.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  frog2.spriteInt = &frog2.sprite;
  frog2.sprite.type = SMALL;
  frog2.sprite.position.x = 256;
  frog2.sprite.position.y = 272;
  frog2.sprite.position.z = 3;
  frog2.sprite.index = 2;
  frog2.sprite.color = light_green;
  initSprite(frog2.spriteInt);

  SpriteObj frog3;
  frog3.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  frog3.spriteInt = &frog3.sprite;
  frog3.sprite.type = SMALL;
  frog3.sprite.position.x = 256;
  frog3.sprite.position.y = 256;
  frog3.sprite.position.z = 3;
  frog3.sprite.index = 3;
  frog3.sprite.color = light_green;
  initSprite(frog3.spriteInt);

  SpriteObj frog4;
  frog4.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  frog4.spriteInt = &frog4.sprite;
  frog4.sprite.type = SMALL;
  frog4.sprite.position.x = 240;
  frog4.sprite.position.y = 272;
  frog4.sprite.position.z = 3;
  frog4.sprite.index = 4;
  frog4.sprite.color = light_green;
  initSprite(frog4.spriteInt);

  // init wood data
  // wood 1
  SpriteObj wood_left_1;
  wood_left_1.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  wood_left_1.spriteInt = &wood_left_1.sprite;
  wood_left_1.sprite.type = MEDUIM;
  wood_left_1.sprite.position.x = 208;
  wood_left_1.sprite.position.y = 207;
  wood_left_1.sprite.position.z = 2;
  wood_left_1.sprite.index = 2;
  wood_left_1.sprite.color = wood_brown;
  initSprite(wood_left_1.spriteInt);

  SpriteObj wood_mid_1;
  wood_mid_1.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  wood_mid_1.spriteInt = &wood_mid_1.sprite;
  wood_mid_1.sprite.type = MEDUIM;
  wood_mid_1.sprite.position.x = 240;
  wood_mid_1.sprite.position.y = 207;
  wood_mid_1.sprite.position.z = 2;
  wood_mid_1.sprite.index = 3;
  wood_mid_1.sprite.color = wood_brown;
  initSprite(wood_mid_1.spriteInt);

  SpriteObj wood_right_1;
  wood_right_1.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  wood_right_1.spriteInt = &wood_right_1.sprite;
  wood_right_1.sprite.type = MEDUIM;
  wood_right_1.sprite.position.x = 272;
  wood_right_1.sprite.position.y = 207;
  wood_right_1.sprite.position.z = 2;
  wood_right_1.sprite.index = 4;
  wood_right_1.sprite.color = wood_brown;
  initSprite(wood_right_1.spriteInt);

  // wood 2
  SpriteObj wood_left_2;
  wood_left_2.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  wood_left_2.spriteInt = &wood_left_2.sprite;
  wood_left_2.sprite.type = MEDUIM;
  wood_left_2.sprite.position.x = 208 + 80;
  wood_left_2.sprite.position.y = 143;
  wood_left_2.sprite.position.z = 2;
  wood_left_2.sprite.index = 5;
  wood_left_2.sprite.color = wood_brown;
  initSprite(wood_left_2.spriteInt);

  SpriteObj wood_mid_2;
  wood_mid_2.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  wood_mid_2.spriteInt = &wood_mid_2.sprite;
  wood_mid_2.sprite.type = MEDUIM;
  wood_mid_2.sprite.position.x = 240 + 80;
  wood_mid_2.sprite.position.y = 143;
  wood_mid_2.sprite.position.z = 2;
  wood_mid_2.sprite.index = 6;
  wood_mid_2.sprite.color = wood_brown;
  initSprite(wood_mid_2.spriteInt);

  SpriteObj wood_right_2;
  wood_right_2.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  wood_right_2.spriteInt = &wood_right_2.sprite;
  wood_right_2.sprite.type = MEDUIM;
  wood_right_2.sprite.position.x = 272 + 80;
  wood_right_2.sprite.position.y = 143;
  wood_right_2.sprite.position.z = 2;
  wood_right_2.sprite.index = 7;
  wood_right_2.sprite.color = wood_brown;
  initSprite(wood_right_2.spriteInt);

  // wood 3
  SpriteObj wood_left_3;
  wood_left_3.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  wood_left_3.spriteInt = &wood_left_3.sprite;
  wood_left_3.sprite.type = MEDUIM;
  wood_left_3.sprite.position.x = 208 - 40;
  wood_left_3.sprite.position.y = 79;
  wood_left_3.sprite.position.z = 2;
  wood_left_3.sprite.index = 8;
  wood_left_3.sprite.color = wood_brown;
  initSprite(wood_left_3.spriteInt);

  SpriteObj wood_mid_3;
  wood_mid_3.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  wood_mid_3.spriteInt = &wood_mid_3.sprite;
  wood_mid_3.sprite.type = MEDUIM;
  wood_mid_3.sprite.position.x = 240 - 40;
  wood_mid_3.sprite.position.y = 79;
  wood_mid_3.sprite.position.z = 2;
  wood_mid_3.sprite.index = 9;
  wood_mid_3.sprite.color = wood_brown;
  initSprite(wood_mid_3.spriteInt);

  SpriteObj wood_right_3;
  wood_right_3.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
  wood_right_3.spriteInt = &wood_right_3.sprite;
  wood_right_3.sprite.type = MEDUIM;
  wood_right_3.sprite.position.x = 272 - 40;
  wood_right_3.sprite.position.y = 79;
  wood_right_3.sprite.position.z = 2;
  wood_right_3.sprite.index = 10;
  wood_right_3.sprite.color = wood_brown;
  initSprite(wood_right_3.spriteInt);

  //Sprite *sprites[9] = {wood_left_1, wood_mid_1, wood_right_1, wood_left_2, wood_mid_2, wood_right_2, wood_left_3, wood_mid_3, wood_right_3};
  //moveSprites(sprites, 9);


  while(status == RUN) {
    global = GetTicks();
    if(global - last_global > 2) {
      // wood move
      // wood 1
      wood_left_1.sprite.position.x += wood1_dir * 5;
      wood_mid_1.sprite.position.x += wood1_dir * 5;
      wood_right_1.sprite.position.x += wood1_dir * 5;

      // wood 2
      wood_left_2.sprite.position.x += wood2_dir * 7;
      wood_mid_2.sprite.position.x += wood2_dir * 7;
      wood_right_2.sprite.position.x += wood2_dir * 7;

      // wood 3
      wood_left_3.sprite.position.x += wood3_dir * 10;
      wood_mid_3.sprite.position.x += wood3_dir * 10;
      wood_right_3.sprite.position.x += wood3_dir * 10;

      // wood position reset over screen
      if (wood_left_1.sprite.position.x <= 0) wood1_dir = 1;

      if (wood_right_1.sprite.position.x + 32 >= 512) wood1_dir = -1;

      if (wood_left_2.sprite.position.x <= 0) wood2_dir = 1;

      if (wood_right_2.sprite.position.x + 32 >= 512) wood2_dir = -1;

      if (wood_left_3.sprite.position.x <= 0) wood3_dir = 1;

      if (wood_right_3.sprite.position.x + 32 >= 512) wood3_dir = -1;
      
      // wood moving
      //moveSprites(sprites, 9);
      moveSprite(wood_left_1.spriteInt); 
      moveSprite(wood_mid_1.spriteInt); 
      moveSprite(wood_right_1.spriteInt);
      moveSprite(wood_left_2.spriteInt); 
      moveSprite(wood_mid_2.spriteInt); 
      moveSprite(wood_right_2.spriteInt);
      moveSprite(wood_left_3.spriteInt); 
      moveSprite(wood_mid_3.spriteInt); 
      moveSprite(wood_right_3.spriteInt);

      // frog on the wood
      if (step == 3) {
        frog1.sprite.position.x += wood3_dir * 10;
        frog2.sprite.position.x += wood3_dir * 10;
        frog3.sprite.position.x += wood3_dir * 10;
        frog4.sprite.position.x += wood3_dir * 10;
      } else if (step == 2) {
        frog1.sprite.position.x += wood2_dir * 7;
        frog2.sprite.position.x += wood2_dir * 7;
        frog3.sprite.position.x += wood2_dir * 7;
        frog4.sprite.position.x += wood2_dir * 7;
      } else if (step== 1) {
        frog1.sprite.position.x += wood1_dir * 5;
        frog2.sprite.position.x += wood1_dir * 5;
        frog3.sprite.position.x += wood1_dir * 5;
        frog4.sprite.position.x += wood1_dir * 5;
      }

      // frog move
      controller_status = GetController();
      if(controller_status) {
        if (controller_status & 0x1) {
          frog1.sprite.position.x -= 10;
          frog2.sprite.position.x -= 10;
          frog3.sprite.position.x -= 10;
          frog4.sprite.position.x -= 10;
        }

        if (controller_status & 0x2 && global - last_move > 15) {
          frog1.sprite.position.y -= 64;
          frog2.sprite.position.y -= 64;
          frog3.sprite.position.y -= 64;
          frog4.sprite.position.y -= 64;
          step++;
          last_move = global;
        }

        if (controller_status & 0x4 && global - last_move > 15) {
          if (step == 0) continue;
          frog1.sprite.position.y += 64;
          frog2.sprite.position.y += 64;
          frog3.sprite.position.y += 64;
          frog4.sprite.position.y += 64;
          step--;
          last_move = global;
        }

        if (controller_status & 0x8) {
          frog1.sprite.position.x += 10;
          frog2.sprite.position.x += 10;
          frog3.sprite.position.x += 10;
          frog4.sprite.position.x += 10;
        }
      }
      //moveSprites(sprites, 10);
      moveSprite(frog1.spriteInt);
      moveSprite(frog2.spriteInt);
      moveSprite(frog3.spriteInt);
      moveSprite(frog4.spriteInt);

      // check win or lose
      if (step == 4) status = WIN;

      if (step == 3) {
        if (abs(frog1.sprite.position.x - wood_mid_3.sprite.position.x) >= 64)
          status = LOSE;
      }

      if (step == 2) {
        if (abs(frog1.sprite.position.x - wood_mid_2.sprite.position.x) >= 64)
          status = LOSE;
      }

      if (step == 1) {
        if (abs(frog1.sprite.position.x - wood_mid_1.sprite.position.x) >= 64)
          status = LOSE;
      }

      last_global = global;
    }
  }

  if(status == LOSE) {
    //setModeRegister(0);
    //char lose[4] = {'L', 'O', 'S', 'E'};
    //print(lose);

    SpriteObj L1;
    L1.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    L1.spriteInt = &L1.sprite;
    L1.sprite.type = SMALL;
    L1.sprite.position.x = 100;
    L1.sprite.position.y = 100;
    L1.sprite.position.z = 4;
    L1.sprite.index = 5;
    L1.sprite.color = 0xFFFFFFFF;
    initSprite(L1.spriteInt);

    SpriteObj L2;
    L2.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    L2.spriteInt = &L2.sprite;
    L2.sprite.type = SMALL;
    L2.sprite.position.x = 100;
    L2.sprite.position.y = 116;
    L2.sprite.position.z = 4;
    L2.sprite.index = 6;
    L2.sprite.color = 0xFFFFFFFF;
    initSprite(L2.spriteInt);

    SpriteObj L3;
    L3.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    L3.spriteInt = &L3.sprite;
    L3.sprite.type = SMALL;
    L3.sprite.position.x = 100;
    L3.sprite.position.y = 132;
    L3.sprite.position.z = 4;
    L3.sprite.index = 7;
    L3.sprite.color = 0xFFFFFFFF;
    initSprite(L3.spriteInt);

    SpriteObj L4;
    L4.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    L4.spriteInt = &L4.sprite;
    L4.sprite.type = SMALL;
    L4.sprite.position.x = 100;
    L4.sprite.position.y = 148;
    L4.sprite.position.z = 4;
    L4.sprite.index = 8;
    L4.sprite.color = 0xFFFFFFFF;
    initSprite(L4.spriteInt);

    SpriteObj L5;
    L5.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    L5.spriteInt = &L5.sprite;
    L5.sprite.type = SMALL;
    L5.sprite.position.x = 116;
    L5.sprite.position.y = 164;
    L5.sprite.position.z = 4;
    L5.sprite.index = 9;
    L5.sprite.color = 0xFFFFFFFF;
    initSprite(L5.spriteInt);

    SpriteObj L6;
    L6.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    L6.spriteInt = &L6.sprite;
    L6.sprite.type = SMALL;
    L6.sprite.position.x = 132;
    L6.sprite.position.y = 164;
    L6.sprite.position.z = 4;
    L6.sprite.index = 10;
    L6.sprite.color = 0xFFFFFFFF;
    initSprite(L6.spriteInt);

    SpriteObj L7;
    L7.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    L7.spriteInt = &L7.sprite;
    L7.sprite.type = SMALL;
    L7.sprite.position.x = 100;
    L7.sprite.position.y = 164;
    L7.sprite.position.z = 4;
    L7.sprite.index = 21;
    L7.sprite.color = 0xFFFFFFFF;
    initSprite(L7.spriteInt);

    SpriteObj O1;
    O1.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    O1.spriteInt = &O1.sprite;
    O1.sprite.type = SMALL;
    O1.sprite.position.x = 148 + 16;
    O1.sprite.position.y = 116;
    O1.sprite.position.z = 4;
    O1.sprite.index = 11;
    O1.sprite.color = 0xFFFFFFFF;
    initSprite(O1.spriteInt);

    SpriteObj O2;
    O2.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    O2.spriteInt = &O2.sprite;
    O2.sprite.type = SMALL;
    O2.sprite.position.x = 148 + 16;
    O2.sprite.position.y = 132;
    O2.sprite.position.z = 3;
    O2.sprite.index = 12;
    O2.sprite.color = 0xFFFFFFFF;
    initSprite(O2.spriteInt);

    SpriteObj O3;
    O3.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    O3.spriteInt = &O3.sprite;
    O3.sprite.type = SMALL;
    O3.sprite.position.x = 148 + 16;
    O3.sprite.position.y = 148;
    O3.sprite.position.z = 3;
    O3.sprite.index = 13;
    O3.sprite.color = 0xFFFFFFFF;
    initSprite(O3.spriteInt);

    SpriteObj O4;
    O4.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    O4.spriteInt = &O4.sprite;
    O4.sprite.type = SMALL;
    O4.sprite.position.x = 196 + 16;
    O4.sprite.position.y = 116;
    O4.sprite.position.z = 4;
    O4.sprite.index = 14;
    O4.sprite.color = 0xFFFFFFFF;
    initSprite(O4.spriteInt);

    SpriteObj O5;
    O5.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    O5.spriteInt = &O5.sprite;
    O5.sprite.type = SMALL;
    O5.sprite.position.x = 196 + 16;
    O5.sprite.position.y = 132;
    O5.sprite.position.z = 3;
    O5.sprite.index = 15;
    O5.sprite.color = 0xFFFFFFFF;
    initSprite(O5.spriteInt);

    SpriteObj O6;
    O6.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    O6.spriteInt = &O6.sprite;
    O6.sprite.type = SMALL;
    O6.sprite.position.x = 196 + 16;
    O6.sprite.position.y = 148;
    O6.sprite.position.z = 3;
    O6.sprite.index = 16;
    O6.sprite.color = 0xFFFFFFFF;
    initSprite(O6.spriteInt);

    SpriteObj O7;
    O7.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    O7.spriteInt = &O7.sprite;
    O7.sprite.type = SMALL;
    O7.sprite.position.x = 164 + 16;
    O7.sprite.position.y = 100;
    O7.sprite.position.z = 4;
    O7.sprite.index = 17;
    O7.sprite.color = 0xFFFFFFFF;
    initSprite(O7.spriteInt);

    SpriteObj O8;
    O8.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    O8.spriteInt = &O8.sprite;
    O8.sprite.type = SMALL;
    O8.sprite.position.x = 180 + 16;
    O8.sprite.position.y = 100;
    O8.sprite.position.z = 4;
    O8.sprite.index = 18;
    O8.sprite.color = 0xFFFFFFFF;
    initSprite(O8.spriteInt);

    SpriteObj O9;
    O9.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    O9.spriteInt = &O9.sprite;
    O9.sprite.type = SMALL;
    O9.sprite.position.x = 164 + 16;
    O9.sprite.position.y = 164;
    O9.sprite.position.z = 4;
    O9.sprite.index = 19;
    O9.sprite.color = 0xFFFFFFFF;
    initSprite(O9.spriteInt);

    SpriteObj O10;
    O10.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    O10.spriteInt = &O10.sprite;
    O10.sprite.type = SMALL;
    O10.sprite.position.x = 180 + 16;
    O10.sprite.position.y = 164;
    O10.sprite.position.z = 4;
    O10.sprite.index = 20;
    O10.sprite.color = 0xFFFFFFFF;
    initSprite(O10.spriteInt);

    SpriteObj S1;
    S1.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    S1.spriteInt = &S1.sprite;
    S1.sprite.type = SMALL;
    S1.sprite.position.x = 180 + 16 + 16 + 16 + 16;
    S1.sprite.position.y = 164;
    S1.sprite.position.z = 4;
    S1.sprite.index = 22;
    S1.sprite.color = 0xFFFFFFFF;
    initSprite(S1.spriteInt);

    SpriteObj S2;
    S2.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    S2.spriteInt = &S2.sprite;
    S2.sprite.type = SMALL;
    S2.sprite.position.x = 180 + 16 + 16 + 16 + 16 + 16;
    S2.sprite.position.y = 164;
    S2.sprite.position.z = 4;
    S2.sprite.index = 23;
    S2.sprite.color = 0xFFFFFFFF;
    initSprite(S2.spriteInt);

    SpriteObj S3;
    S3.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    S3.spriteInt = &S3.sprite;
    S3.sprite.type = SMALL;
    S3.sprite.position.x = 180 + 16 + 16 + 16 + 16 + 16 + 16;
    S3.sprite.position.y = 164;
    S3.sprite.position.z = 4;
    S3.sprite.index = 24;
    S3.sprite.color = 0xFFFFFFFF;
    initSprite(S3.spriteInt);

    SpriteObj S4;
    S4.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    S4.spriteInt = &S4.sprite;
    S4.sprite.type = SMALL;
    S4.sprite.position.x = 180 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    S4.sprite.position.y = 164 - 16;
    S4.sprite.position.z = 4;
    S4.sprite.index = 25;
    S4.sprite.color = 0xFFFFFFFF;
    initSprite(S4.spriteInt);

    SpriteObj S5;
    S5.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    S5.spriteInt = &S5.sprite;
    S5.sprite.type = SMALL;
    S5.sprite.position.x = 180 + 16 + 16 + 16 + 16 + 16 + 16;
    S5.sprite.position.y = 164 - 16 - 16;
    S5.sprite.position.z = 4;
    S5.sprite.index = 26;
    S5.sprite.color = 0xFFFFFFFF;
    initSprite(S5.spriteInt);

    SpriteObj S6;
    S6.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    S6.spriteInt = &S6.sprite;
    S6.sprite.type = SMALL;
    S6.sprite.position.x = 180 + 16 + 16 + 16 + 16 + 16;
    S6.sprite.position.y = 164 - 16 - 16;
    S6.sprite.position.z = 4;
    S6.sprite.index = 27;
    S6.sprite.color = 0xFFFFFFFF;
    initSprite(S6.spriteInt);

    SpriteObj S7;
    S7.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    S7.spriteInt = &S7.sprite;
    S7.sprite.type = SMALL;
    S7.sprite.position.x = 180 + 16 + 16 + 16 + 16;
    S7.sprite.position.y = 164 - 16 - 16 - 16;
    S7.sprite.position.z = 4;
    S7.sprite.index = 28;
    S7.sprite.color = 0xFFFFFFFF;
    initSprite(S7.spriteInt);

    SpriteObj S8;
    S8.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    S8.spriteInt = &S8.sprite;
    S8.sprite.type = SMALL;
    S8.sprite.position.x = 180 + 16 + 16 + 16 + 16 + 16;
    S8.sprite.position.y = 164 - 16 - 16 - 16 - 16;
    S8.sprite.position.z = 4;
    S8.sprite.index = 29;
    S8.sprite.color = 0xFFFFFFFF;
    initSprite(S8.spriteInt);

    SpriteObj S9;
    S9.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    S9.spriteInt = &S9.sprite;
    S9.sprite.type = SMALL;
    S9.sprite.position.x = 180 + 16 + 16 + 16 + 16 + 16 + 16;
    S9.sprite.position.y = 164 - 16 - 16 - 16 - 16;
    S9.sprite.position.z = 4;
    S9.sprite.index = 30;
    S9.sprite.color = 0xFFFFFFFF;
    initSprite(S9.spriteInt);

    SpriteObj S10;
    S10.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    S10.spriteInt = &S10.sprite;
    S10.sprite.type = SMALL;
    S10.sprite.position.x = 180 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    S10.sprite.position.y = 164 - 16 - 16 - 16 - 16;
    S10.sprite.position.z = 4;
    S10.sprite.index = 31;
    S10.sprite.color = 0xFFFFFFFF;
    initSprite(S10.spriteInt);

    SpriteObj E1;
    E1.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    E1.spriteInt = &E1.sprite;
    E1.sprite.type = SMALL;
    E1.sprite.position.x = 180 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    E1.sprite.position.y = 164 - 16 - 16 - 16 - 16;
    E1.sprite.position.z = 4;
    E1.sprite.index = 32;
    E1.sprite.color = 0xFFFFFFFF;
    initSprite(E1.spriteInt);

    SpriteObj E2;
    E2.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    E2.spriteInt = &E2.sprite;
    E2.sprite.type = SMALL;
    E2.sprite.position.x = 180 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    E2.sprite.position.y = 164 - 16 - 16 - 16 - 16;
    E2.sprite.position.z = 4;
    E2.sprite.index = 33;
    E2.sprite.color = 0xFFFFFFFF;
    initSprite(E2.spriteInt);

    SpriteObj E3;
    E3.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    E3.spriteInt = &E3.sprite;
    E3.sprite.type = SMALL;
    E3.sprite.position.x = 180 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    E3.sprite.position.y = 164 - 16 - 16 - 16 - 16;
    E3.sprite.position.z = 4;
    E3.sprite.index = 34;
    E3.sprite.color = 0xFFFFFFFF;
    initSprite(E3.spriteInt);

    SpriteObj E4;
    E4.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    E4.spriteInt = &E4.sprite;
    E4.sprite.type = SMALL;
    E4.sprite.position.x = 180 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    E4.sprite.position.y = 164 - 16 - 16 - 16 - 16;
    E4.sprite.position.z = 4;
    E4.sprite.index = 35;
    E4.sprite.color = 0xFFFFFFFF;
    initSprite(E4.spriteInt);

    SpriteObj E5;
    E5.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    E5.spriteInt = &E5.sprite;
    E5.sprite.type = SMALL;
    E5.sprite.position.x = 180 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    E5.sprite.position.y = 164 - 16 - 16 - 16;
    E5.sprite.position.z = 4;
    E5.sprite.index = 36;
    E5.sprite.color = 0xFFFFFFFF;
    initSprite(E5.spriteInt);

    SpriteObj E6;
    E6.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    E6.spriteInt = &E6.sprite;
    E6.sprite.type = SMALL;
    E6.sprite.position.x = 180 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    E6.sprite.position.y = 164 - 16 - 16;
    E6.sprite.position.z = 4;
    E6.sprite.index = 37;
    E6.sprite.color = 0xFFFFFFFF;
    initSprite(E6.spriteInt);

    SpriteObj E7;
    E7.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    E7.spriteInt = &E7.sprite;
    E7.sprite.type = SMALL;
    E7.sprite.position.x = 180 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    E7.sprite.position.y = 164 - 16;
    E7.sprite.position.z = 4;
    E7.sprite.index = 38;
    E7.sprite.color = 0xFFFFFFFF;
    initSprite(E7.spriteInt);

    SpriteObj E8;
    E8.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    E8.spriteInt = &E8.sprite;
    E8.sprite.type = SMALL;
    E8.sprite.position.x = 180 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    E8.sprite.position.y = 164;
    E8.sprite.position.z = 4;
    E8.sprite.index = 39;
    E8.sprite.color = 0xFFFFFFFF;
    initSprite(E8.spriteInt);

    SpriteObj E9;
    E9.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    E9.spriteInt = &E9.sprite;
    E9.sprite.type = SMALL;
    E9.sprite.position.x = 180 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    E9.sprite.position.y = 164 - 16 - 16;
    E9.sprite.position.z = 4;
    E9.sprite.index = 43;
    E9.sprite.color = 0xFFFFFFFF;
    initSprite(E9.spriteInt);

    SpriteObj E10;
    E10.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    E10.spriteInt = &E10.sprite;
    E10.sprite.type = SMALL;
    E10.sprite.position.x = 180 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    E10.sprite.position.y = 164 - 16 - 16;
    E10.sprite.position.z = 4;
    E10.sprite.index = 44;
    E10.sprite.color = 0xFFFFFFFF;
    initSprite(E10.spriteInt);

    SpriteObj E11;
    E11.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    E11.spriteInt = &E11.sprite;
    E11.sprite.type = SMALL;
    E11.sprite.position.x = 180 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    E11.sprite.position.y = 164;
    E11.sprite.position.z = 4;
    E11.sprite.index = 40;
    E11.sprite.color = 0xFFFFFFFF;
    initSprite(E11.spriteInt);

    SpriteObj E12;
    E12.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    E12.spriteInt = &E12.sprite;
    E12.sprite.type = SMALL;
    E12.sprite.position.x = 180 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    E12.sprite.position.y = 164;
    E12.sprite.position.z = 4;
    E12.sprite.index = 41;
    E12.sprite.color = 0xFFFFFFFF;
    initSprite(E12.spriteInt);

    SpriteObj E13;
    E13.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    E13.spriteInt = &E13.sprite;
    E13.sprite.type = SMALL;
    E13.sprite.position.x = 180 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    E13.sprite.position.y = 164;
    E13.sprite.position.z = 4;
    E13.sprite.index = 42;
    E13.sprite.color = 0xFFFFFFFF;
    initSprite(E13.spriteInt);
  }

  if(status == WIN) {
    //setModeRegister(0);
    //char lose[3] = {'W', 'I', 'N'};
    //print(lose);
    SpriteObj W1;
    W1.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    W1.spriteInt = &W1.sprite;
    W1.sprite.type = SMALL;
    W1.sprite.position.x = 100;
    W1.sprite.position.y = 100;
    W1.sprite.position.z = 4;
    W1.sprite.index = 43;
    W1.sprite.color = 0xFFFFFFFF;
    initSprite(W1.spriteInt);

    SpriteObj W2;
    W2.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    W2.spriteInt = &W2.sprite;
    W2.sprite.type = SMALL;
    W2.sprite.position.x = 100;
    W2.sprite.position.y = 100 + 16;
    W2.sprite.position.z = 4;
    W2.sprite.index = 44;
    W2.sprite.color = 0xFFFFFFFF;
    initSprite(W2.spriteInt);

    SpriteObj W3;
    W3.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    W3.spriteInt = &W3.sprite;
    W3.sprite.type = SMALL;
    W3.sprite.position.x = 100;
    W3.sprite.position.y = 100 + 16  + 16;
    W3.sprite.position.z = 4;
    W3.sprite.index = 45;
    W3.sprite.color = 0xFFFFFFFF;
    initSprite(W3.spriteInt);

    SpriteObj W4;
    W4.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    W4.spriteInt = &W4.sprite;
    W4.sprite.type = SMALL;
    W4.sprite.position.x = 100;
    W4.sprite.position.y = 100 + 16 + 16 + 16;
    W4.sprite.position.z = 4;
    W4.sprite.index = 46;
    W4.sprite.color = 0xFFFFFFFF;
    initSprite(W4.spriteInt);

    SpriteObj W5;
    W5.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    W5.spriteInt = &W5.sprite;
    W5.sprite.type = SMALL;
    W5.sprite.position.x = 100 + 16;
    W5.sprite.position.y = 100 + 16 + 16 + 16 + 16;
    W5.sprite.position.z = 4;
    W5.sprite.index = 47;
    W5.sprite.color = 0xFFFFFFFF;
    initSprite(W5.spriteInt);

    SpriteObj W6;
    W6.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    W6.spriteInt = &W6.sprite;
    W6.sprite.type = SMALL;
    W6.sprite.position.x = 100 + 16 + 16;
    W6.sprite.position.y = 100 + 16 + 16 + 16;
    W6.sprite.position.z = 4;
    W6.sprite.index = 48;
    W6.sprite.color = 0xFFFFFFFF;
    initSprite(W6.spriteInt);

    SpriteObj W7;
    W7.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    W7.spriteInt = &W7.sprite;
    W7.sprite.type = SMALL;
    W7.sprite.position.x = 100 + 16 + 16 + 16;
    W7.sprite.position.y = 100 + 16 + 16 + 16 + 16;
    W7.sprite.position.z = 4;
    W7.sprite.index = 49;
    W7.sprite.color = 0xFFFFFFFF;
    initSprite(W7.spriteInt);

    SpriteObj W8;
    W8.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    W8.spriteInt = &W8.sprite;
    W8.sprite.type = SMALL;
    W8.sprite.position.x = 100 + 16 + 16 + 16 + 16;
    W8.sprite.position.y = 100 + 16 + 16 + 16;
    W8.sprite.position.z = 4;
    W8.sprite.index = 50;
    W8.sprite.color = 0xFFFFFFFF;
    initSprite(W8.spriteInt);

    SpriteObj W9;
    W9.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    W9.spriteInt = &W9.sprite;
    W9.sprite.type = SMALL;
    W9.sprite.position.x = 100 + 16 + 16 + 16 + 16;
    W9.sprite.position.y = 100 + 16 + 16;
    W9.sprite.position.z = 4;
    W9.sprite.index = 51;
    W9.sprite.color = 0xFFFFFFFF;
    initSprite(W9.spriteInt);

    SpriteObj W10;
    W10.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    W10.spriteInt = &W10.sprite;
    W10.sprite.type = SMALL;
    W10.sprite.position.x = 100 + 16 + 16 + 16 + 16;
    W10.sprite.position.y = 100 + 16;
    W10.sprite.position.z = 4;
    W10.sprite.index = 52;
    W10.sprite.color = 0xFFFFFFFF;
    initSprite(W10.spriteInt);

    SpriteObj W11;
    W11.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    W11.spriteInt = &W11.sprite;
    W11.sprite.type = SMALL;
    W11.sprite.position.x = 100 + 16 + 16 + 16 + 16;
    W11.sprite.position.y = 100;
    W11.sprite.position.z = 4;
    W11.sprite.index = 53;
    W11.sprite.color = 0xFFFFFFFF;
    initSprite(W11.spriteInt);

    SpriteObj I1;
    I1.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    I1.spriteInt = &I1.sprite;
    I1.sprite.type = SMALL;
    I1.sprite.position.x = 100 + 16 + 16 + 16 + 16 + 16 + 16;
    I1.sprite.position.y = 100;
    I1.sprite.position.z = 4;
    I1.sprite.index = 54;
    I1.sprite.color = 0xFFFFFFFF;
    initSprite(I1.spriteInt);

    SpriteObj I2;
    I2.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    I2.spriteInt = &I2.sprite;
    I2.sprite.type = SMALL;
    I2.sprite.position.x = 100 + 16 + 16 + 16 + 16 + 16 + 16;
    I2.sprite.position.y = 100 + 16;
    I2.sprite.position.z = 4;
    I2.sprite.index = 55;
    I2.sprite.color = 0xFFFFFFFF;
    initSprite(I2.spriteInt);

    SpriteObj I3;
    I3.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    I3.spriteInt = &I3.sprite;
    I3.sprite.type = SMALL;
    I3.sprite.position.x = 100 + 16 + 16 + 16 + 16 + 16 + 16;
    I3.sprite.position.y = 100 + 16 + 16;
    I3.sprite.position.z = 4;
    I3.sprite.index = 56;
    I3.sprite.color = 0xFFFFFFFF;
    initSprite(I3.spriteInt);

    SpriteObj I4;
    I4.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    I4.spriteInt = &I4.sprite;
    I4.sprite.type = SMALL;
    I4.sprite.position.x = 100 + 16 + 16 + 16 + 16 + 16 + 16;
    I4.sprite.position.y = 100 + 16 + 16 + 16;
    I4.sprite.position.z = 4;
    I4.sprite.index = 57;
    I4.sprite.color = 0xFFFFFFFF;
    initSprite(I4.spriteInt);

    SpriteObj I5;
    I5.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    I5.spriteInt = &I5.sprite;
    I5.sprite.type = SMALL;
    I5.sprite.position.x = 100 + 16 + 16 + 16 + 16 + 16 + 16;
    I5.sprite.position.y = 100 + 16 + 16 + 16 + 16;
    I5.sprite.position.z = 4;
    I5.sprite.index = 58;
    I5.sprite.color = 0xFFFFFFFF;
    initSprite(I5.spriteInt);

    SpriteObj N1;
    N1.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    N1.spriteInt = &N1.sprite;
    N1.sprite.type = SMALL;
    N1.sprite.position.x = 100 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    N1.sprite.position.y = 100;
    N1.sprite.position.z = 4;
    N1.sprite.index = 59;
    N1.sprite.color = 0xFFFFFFFF;
    initSprite(N1.spriteInt);

    SpriteObj N2;
    N2.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    N2.spriteInt = &N2.sprite;
    N2.sprite.type = SMALL;
    N2.sprite.position.x = 100 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    N2.sprite.position.y = 100 + 16;
    N2.sprite.position.z = 4;
    N2.sprite.index = 60;
    N2.sprite.color = 0xFFFFFFFF;
    initSprite(N2.spriteInt);

    SpriteObj N3;
    N3.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    N3.spriteInt = &N3.sprite;
    N3.sprite.type = SMALL;
    N3.sprite.position.x = 100 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    N3.sprite.position.y = 100 + 16 + 16;
    N3.sprite.position.z = 4;
    N3.sprite.index = 61;
    N3.sprite.color = 0xFFFFFFFF;
    initSprite(N3.spriteInt);

    SpriteObj N4;
    N4.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    N4.spriteInt = &N4.sprite;
    N4.sprite.type = SMALL;
    N4.sprite.position.x = 100 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    N4.sprite.position.y = 100 + 16 + 16 + 16;
    N4.sprite.position.z = 4;
    N4.sprite.index = 62;
    N4.sprite.color = 0xFFFFFFFF;
    initSprite(N4.spriteInt);

    SpriteObj N5;
    N5.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    N5.spriteInt = &N5.sprite;
    N5.sprite.type = SMALL;
    N5.sprite.position.x = 100 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    N5.sprite.position.y = 100 + 16 + 16 + 16 + 16;
    N5.sprite.position.z = 4;
    N5.sprite.index = 63;
    N5.sprite.color = 0xFFFFFFFF;
    initSprite(N5.spriteInt);

    SpriteObj N6;
    N6.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    N6.spriteInt = &N6.sprite;
    N6.sprite.type = SMALL;
    N6.sprite.position.x = 100 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    N6.sprite.position.y = 100 + 16;
    N6.sprite.position.z = 4;
    N6.sprite.index = 64;
    N6.sprite.color = 0xFFFFFFFF;
    initSprite(N6.spriteInt);

    SpriteObj N7;
    N7.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    N7.spriteInt = &N7.sprite;
    N7.sprite.type = SMALL;
    N7.sprite.position.x = 100 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    N7.sprite.position.y = 100 + 16 + 16;
    N7.sprite.position.z = 4;
    N7.sprite.index = 65;
    N7.sprite.color = 0xFFFFFFFF;
    initSprite(N7.spriteInt);

    SpriteObj N8;
    N8.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    N8.spriteInt = &N8.sprite;
    N8.sprite.type = SMALL;
    N8.sprite.position.x = 100 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    N8.sprite.position.y = 100;
    N8.sprite.position.z = 4;
    N8.sprite.index = 66;
    N8.sprite.color = 0xFFFFFFFF;
    initSprite(N8.spriteInt);

    SpriteObj N9;
    N9.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    N9.spriteInt = &N9.sprite;
    N9.sprite.type = SMALL;
    N9.sprite.position.x = 100 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    N9.sprite.position.y = 100 + 16;
    N9.sprite.position.z = 4;
    N9.sprite.index = 67;
    N9.sprite.color = 0xFFFFFFFF;
    initSprite(N9.spriteInt);

    SpriteObj N10;
    N10.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    N10.spriteInt = &N10.sprite;
    N10.sprite.type = SMALL;
    N10.sprite.position.x = 100 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    N10.sprite.position.y = 100 + 16 + 16;
    N10.sprite.position.z = 4;
    N10.sprite.index = 68;
    N10.sprite.color = 0xFFFFFFFF;
    initSprite(N10.spriteInt);

    SpriteObj N11;
    N11.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    N11.spriteInt = &N11.sprite;
    N11.sprite.type = SMALL;
    N11.sprite.position.x = 100 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    N11.sprite.position.y = 100 + 16 + 16 + 16;
    N11.sprite.position.z = 4;
    N11.sprite.index = 69;
    N11.sprite.color = 0xFFFFFFFF;
    initSprite(N11.spriteInt);

    SpriteObj N12;
    N12.spriteInt = (uint32_t *)malloc(sizeof(Sprite));
    N12.spriteInt = &N12.sprite;
    N12.sprite.type = SMALL;
    N12.sprite.position.x = 100 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16 + 16;
    N12.sprite.position.y = 100 + 16 + 16 + 16 + 16;
    N12.sprite.position.z = 4;
    N12.sprite.index = 70;
    N12.sprite.color = 0xFFFFFFFF;
    initSprite(N12.spriteInt);

  }

  while(1){};

  return 0;
}

/*
void frogMoveThread(void *param) {
  struct position *frog = (struct position *)param;
  int counter2 = 0;
  int last_counter2 = 0;
  while (status == RUN) {
    counter2 = getTicks();
    if (counter2 - last_counter2 >= 1) {  //set frequency here
      controller_status = getButtonStatus();
      if (controller_status) {
        if (controller_status & 0x1) {
          lock(frog->mtx);
          frog->x -= 10;
          unlock(frog->mtx);
        }

        if (controller_status & 0x2) {
          if (counter2 - last_counter2 < 5) continue;
          lock(frog->mtx);
          frog->y -= 64;
          frog->step++;
          unlock(frog->mtx);
        }

        if (controller_status & 0x4) {
          if (frog->step == 0 || counter2 - last_counter2 < 5) continue;
          lock(frog->mtx);
          frog->y += 64;
          frog->step--;
          unlock(frog->mtx);
        }

        if (controller_status & 0x8) {
          lock(frog->mtx);
          frog->x += 10;
          unlock(frog->mtx);
        }
      }
      setSpriteControl(1, 1, frog->x, frog->y, 2, 1, Medium);
      last_counter2 = counter2;
    }
  }
}
*/