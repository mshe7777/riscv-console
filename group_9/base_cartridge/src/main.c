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
    setModeRegister(0);
    char lose[4] = {'L', 'O', 'S', 'E'};
    print(lose);
  }

  if(status == WIN) {
    setModeRegister(0);
    char lose[3] = {'W', 'I', 'N'};
    print(lose);
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