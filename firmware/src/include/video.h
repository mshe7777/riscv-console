#pragma once
#include <stdint.h>

// video controller
#define DISPLAY_WITDH 512
#define DISPLAY_HEIGHT 288
#define LARGE_SPRITES_SIZE 64
#define MEDIUM_SPRITES_SIZE 32
#define SMALL_SPRITES_SIZE 16
// Background Data
#define BACKGROUND_DATA_BASE 0x50000000
#define BACKGROUND_DATA_SIZE 0x90000 // 576KiB

// Large Sprite Data
#define LARGE_SPRITE_DATA_BASE 0x50090000
#define LARGE_SPRITE_DATA_SIZE 0x1000 // 4Kib

// Medium Sprite Data
#define MEDIUM_SPRITE_DATA_BASE 0x500D0000
#define MEDIUM_SPRITE_DATA_SIZE 0x400 // 1KiB

// Small Sprite Data
#define SMALL_SPRITE_DATA_BASE 0x500E0000
#define SMALL_SPRITE_DATA_SIZE 0x100 // 256B

// Background and Sprite Palettes
#define BACKGROUND_PALETTE_BASE 0x500F0000
#define BACKGROUND_PALETTE_SIZE 0x400 // 4KiB

// Large Sprite Palettes
#define LARGE_SPRITE_PALETTE_BASE 0x500F1000
#define LARGE_SPRITE_PALETTE_SIZE 0x400 // 4KiB

// Medium Sprite Palettes
#define MEDIUM_SPRITE_PALETTE_BASE 0x500F2000
#define MEDIUM_SPRITE_PALETTE_SIZE 0x400 // 4KiB

// Small Sprite Palettes
#define SMALL_SPRITE_PALETTE_BASE 0x500F3000
#define SMALL_SPRITE_PALETTE_SIZE 0x400 // 4KiB

// Font Data
#define FONT_DATA_BASE 0x500F4000
#define FONT_DATA_SIZE 0x800 // 2KiB

// Text Data
#define TEXT_DATA_BASE 0x500F4800
#define TEXT_DATA_SIZE 0x900 // 2.25KiB

// Text Color
#define TEXT_COLOR_BASE 0x500F5100
#define TEXT_COLOR_SIZE 0x900 // 2.25KiB

// Background Control Memory
#define BACKGROUND_CONTROL_BASE 0x500F5A00
#define BACKGROUND_CONTROL_SIZE 0x100 // 256B

// Large Sprite Control Memory
#define LARGE_SPRITE_CONTROL_BASE 0x500F5B00
#define LARGE_SPRITE_CONTROL_SIZE 0x400 // 1KiB

// Medium Sprite Control Memory
#define MEDIUM_SPRITE_CONTROL_BASE 0x500F5F00
#define MEDIUM_SPRITE_CONTROL_SIZE 0x400 // 1KiB

// Small Sprite Control Memory
#define SMALL_SPRITE_CONTROL_BASE 0x500F6300
#define SMALL_SPRITE_CONTROL_SIZE 0x400 // 1KiB

// Text Palettes
#define TEXT_PALETTE_BASE 0x500F6700
#define TEXT_PALETTE_SIZE 0x80 // 128B

// Mode Control Register
#define MODE_CONTROL_BASE 0x500F6780
#define MODE_CONTROL_SIZE 0x4 // 4B



enum Sprites{
    Large,
    Medium,
    Small
};
typedef enum Sprites Sprite;



void setVideoModel(int cmd);

int setBackGround(uint32_t idx,uint8_t* addr);
int setSprite(uint32_t idx,uint8_t* addr,Sprite sprites);


int initBackGroundPalettes(uint32_t idx,uint8_t* addr);
int initSpritesPalettes(uint32_t idx, uint8_t *addr,Sprite sprites);




int writeMemory(uint32_t mem_handle,uint32_t addr,uint32_t size);

void setBackGroundControl(uint32_t idx,uint32_t x,uint32_t y,uint32_t z,uint32_t palette);
void setSpriteControl(uint32_t idx,uint32_t x,uint32_t y,uint32_t z,uint32_t palette,Sprite sprites);
