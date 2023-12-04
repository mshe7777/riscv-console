#include "api.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern uint32_t color_palette[10];
extern uint8_t frog_img[32 * 32];
extern uint8_t wood_left_img[32 * 32];
extern uint8_t wood_mid_img[32 * 32];
extern uint8_t wood_right_img[32 * 32];
extern uint8_t background_img[512 * 288];
extern uint8_t background_color_palette[4 * 16];
extern uint8_t char_g_img[64 * 64];
extern uint8_t char_a_img[64 * 64];
extern uint8_t char_m_img[64 * 64];
extern uint8_t char_e_img[64 * 64];
extern uint8_t char_o_img[64 * 64];
extern uint8_t char_v_img[64 * 64];
extern uint8_t char_r_img[64 * 64];
extern uint8_t char_y_img[64 * 64];
extern uint8_t char_u_img[64 * 64];
extern uint8_t char_w_img[64 * 64];
extern uint8_t char_i_img[64 * 64];
extern uint8_t char_n_img[64 * 64];

void woodMoveThread(void *param);
void frogMoveThread(void *param);
void checkGameOverThread(void *param);

typedef enum { RUN = 0, WIN, LOSE } Status;
volatile Status status = RUN;

int wood1_y = 192;
int wood2_y = 128;
int wood3_y = 64;

struct position {
  uint32_t x;
  uint32_t y;
  uint8_t step;
  MutexId mtx;
};

struct wood {
  int x;
  int y;
  int dir;
};

volatile struct wood woods[3];

ThreadID t1;
ThreadID t2;
ThreadID t3;

int main() {
  initVideoSetting();
  struct position frog;

  frog.x = 240;
  frog.y = 256;
  frog.step = 0;
  frog.mtx = initLock();

  t1 = thread_create_gp(woodMoveThread, &frog, THREAD_MEMORY, High);
  t2 = thread_create_gp(frogMoveThread, &frog, THREAD_MEMORY, High);
  t3 = thread_create_gp(checkGameOverThread, &frog, THREAD_MEMORY, High);

  return 0;
}

void initVideoSetting() {
  *MODE_REGISTER = 0x01;
  // initialize background
  setBackGround(1, background_img);
  setBackGroundControl(1, 1, 0, 0, 0, 1);
  initBackGroundPalettes(1, color_palette);

  // initialize frog
  initSpritesPalettes(1, color_palette, Medium); // palette index 1
  setSprite(1, frog_img, Medium);                // sprite index 1 for frog
  setSpriteControl(1, 1, 240, 256, 2, 1,
                   Medium); // control index 1 for frog, z=2

  // initialize wood
  // first set 2,3,4
  setSprite(2, wood_left_img, Medium);
  setSpriteControl(2, 2, 208, wood1_y, 1, 1, Medium);
  setSprite(3, wood_mid_img, Medium);
  setSpriteControl(3, 3, 240, wood1_y, 1, 1, Medium);
  setSprite(4, wood_right_img, Medium);
  setSpriteControl(4, 4, 272, wood1_y, 1, 1, Medium);

  // second set 5,6,7
  setSprite(5, wood_left_img, Medium);
  setSpriteControl(5, 5, 208 + 80, wood2_y, 1, 1, Medium);
  setSprite(6, wood_mid_img, Medium);
  setSpriteControl(6, 6, 240 + 80, wood2_y, 1, 1, Medium);
  setSprite(7, wood_right_img, Medium);
  setSpriteControl(7, 7, 272 + 80, wood2_y, 1, 1, Medium);

  // third set 8,9,10
  setSprite(8, wood_left_img, Medium);
  setSpriteControl(8, 8, 208 - 40, wood3_y, 1, 1, Medium);
  setSprite(9, wood_mid_img, Medium);
  setSpriteControl(9, 9, 240 - 40, wood3_y, 1, 1, Medium);
  setSprite(10, wood_right_img, Medium);
  setSpriteControl(10, 10, 272 - 40, wood3_y, 1, 1, Medium);
}

void showGameOver() {
  initSpritesPalettes(1, color_palette, Large);
  if (status == WIN) {
    // display YOU WIN
    setSprite(0, char_y_img, Large);
    setSprite(1, char_o_img, Large);
    setSprite(2, char_u_img, Large);
    setSprite(3, char_w_img, Large);
    setSprite(4, char_i_img, Large);
    setSprite(5, char_n_img, Large);
    setSpriteControl(0, 0, 64 + 12, 128, 3, 1, Large);
    setSpriteControl(1, 1, 128 - 5, 128, 3, 1, Large);
    setSpriteControl(2, 2, 192 - 15, 128, 3, 1, Large);
    setSpriteControl(3, 3, 256 + 15, 128, 3, 1, Large);
    setSpriteControl(4, 4, 320 + 5, 128, 3, 1, Large);
    setSpriteControl(5, 5, 384 - 12, 128, 3, 1, Large);
  } else if (status == LOSE) {
    // display GAME OVER
    setSprite(0, char_g_img, Large);
    setSprite(1, char_a_img, Large);
    setSprite(2, char_m_img, Large);
    setSprite(3, char_e_img, Large);
    setSprite(4, char_o_img, Large);
    setSprite(5, char_v_img, Large);
    setSprite(6, char_e_img, Large);
    setSprite(7, char_r_img, Large);
    setSpriteControl(0, 0, 128 + 21, 84, 3, 1, Large);
    setSpriteControl(1, 1, 192 + 6, 84, 3, 1, Large);
    setSpriteControl(2, 2, 256 - 6, 84, 3, 1, Large);
    setSpriteControl(3, 3, 320 - 21, 84, 3, 1, Large);
    setSpriteControl(4, 4, 128 + 21, 160, 3, 1, Large);
    setSpriteControl(5, 5, 192 + 6, 160, 3, 1, Large);
    setSpriteControl(6, 6, 256 - 6, 160, 3, 1, Large);
    setSpriteControl(7, 7, 320 - 21, 160, 3, 1, Large);
  }
}

