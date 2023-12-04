#include "api.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef enum { RUN = 0, WIN, LOSE } Status;
volatile Status status = RUN;

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

int wood1_y = 192;
int wood2_y = 128;
int wood3_y = 64;

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

  int wood1_x = 208;
  int wood2_x = wood1_x + 80;
  int wood3_x = wood1_x - 40;
  int wood1_dir = -1;
  int wood2_dir = 1;
  int wood3_dir = -1;

  while (status == RUN) {

    ////Wood move thread
    global = getTicks();
    if (global != last_global) {
      // wood move speed
      wood1_x += wood1_dir * 5;
      wood2_x += wood2_dir * 7;
      wood3_x += wood3_dir * 10;

      // position reset over screen
      if ((wood1_dir == -1 && wood1_x - 32 <= 0) ||
          (wood1_dir == 1 && wood1_x + 64 >= 512))
        wood1_dir *= -1;
      if ((wood2_dir == -1 && wood2_x - 32 <= 0) ||
          (wood2_dir == 1 && wood2_x + 64 >= 512))
        wood2_dir *= -1;
      if ((wood3_dir == -1 && wood3_x - 32 <= 0) ||
          (wood3_dir == 1 && wood3_x + 64 >= 512))
        wood3_dir *= -1;

      // moving
      setSpriteControl(2, 2, wood1_x - 32, wood1_y, 1, 1, Medium);
      setSpriteControl(3, 3, wood1_x, wood1_y, 1, 1, Medium);
      setSpriteControl(4, 4, wood1_x + 32, wood1_y, 1, 1, Medium);

      setSpriteControl(5, 5, wood2_x - 32, wood2_y, 1, 1, Medium);
      setSpriteControl(6, 6, wood2_x, wood2_y, 1, 1, Medium);
      setSpriteControl(7, 7, wood2_x + 32, wood2_y, 1, 1, Medium);

      setSpriteControl(8, 8, wood3_x - 32, wood3_y, 1, 1, Medium);
      setSpriteControl(9, 9, wood3_x, wood3_y, 1, 1, Medium);
      setSpriteControl(10, 10, wood3_x + 32, wood3_y, 1, 1, Medium);

      // frog on the wood
      if (frog.step == 3 && abs(frog.x - wood3_x) < 64) {
        lock(frog.mtx);
        frog.x += wood3_dir * 10;
        unlock(frog.mtx);
      } else if (frog.step == 2 && abs(frog.x - wood2_x) < 64) {
        lock(frog.mtx);
        frog.x += wood2_dir * 7;
        unlock(frog.mtx);
      } else if (frog.step == 1 && abs(frog.x - wood1_x) < 64) {
        lock(frog.mtx);
        frog.x += wood1_dir * 5;
        unlock(frog.mtx);
      }
      lock(frog.mtx);
      setSpriteControl(1, 1, frog.x, frog.y, 2, 1, Medium);
      unlock(frog.mtx);

      last_global = global;
    }

    // Frog move thread
    if (countdown > 15000) {
      controller_status = getButtonStatus();
      if (controller_status) {
        if (controller_status & 0x1) {
          lock(frog.mtx);
          frog.x -= 10;
          unlock(frog.mtx);
        }

        if (controller_status & 0x2) {
          lock(frog.mtx);
          frog.y -= 64;
          frog.step++;
          unlock(frog.mtx);
        }

        if (controller_status & 0x4) {
          lock(frog.mtx);
          frog.y += 64;
          frog.step--;
          unlock(frog.mtx);
        }

        if (controller_status & 0x8) {
          lock(frog.mtx);
          frog.x += 10;
          unlock(frog.mtx);
        }
      }
      lock(frog.mtx);
      setSpriteControl(1, 1, frog.x, frog.y, 2, 1, Medium);
      unlock(frog.mtx);
      countdown = 0;
    }
    countdown++;

    // Game over check thread
    if (frog.step == 4) {
      status = WIN;
    }

    if (frog.step == 3) {
      if (abs(frog.x - wood3_x) >= 64)
        status = LOSE;
    }

    if (frog.step == 2) {
      if (abs(frog.x - wood2_x) >= 64)
        status = LOSE;
    }

    if (frog.step == 1) {
      if (abs(frog.x - wood1_x) >= 64)
        status = LOSE;
    }
  }

  // Game over graph
  showGameOver();

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
  setSpriteControl(2, 2, 240, wood1_y, 1, 1, Medium);
  setSprite(3, wood_mid_img, Medium);
  setSpriteControl(3, 3, 208, wood1_y, 1, 1, Medium);
  setSprite(4, wood_right_img, Medium);
  setSpriteControl(4, 4, 272, wood1_y, 1, 1, Medium);

  // second set 5,6,7
  setSprite(5, wood_left_img, Medium);
  setSpriteControl(5, 5, 240 + 80, wood2_y, 1, 1, Medium);
  setSprite(6, wood_mid_img, Medium);
  setSpriteControl(6, 6, 208 + 80, wood2_y, 1, 1, Medium);
  setSprite(7, wood_right_img, Medium);
  setSpriteControl(7, 7, 272 + 80, wood2_y, 1, 1, Medium);

  // third set 8,9,10
  setSprite(8, wood_left_img, Medium);
  setSpriteControl(8, 8, 240 - 40, wood3_y, 1, 1, Medium);
  setSprite(9, wood_mid_img, Medium);
  setSpriteControl(9, 9, 208 - 40, wood3_y, 1, 1, Medium);
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
