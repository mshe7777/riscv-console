#include "include/video.h"

volatile uint32_t *MODE_CONTROL_REG=(volatile uint32_t *)(0x50000000+0xF6780);


void setVideoModel(int cmd){
    (*MODE_CONTROL_REG)^=(cmd&0x1);
}
int writeMemory(uint32_t mem_handle,uint32_t addr,uint32_t size){
    uint32_t* transfer_addr=(uint32_t*)mem_handle;

    for(uint32_t i=0;i<size;i++){
        ((uint8_t*)transfer_addr)[i]=((uint8_t*)addr)[i];
    }
    return 0;
}


int setBackGround(uint32_t idx,uint8_t* addr){
    uint32_t offset=BACKGROUND_DATA_BASE+idx*BACKGROUND_DATA_SIZE;

    writeMemory(offset,(uint32_t)addr,BACKGROUND_DATA_SIZE);
    // for(uint32_t i=0;i<BACKGROUND_DATA_SIZE;i++) ((uint8_t*)offset)[i]=addr[i];
    return 0;
}

int setSprite(uint32_t idx, uint8_t *addr, Sprite sprites) {
    uint32_t offset;
    uint32_t size = 0;
    switch (sprites) {
        case Large:
            size = LARGE_SPRITE_DATA_SIZE;
            offset = LARGE_SPRITE_DATA_BASE + idx * size;
            break;
        case Medium:
            size = MEDIUM_SPRITE_DATA_SIZE;
            offset = MEDIUM_SPRITE_DATA_BASE + idx * size;
            break;
        case Small:
            size = SMALL_SPRITE_DATA_SIZE;
            offset = SMALL_SPRITE_DATA_BASE + idx * size;
            break;
        default:
            break;
    }

    writeMemory(offset,(uint32_t)addr,size);
    return 0;
}



int initBackGroundPalettes(uint32_t idx,uint8_t* addr){
    uint32_t offset=BACKGROUND_PALETTE_BASE+idx*BACKGROUND_PALETTE_SIZE;
    writeMemory(offset,(uint32_t)addr,BACKGROUND_PALETTE_SIZE);
    return 0;
}

int initSpritesPalettes(uint32_t idx,uint8_t *addr,Sprite sprites){
    uint32_t* offset;
    uint32_t size=0x4;
    switch (sprites)
    {
    case Large :
        /* code */
        offset=LARGE_SPRITE_PALETTE_BASE+idx*0x4;
        break;
    case Medium:
        offset=MEDIUM_SPRITE_PALETTE_BASE+idx*0x4;
        break;
    case Small:
        offset=SMALL_SPRITE_PALETTE_BASE+idx*0x4;
        break;
    default:
        break;
    }
    writeMemory(offset,(uint32_t)addr,SMALL_SPRITE_PALETTE_SIZE);
}


void setBackGroundControl(uint32_t idx,uint32_t x,uint32_t y,uint32_t z,uint32_t palette){

    uint32_t offset=BACKGROUND_CONTROL_BASE+idx*4;
    y=(y+288)& 0x3FF;
    x=(x+512)& 0x3FF;
    z=(z+0)& 0x7;
    palette=palette&0x3;
    uint32_t value=(idx<<29)|(z<<22)|(y<12)|(x<<2)|palette;
    uint32_t* addr=(uint32_t*) offset;
    *addr=value;    
}
void setSpriteControl(uint32_t idx,uint32_t x,uint32_t y,uint32_t z,uint32_t palette,Sprite sprites){
    uint32_t offset=0;
    switch (sprites)
    {
    case Large:
        offset=LARGE_SPRITE_CONTROL_BASE+idx*4;
        y=(y+LARGE_SPRITES_SIZE)&0x3FF;
        x=(x+LARGE_SPRITES_SIZE)&0x3FF;
        break;
    case Medium:
        offset=MEDIUM_SPRITE_CONTROL_BASE+idx*4;
        y=(y+MEDIUM_SPRITES_SIZE)&0x3FF;
        x=(x+MEDIUM_SPRITES_SIZE)&0x3FF;
        break;
    case Small:
        offset=SMALL_SPRITE_CONTROL_BASE+idx*4;
        y=(y+SMALL_SPRITES_SIZE)&0x3FF;
        x=(x+SMALL_SPRITES_SIZE)&0x3FF;
        break;
    default:
        break;
    }
    z=(z+0) &0x7;
    palette=palette&0x3;
    uint32_t value=(idx<<24)|(z<<21)|(y<12)|(x<<2)|palette;
    uint32_t* addr=(uint32_t*) offset;
    *addr=value;    
}