void woodMoveThread(void *param) {
  struct position *frog = (struct position *)param;

  int last_global = 0;
  woods[0].x = 208;
  woods[1].x = 208 + 80;
  woods[2].x = 208 - 40;
  woods[0].dir = -1;
  woods[1].dir = 1;
  woods[2].dir = -1;

  while (status == RUN) {
    global = getTicks();
    if (global != last_global) {
      // wood move speed
      woods[0].x += woods[0].dir * 5;
      woods[1].x += woods[1].dir * 7;
      woods[2].x += woods[2].dir * 10;

      // position reset over screen
      if ((woods[0].dir == -1 && woods[0].x - 32 <= 0) ||
          (woods[0].dir == 1 && woods[0].x + 64 >= 512))
        woods[0].dir *= -1;
      if ((woods[1].dir == -1 && woods[1].x - 32 <= 0) ||
          (woods[1].dir == 1 && woods[1].x + 64 >= 512))
        woods[1].dir *= -1;
      if ((woods[2].dir == -1 && woods[2].x - 32 <= 0) ||
          (woods[2].dir == 1 && woods[2].x + 64 >= 512))
        woods[2].dir *= -1;

      // moving
      setSpriteControl(2, 2, woods[0].x - 32, wood1_y, 1, 1, Medium);
      setSpriteControl(3, 3, woods[0].x, wood1_y, 1, 1, Medium);
      setSpriteControl(4, 4, woods[0].x + 32, wood1_y, 1, 1, Medium);

      setSpriteControl(5, 5, woods[1].x - 32, wood2_y, 1, 1, Medium);
      setSpriteControl(6, 6, woods[1].x, wood2_y, 1, 1, Medium);
      setSpriteControl(7, 7, woods[1].x + 32, wood2_y, 1, 1, Medium);

      setSpriteControl(8, 8, woods[2].x - 32, wood3_y, 1, 1, Medium);
      setSpriteControl(9, 9, woods[2].x, wood3_y, 1, 1, Medium);
      setSpriteControl(10, 10, woods[2].x + 32, wood3_y, 1, 1, Medium);

      // frog on the wood
      if (frog->step == 3 && abs(frog->x - woods[2].x) < 64) {
        lock(frog->mtx);
        frog->x += woods[2].dir * 10;
        unlock(frog->mtx);
      } else if (frog->step == 2 && abs(frog->x - woods[1].x) < 64) {
        lock(frog->mtx);
        frog->x += woods[1].dir * 7;
        unlock(frog->mtx);
      } else if (frog->step == 1 && abs(frog->x - woods[0].x) < 64) {
        lock(frog->mtx);
        frog->x += woods[0].dir * 5;
        unlock(frog->mtx);
      }
      setSpriteControl(1, 1, frog->x, frog->y, 2, 1, Medium);

      last_global = global;
    }
    thread_yield(t1);
  }
}

void frogMoveThread(void *param) {
  struct position *frog = (struct position *)param;
  int countdown = 0;
  while (status == RUN) {

    if (countdown > 15000) {
      controller_status = getButtonStatus();
      if (controller_status) {
        if (controller_status & 0x1) {
          lock(frog->mtx);
          frog->x -= 10;
          unlock(frog->mtx);
        }

        if (controller_status & 0x2) {
          lock(frog->mtx);
          frog->y -= 64;
          frog->step++;
          unlock(frog->mtx);
        }

        if (controller_status & 0x4) {
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
      countdown = 0;
    }
    countdown++;
    thread_yield(t2);
  }
}

void checkGameOverThread(void *param) {
  struct position *frog = (struct position *)param;
  while (status == RUN) {
    if (frog->step == 4) {
      status = WIN;
    }

    if (frog->step == 3) {
      if (abs(frog->x - woods[2].x) >= 64)
        status = LOSE;
    }

    if (frog->step == 2) {
      if (abs(frog->x - woods[1].x) >= 64)
        status = LOSE;
    }

    if (frog->step == 1) {
      if (abs(frog->x - woods[0].x) >= 64)
        status = LOSE;
    }
  }
  showGameOver();
  thread_exit();
}