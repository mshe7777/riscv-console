#pragma once
#include <stdint.h>
#include <stddef.h>

// video controller
// #define DISPLAY_WITDH 512
// #define DISPLAY_HEIGHT 288
// #define LARGE_SPRITES_SIZE 64
// #define MEDIUM_SPRITES_SIZE 32
// #define SMALL_SPRITES_SIZE 16

// #define GRAPHICS_MODE 0x1
// #define TEXT_MODE 0x0

// // Background Data
// #define BACKGROUND_DATA_BASE 0x50000000
// #define BACKGROUND_DATA_SIZE 0x24000 

// // Large Sprite Data
// #define LARGE_SPRITE_DATA_BASE 0x50090000
// #define LARGE_SPRITE_DATA_SIZE 0x1000 // 4Kib

// // Medium Sprite Data
// #define MEDIUM_SPRITE_DATA_BASE 0x500D0000
// #define MEDIUM_SPRITE_DATA_SIZE 0x400 // 1KiB

// // Small Sprite Data
// #define SMALL_SPRITE_DATA_BASE 0x500E0000
// #define SMALL_SPRITE_DATA_SIZE 0x100 // 256B

// // Background and Sprite Palettes
// #define BACKGROUND_PALETTE_BASE 0x500F0000
// #define BACKGROUND_PALETTE_SIZE 0x400 // 4KiB

// // Large Sprite Palettes
// #define LARGE_SPRITE_PALETTE_BASE 0x500F1000
// #define LARGE_SPRITE_PALETTE_SIZE 0x400 // 4KiB

// // Medium Sprite Palettes
// #define MEDIUM_SPRITE_PALETTE_BASE 0x500F2000
// #define MEDIUM_SPRITE_PALETTE_SIZE 0x400 // 4KiB

// // Small Sprite Palettes
// #define SMALL_SPRITE_PALETTE_BASE 0x500F3000
// #define SMALL_SPRITE_PALETTE_SIZE 0x400 // 4KiB

// // Font Data
// #define FONT_DATA_BASE 0x500F4000
// #define FONT_DATA_SIZE 0x800 // 2KiB

// // Text Data
// #define TEXT_DATA_BASE 0x500F4800
// #define TEXT_DATA_SIZE 0x900 // 2.25KiB

// // Text Color
// #define TEXT_COLOR_BASE 0x500F5100
// #define TEXT_COLOR_SIZE 0x900 // 2.25KiB

// // Background Control Memory
// #define BACKGROUND_CONTROL_BASE 0x500F5A00
// #define BACKGROUND_CONTROL_SIZE 0x100 // 256B

// // Large Sprite Control Memory
// #define LARGE_SPRITE_CONTROL_BASE 0x500F5B00
// #define LARGE_SPRITE_CONTROL_SIZE 0x400 // 1KiB

// // Medium Sprite Control Memory
// #define MEDIUM_SPRITE_CONTROL_BASE 0x500F5F00
// #define MEDIUM_SPRITE_CONTROL_SIZE 0x400 // 1KiB

// // Small Sprite Control Memory
// #define SMALL_SPRITE_CONTROL_BASE 0x500F6300
// #define SMALL_SPRITE_CONTROL_SIZE 0x400 // 1KiB

// // Text Palettes
// #define TEXT_PALETTE_BASE 0x500F6700
// #define TEXT_PALETTE_SIZE 0x80 // 128B

// // Mode Control Register
// #define MODE_CONTROL_BASE 0x500F6780
// #define MODE_CONTROL_SIZE 0x4 // 4B
// extern volatile uint32_t *MODE_CONTROL_REG;

// #define RED 0xFFFF0000
// #define BLUE 0xFF0000FF
// #define GREEN 0xFF00FF00
// #define WHITE 0xFFFFFFFF

// enum Sprites{
//     Large,
//     Medium,
//     Small
// };
// typedef enum Sprites Sprite;



// // void setVideoModel(int cmd);


// int setBackGround(uint8_t idx,char* addr);
// int setSprite(uint8_t idx, uint8_t *addr, Sprite sprites) ;
// int initBackGroundPalettes(uint8_t idx,uint8_t* addr);
// int initSpritesPalettes(uint8_t idx,uint32_t *addr,Sprite sprites);
// void setBackGroundControl(uint8_t ctrl_idx, uint8_t data_idx,uint16_t x,uint16_t y,uint8_t z,uint8_t palette);
// void setTileBackGroundControl(uint8_t ctrl_x,uint8_t tile_idx,uint8_t sub_idx,uint16_t x, uint16_t y, uint8_t z,uint8_t palette);
// void setSpriteControl(uint8_t ctrl_idx,uint8_t data_idx,uint16_t x,uint16_t y,uint16_t z,uint8_t palette,Sprite sprites);
// // Function declarations with updated variable names
// void setBackground(uint8_t backgroundIndex, char* pixelData,
//                    uint8_t controlIndex, uint8_t pixelIndex,
//                    uint8_t tileIndex, uint8_t subIndex,
//                    uint16_t posX, uint16_t posY,
//                    uint8_t zIndex, uint8_t paletteIndex,
//                    uint32_t* paletteData);

// void setLargeSprite(uint8_t spriteIndex, uint8_t* spriteData,
//                     uint8_t controlIndex, uint8_t spriteDataIndex,
//                     uint16_t posX, uint16_t posY, uint16_t zIndex,
//                     uint8_t paletteIndex, uint32_t* paletteData);

// void setMediumSprite(uint8_t spriteIndex, uint8_t* spriteData,
//                      uint8_t controlIndex, uint8_t spriteDataIndex,
//                      uint16_t posX, uint16_t posY, uint16_t zIndex,
//                      uint8_t paletteIndex, uint32_t* paletteData);

// void setSmallSprite(uint8_t spriteIndex, uint8_t* spriteData,
//                     uint8_t controlIndex, uint8_t spriteDataIndex,
//                     uint16_t posX, uint16_t posY, uint16_t zIndex,
//                     uint8_t paletteIndex, uint32_t* paletteData);

// void simple_medium_sprite(int16_t x, int16_t y, int16_t z);