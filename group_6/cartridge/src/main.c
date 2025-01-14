#include "api.h"
#include "display.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void initVideoSetting();
void showGameOver();
void printText(char *string);

typedef enum { RUN = 0, WIN, LOSE } Status;
Status status = RUN;

volatile int global = 42;
volatile uint32_t controller_status = 0;
volatile uint32_t *SMALL_SPRITE_CONTROL = (volatile uint32_t *)(0x500F6300);

uint32_t black = 0xFF000000;
uint32_t green = 0xFF0EB037;
uint32_t blue = 0xFF0A1F94;
uint32_t brown = 0xFF994C1C;

int wood1_y = 192;
int wood2_y = 128;
int wood3_y = 64;

struct position {
  uint32_t x;
  uint32_t y;
  uint8_t step;
};

struct wood {
  int x;
  int y;
  int dir;
};

struct position frog;

int main() {
  initVideoSetting();
  int last_global = 0;
  int countdown = 0;

  frog.x = 240 + 8;
  frog.y = 256 + 8;
  frog.step = 0;

  int wood1_x = 208;
  int wood2_x = wood1_x + 80;
  int wood3_x = wood1_x - 40;
  int wood1_dir = -1;
  int wood2_dir = 1;
  int wood3_dir = -1;

  int gap = 10000;

  while (status == RUN) {

    ////Wood move thread
    global = getTicks();
    if (global - last_global > 1) {
      // wood move speed
      wood1_x += wood1_dir * 5;
      wood2_x += wood2_dir * 7;
      wood3_x += wood3_dir * 10;

      // position reset over screen
      if (wood1_x <= 0)
        wood1_dir = 1;
      else if (wood1_x + 96 >= 512)
        wood1_dir = -1;
      if (wood2_x <= 0)
        wood2_dir = 1;
      else if (wood2_x + 96 >= 512)
        wood2_dir = -1;
      if (wood3_x <= 0)
        wood3_dir = 1;
      else if (wood3_x + 96 >= 512)
        wood3_dir = -1;

      // moving
      // wood 1
      for (int y = 0; y < 2; y++) {
        for (int x = 0; x < 6; x++) {
          moveSmallSprite(y * 6 + x, wood1_x + x * 16, wood1_y + y * 16);
        }
      }
      // wood 2
      for (int y = 0; y < 2; y++) {
        for (int x = 0; x < 6; x++) {
          moveSmallSprite(12 + y * 6 + x, wood2_x + x * 16, wood2_y + y * 16);
        }
      }
      // wood 3
      for (int y = 0; y < 2; y++) {
        for (int x = 0; x < 6; x++) {
          moveSmallSprite(24 + y * 6 + x, wood3_x + x * 16, wood3_y + y * 16);
        }
      }

      // frog on the wood
      if (frog.step == 3) {
        frog.x += wood3_dir * 10;
      }
      if (frog.step == 2) {
        frog.x += wood2_dir * 7;
      }

      if (frog.step == 1) {
        frog.x += wood1_dir * 5;
      }
      moveSmallSprite(36, frog.x, frog.y);

      last_global = global;
    }

    // Frog move thread
    if (countdown > gap) {
      gap = 10000;
      controller_status = getStatus();
      if (controller_status) {
        if (controller_status & 0x1) {
          frog.x -= 10;
        }

        if (controller_status & 0x2) {
          frog.y -= 64;
          frog.step++;
          gap = 60000;
        }

        if (controller_status & 0x4) {
          if (frog.step == 0)
            continue;
          frog.y += 64;
          frog.step--;
          gap = 60000;
        }

        if (controller_status & 0x8) {
          frog.x += 10;
        }
      }
      moveSmallSprite(36, frog.x, frog.y);
      countdown = 0;
    }
    countdown++;

    // Game over check thread
    if (frog.step == 4) {
      status = WIN;
    }
    if (frog.step == 3) {
      if (abs((wood3_x + 48) - (frog.x + 8)) > 58)
        status = LOSE;
    }
    if (frog.step == 2) {
      if (abs((wood2_x + 48) - (frog.x + 8)) > 58)
        status = LOSE;
    }
    if (frog.step == 1) {
      if (abs((wood1_x + 48) - (frog.x + 8)) > 58)
        status = LOSE;
    }
  }

  showGameOver();
  return 0;
}

