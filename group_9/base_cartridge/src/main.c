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
//Sprite *frog;
//Sprite *wood_left_1;
//Sprite *wood_mid_1;
//Sprite *wood_right_1;
//Sprite *wood_left_2;
//Sprite *wood_mid_2;
//Sprite *wood_right_2;
//Sprite *wood_left_3;
//Sprite *wood_mid_3;
//Sprite *wood_right_3;
//Sprite *sprites[10];

int main() {
  // set mode to video
  setModeRegister(1);

  // init frog data
  Sprite *frog;
  frog->type = MEDUIM;
  frog->position.x = 240;
  frog->position.y = 256;
  frog->position.z = 3;
  frog->index = 1;
  frog->color = 0xFF0EB037;
  initSprite(frog);

  // init wood data
  // wood 1
  Sprite *wood_left_1;
  wood_left_1->type = MEDUIM;
  wood_left_1->position.x = 208;
  wood_left_1->position.y = 192;
  wood_left_1->position.z = 2;
  wood_left_1->index = 2;
  wood_left_1->color = 0xFF994C1C;
  initSprite(wood_left_1);

  Sprite *wood_mid_1;
  wood_mid_1->type = MEDUIM;
  wood_mid_1->position.x = 240;
  wood_mid_1->position.y = 192;
  wood_mid_1->position.z = 2;
  wood_mid_1->index = 3;
  wood_mid_1->color = 0xFF994C1C;
  initSprite(wood_mid_1);

  Sprite *wood_right_1;
  wood_right_1->type = MEDUIM;
  wood_right_1->position.x = 272;
  wood_right_1->position.y = 192;
  wood_right_1->position.z = 2;
  wood_right_1->index = 4;
  wood_right_1->color = 0xFF994C1C;
  initSprite(wood_right_1);

  // wood 2
  Sprite *wood_left_2;
  wood_left_2->type = MEDUIM;
  wood_left_2->position.x = 208 + 80;
  wood_left_2->position.y = 128;
  wood_left_2->position.z = 2;
  wood_left_2->index = 5;
  wood_left_2->color = 0xFF994C1C;
  initSprite(wood_left_2);

  Sprite *wood_mid_2;
  wood_mid_2->type = MEDUIM;
  wood_mid_2->position.x = 240 + 80;
  wood_mid_2->position.y = 128;
  wood_mid_2->position.z = 2;
  wood_mid_2->index = 6;
  wood_mid_2->color = 0xFF994C1C;
  initSprite(wood_mid_2);

  Sprite *wood_right_2;
  wood_right_2->type = MEDUIM;
  wood_right_2->position.x = 272 + 80;
  wood_right_2->position.y = 128;
  wood_right_2->position.z = 2;
  wood_right_2->index = 7;
  wood_right_2->color = 0xFF994C1C;
  initSprite(wood_right_2);

  // wood 3
  Sprite *wood_left_3;
  wood_left_3->type = MEDUIM;
  wood_left_3->position.x = 208 - 40;
  wood_left_3->position.y = 64;
  wood_left_3->position.z = 2;
  wood_left_3->index = 8;
  wood_left_3->color = 0xFF994C1C;
  initSprite(wood_left_3);

  Sprite *wood_mid_3;
  wood_mid_3->type = MEDUIM;
  wood_mid_3->position.x = 240 - 40;
  wood_mid_3->position.y = 64;
  wood_mid_3->position.z = 2;
  wood_mid_3->index = 9;
  wood_mid_3->color = 0xFF994C1C;
  initSprite(wood_mid_3);

  Sprite *wood_right_3;
  wood_right_3->type = MEDUIM;
  wood_right_3->position.x = 272 - 40;
  wood_right_3->position.y = 64;
  wood_right_3->position.z = 2;
  wood_right_3->index = 10;
  wood_right_3->color = 0xFF994C1C;
  initSprite(wood_right_3);

  Sprite *sprites[9] = {wood_left_1, wood_mid_1, wood_right_1, wood_left_2, wood_mid_2, wood_right_2, wood_left_3, wood_mid_3, wood_right_3};
  //moveSprites(sprites, 9);

  // init background data
  //Background *background;
  //background->mode = 0;
  //background->typeMode = 0;
  //background->position.x = 100;
  //background->position.y = 100;
  //background->position.z = 0;
  //background->color = 0xFF0A1F94;
  //background->index = 0;
  //backgroundInit(background);
  
  while(status != RUN) {

  }

  while(status == RUN) {
    global = GetTicks();
    if(global != last_global) {
      // wood move
      // wood 1
      wood_left_1->position.x += wood1_dir * 5;
      wood_mid_1->position.x += wood1_dir * 5;
      wood_right_1->position.x += wood1_dir * 5;

      // wood 2
      wood_left_2->position.x += wood2_dir * 7;
      wood_mid_2->position.x += wood2_dir * 7;
      wood_right_2->position.x += wood2_dir * 7;

      // wood 3
      wood_left_3->position.x += wood3_dir * 10;
      wood_mid_3->position.x += wood3_dir * 10;
      wood_right_3->position.x += wood3_dir * 10;

      // wood position reset over screen
      if (wood_left_1->position.x <= 0) wood1_dir = 1;

      if (wood_right_1->position.x + 32 >= 512) wood1_dir = -1;

      if (wood_left_2->position.x <= 0) wood2_dir = 1;

      if (wood_right_2->position.x + 32 >= 512) wood2_dir = -1;

      if (wood_left_3->position.x <= 0) wood3_dir = 1;

      if (wood_right_3->position.x + 32 >= 512) wood3_dir = -1;
      
      // wood moving
      //moveSprites(sprites, 9);
      moveSprite(wood_left_1); 
      moveSprite(wood_mid_1); 
      moveSprite(wood_right_1);
      moveSprite(wood_left_2); 
      moveSprite(wood_mid_2); 
      moveSprite(wood_right_2);
      moveSprite(wood_left_3); 
      moveSprite(wood_mid_3); 
      moveSprite(wood_right_3);

      // frog on the wood
      if (step == 3) {
        frog->position.x += wood3_dir * 10;
      } else if (step == 2) {
        frog->position.x += wood2_dir * 7;
      } else if (step== 1) {
        frog->position.x += wood1_dir * 5;
      }

      // frog move
      controller_status = GetController();
      if(controller_status) {
        if (controller_status & 0x1) {
          frog->position.x -= 10;
        }

        if (controller_status & 0x2 && global - last_move > 5) {
          frog->position.y -= 64;
          step++;
          last_move = global;
        }

        if (controller_status & 0x4 && (step == 0 || global - last_move > 5)) {
          frog->position.y += 64;
          step--;
          last_move = global;
        }

        if (controller_status & 0x8) {
          frog->position.x += 10;
        }
      }
      //moveSprites(sprites, 10);
      moveSprite(frog);
      last_global = global;
    }
  }

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