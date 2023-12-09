#ifndef _VIDEOSYSTEMCALLS_H
#define _VIDEOSYSTEMCALLS_H

#include <stdint.h>

typedef enum {
    SMALL, MEDUIM, LARGE
} SpriteTYPE;

typedef struct {
    int x;
    int y;
    int z;
} coordinate;


typedef struct {
    SpriteTYPE type;
    coordinate position;
    int index;
    uint32_t color;
} Sprite;

typedef struct {
    int numMediumSprites;
    int numSmallSprites;
    int numLargeSprites;
} SpiritesNUM;

typedef struct {
    Sprite sprite;
    uint32_t* spriteInt;
} SpriteObj;

typedef struct {
    int mode; // pixel = 0, tile = 1
    int typeMode; // Pixel or tile mode
    coordinate position;
    uint32_t color;
    int index; // pixel idx or tile idx
} Background;


uint32_t moveSprites(Sprite **spirites, int numSpirites);
uint32_t moveSprite(Sprite *spirite);
uint32_t initSprite(Sprite *spirite);
uint32_t removeSprite(Sprite *spirite);
uint32_t backgroundInit(Background *background);


#endif