void initVideoSetting() {
  switchToGraphicsMode();

  setBackgroundColor(0, 0, blue);
  setColor(0, 0, brown);
  setColor(1, 0, green);
  setColor(2, 0, black);

  drawRectangleWithBackgroundSpriteControl(
      0, generateBackgroundConfig(0, 0, 0, 0));

  // upper band
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 32; x++) {
      // If index greater than 127, drawRectangleWithSmallSprite() doesn't work
      // Save them for moving sprites
      SMALL_SPRITE_CONTROL[128 + y * 32 + x] =
          generateSmallSpriteConfig(x * 16, y * 16, 1, 1, 0);
    }
  }

  // bottom band
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 32; x++) {
      SMALL_SPRITE_CONTROL[192 + y * 32 + x] =
          generateSmallSpriteConfig(x * 16, 256 + y * 16, 1, 1, 0);
    }
  }

  // wood 1
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 6; x++) {
      drawRectangleWithSmallSprite(
          y * 6 + x,
          generateSmallSpriteConfig(208 + x * 16, wood1_y + y * 16, 2, 2, 0));
    }
  }

  // wood 2
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 6; x++) {
      drawRectangleWithSmallSprite(
          12 + y * 6 + x, generateSmallSpriteConfig(208 + 80 + x * 16,
                                                    wood2_y + y * 16, 2, 2, 0));
    }
  }

  // wood3
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 6; x++) {
      drawRectangleWithSmallSprite(
          24 + y * 6 + x, generateSmallSpriteConfig(208 - 40 + x * 16,
                                                    wood3_y + y * 16, 2, 2, 0));
    }
  }

  // frog
  drawRectangleWithSmallSprite(
      36, generateSmallSpriteConfig(240 + 8, 256 + 8, 2, 2, 1));
}

void showGameOver() {

  if (status == WIN) {
    // W
    drawRectangleWithSmallSprite(
        36 + 1, generateSmallSpriteConfig(160 + 16 * 0, 100 + 16 * 0, 2, 2, 2));
    drawRectangleWithSmallSprite(
        36 + 2, generateSmallSpriteConfig(160 + 16 * 0, 100 + 16 * 1, 2, 2, 2));
    drawRectangleWithSmallSprite(
        36 + 3, generateSmallSpriteConfig(160 + 16 * 0, 100 + 16 * 2, 2, 2, 2));
    drawRectangleWithSmallSprite(
        36 + 4, generateSmallSpriteConfig(160 + 16 * 0, 100 + 16 * 3, 2, 2, 2));
    drawRectangleWithSmallSprite(
        36 + 5, generateSmallSpriteConfig(160 + 16 * 1, 100 + 16 * 4, 2, 2, 2));
    drawRectangleWithSmallSprite(
        36 + 6, generateSmallSpriteConfig(160 + 16 * 2, 100 + 16 * 3, 2, 2, 2));
    drawRectangleWithSmallSprite(
        36 + 7, generateSmallSpriteConfig(160 + 16 * 3, 100 + 16 * 4, 2, 2, 2));
    drawRectangleWithSmallSprite(
        36 + 8, generateSmallSpriteConfig(160 + 16 * 4, 100 + 16 * 3, 2, 2, 2));
    drawRectangleWithSmallSprite(
        36 + 9, generateSmallSpriteConfig(160 + 16 * 4, 100 + 16 * 2, 2, 2, 2));
    drawRectangleWithSmallSprite(
        36 + 10,
        generateSmallSpriteConfig(160 + 16 * 4, 100 + 16 * 1, 2, 2, 2));
    drawRectangleWithSmallSprite(
        36 + 11,
        generateSmallSpriteConfig(160 + 16 * 4, 100 + 16 * 0, 2, 2, 2));
    // I
    drawRectangleWithSmallSprite(47 + 1,
                                 generateSmallSpriteConfig(256, 100, 2, 2, 2));
    drawRectangleWithSmallSprite(
        47 + 2, generateSmallSpriteConfig(256, 100 + 16, 2, 2, 2));
    drawRectangleWithSmallSprite(
        47 + 3, generateSmallSpriteConfig(256, 100 + 16 * 2, 2, 2, 2));
    drawRectangleWithSmallSprite(
        47 + 4, generateSmallSpriteConfig(256, 100 + 16 * 3, 2, 2, 2));
    drawRectangleWithSmallSprite(
        47 + 5, generateSmallSpriteConfig(256, 100 + 16 * 4, 2, 2, 2));
    // N
    drawRectangleWithSmallSprite(
        52 + 1, generateSmallSpriteConfig(288 + 16 * 0, 100, 2, 2, 2));
    drawRectangleWithSmallSprite(
        52 + 2, generateSmallSpriteConfig(288 + 16 * 0, 100 + 16, 2, 2, 2));
    drawRectangleWithSmallSprite(
        52 + 3, generateSmallSpriteConfig(288 + 16 * 0, 100 + 16 * 2, 2, 2, 2));
    drawRectangleWithSmallSprite(
        52 + 4, generateSmallSpriteConfig(288 + 16 * 0, 100 + 16 * 3, 2, 2, 2));
    drawRectangleWithSmallSprite(
        52 + 5, generateSmallSpriteConfig(288 + 16 * 0, 100 + 16 * 4, 2, 2, 2));
    drawRectangleWithSmallSprite(
        52 + 6, generateSmallSpriteConfig(288 + 16 * 1, 100 + 16, 2, 2, 2));
    drawRectangleWithSmallSprite(
        52 + 7, generateSmallSpriteConfig(288 + 16 * 2, 100 + 16 * 2, 2, 2, 2));
    drawRectangleWithSmallSprite(
        52 + 8, generateSmallSpriteConfig(288 + 16 * 3, 100, 2, 2, 2));
    drawRectangleWithSmallSprite(
        52 + 9, generateSmallSpriteConfig(288 + 16 * 3, 100 + 16, 2, 2, 2));
    drawRectangleWithSmallSprite(
        52 + 10,
        generateSmallSpriteConfig(288 + 16 * 3, 100 + 16 * 2, 2, 2, 2));
    drawRectangleWithSmallSprite(
        52 + 11,
        generateSmallSpriteConfig(288 + 16 * 3, 100 + 16 * 3, 2, 2, 2));
    drawRectangleWithSmallSprite(
        52 + 12,
        generateSmallSpriteConfig(288 + 16 * 3, 100 + 16 * 4, 2, 2, 2));
    // printText("YOU WIN!!!");
  }
  if (status == LOSE) {
    // L
    drawRectangleWithSmallSprite(
        64 + 1, generateSmallSpriteConfig(100 + 16 * 0, 100 + 16 * 0, 2, 2, 2));
    drawRectangleWithSmallSprite(
        64 + 2, generateSmallSpriteConfig(100 + 16 * 0, 100 + 16 * 1, 2, 2, 2));
    drawRectangleWithSmallSprite(
        64 + 3, generateSmallSpriteConfig(100 + 16 * 0, 100 + 16 * 2, 2, 2, 2));
    drawRectangleWithSmallSprite(
        64 + 4, generateSmallSpriteConfig(100 + 16 * 0, 100 + 16 * 3, 2, 2, 2));
    drawRectangleWithSmallSprite(
        64 + 5, generateSmallSpriteConfig(100 + 16 * 1, 100 + 16 * 4, 2, 2, 2));
    drawRectangleWithSmallSprite(
        64 + 6, generateSmallSpriteConfig(100 + 16 * 2, 100 + 16 * 4, 2, 2, 2));
    drawRectangleWithSmallSprite(
        64 + 7, generateSmallSpriteConfig(100 + 16 * 0, 100 + 16 * 4, 2, 2, 2));
    // O
    drawRectangleWithSmallSprite(
        73 + 1, generateSmallSpriteConfig(100 + 16 * 4, 100 + 16 * 1, 2, 2, 2));
    drawRectangleWithSmallSprite(
        73 + 2, generateSmallSpriteConfig(100 + 16 * 4, 100 + 16 * 2, 2, 2, 2));
    drawRectangleWithSmallSprite(
        73 + 3, generateSmallSpriteConfig(100 + 16 * 4, 100 + 16 * 3, 2, 2, 2));
    drawRectangleWithSmallSprite(
        73 + 4, generateSmallSpriteConfig(100 + 16 * 7, 100 + 16 * 1, 2, 2, 2));
    drawRectangleWithSmallSprite(
        73 + 5, generateSmallSpriteConfig(100 + 16 * 7, 100 + 16 * 2, 2, 2, 2));
    drawRectangleWithSmallSprite(
        73 + 6, generateSmallSpriteConfig(100 + 16 * 7, 100 + 16 * 3, 2, 2, 2));
    drawRectangleWithSmallSprite(
        73 + 7, generateSmallSpriteConfig(100 + 16 * 5, 100 + 16 * 0, 2, 2, 2));
    drawRectangleWithSmallSprite(
        73 + 8, generateSmallSpriteConfig(100 + 16 * 6, 100 + 16 * 0, 2, 2, 2));
    drawRectangleWithSmallSprite(
        73 + 9, generateSmallSpriteConfig(100 + 16 * 5, 100 + 16 * 4, 2, 2, 2));
    drawRectangleWithSmallSprite(
        73 + 10,
        generateSmallSpriteConfig(100 + 16 * 6, 100 + 16 * 4, 2, 2, 2));
    // S
    drawRectangleWithSmallSprite(
        83 + 1, generateSmallSpriteConfig(180 + 16 * 4, 100 + 16 * 4, 2, 2, 2));
    drawRectangleWithSmallSprite(
        83 + 2, generateSmallSpriteConfig(180 + 16 * 5, 100 + 16 * 4, 2, 2, 2));
    drawRectangleWithSmallSprite(
        83 + 3, generateSmallSpriteConfig(180 + 16 * 6, 100 + 16 * 4, 2, 2, 2));
    drawRectangleWithSmallSprite(
        83 + 4, generateSmallSpriteConfig(180 + 16 * 7, 100 + 16 * 3, 2, 2, 2));
    drawRectangleWithSmallSprite(
        83 + 5, generateSmallSpriteConfig(180 + 16 * 6, 100 + 16 * 2, 2, 2, 2));
    drawRectangleWithSmallSprite(
        83 + 6, generateSmallSpriteConfig(180 + 16 * 5, 100 + 16 * 2, 2, 2, 2));
    drawRectangleWithSmallSprite(
        83 + 7, generateSmallSpriteConfig(180 + 16 * 4, 100 + 16 * 1, 2, 2, 2));
    drawRectangleWithSmallSprite(
        83 + 8, generateSmallSpriteConfig(180 + 16 * 5, 100 + 16 * 0, 2, 2, 2));
    drawRectangleWithSmallSprite(
        83 + 9, generateSmallSpriteConfig(180 + 16 * 6, 100 + 16 * 0, 2, 2, 2));
    drawRectangleWithSmallSprite(
        83 + 10,
        generateSmallSpriteConfig(180 + 16 * 7, 100 + 16 * 0, 2, 2, 2));
    // E
    drawRectangleWithSmallSprite(
        93 + 1, generateSmallSpriteConfig(180 + 16 * 9, 100 + 16 * 0, 2, 2, 2));
    drawRectangleWithSmallSprite(
        93 + 2,
        generateSmallSpriteConfig(180 + 16 * 10, 100 + 16 * 0, 2, 2, 2));
    drawRectangleWithSmallSprite(
        93 + 3,
        generateSmallSpriteConfig(180 + 16 * 11, 100 + 16 * 0, 2, 2, 2));
    drawRectangleWithSmallSprite(
        93 + 4,
        generateSmallSpriteConfig(180 + 16 * 12, 100 + 16 * 0, 2, 2, 2));
    drawRectangleWithSmallSprite(
        93 + 5, generateSmallSpriteConfig(180 + 16 * 9, 100 + 16 * 1, 2, 2, 2));
    drawRectangleWithSmallSprite(
        93 + 6, generateSmallSpriteConfig(180 + 16 * 9, 100 + 16 * 2, 2, 2, 2));
    drawRectangleWithSmallSprite(
        93 + 7, generateSmallSpriteConfig(180 + 16 * 9, 100 + 16 * 3, 2, 2, 2));
    drawRectangleWithSmallSprite(
        93 + 8, generateSmallSpriteConfig(180 + 16 * 9, 100 + 16 * 4, 2, 2, 2));
    drawRectangleWithSmallSprite(
        93 + 9,
        generateSmallSpriteConfig(180 + 16 * 10, 100 + 16 * 2, 2, 2, 2));
    drawRectangleWithSmallSprite(
        93 + 10,
        generateSmallSpriteConfig(180 + 16 * 11, 100 + 16 * 2, 2, 2, 2));
    drawRectangleWithSmallSprite(
        93 + 11,
        generateSmallSpriteConfig(180 + 16 * 10, 100 + 16 * 4, 2, 2, 2));
    drawRectangleWithSmallSprite(
        93 + 12,
        generateSmallSpriteConfig(180 + 16 * 11, 100 + 16 * 4, 2, 2, 2));
    drawRectangleWithSmallSprite(
        93 + 13,
        generateSmallSpriteConfig(180 + 16 * 12, 100 + 16 * 4, 2, 2, 2));
    // printText("GAME OVER");
  }
  while (1) {
  }
}