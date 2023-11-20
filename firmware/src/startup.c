#include <stdint.h>
#include "include/timer.h"
#include "include/kernel.h"
#include "include/thread.h"


extern uint8_t _erodata[];
extern uint8_t _data[];
extern uint8_t _edata[];
extern uint8_t _sdata[];
extern uint8_t _esdata[];
extern uint8_t _bss[];
extern uint8_t _ebss[];

// Adapted from https://stackoverflow.com/questions/58947716/how-to-interact-with-risc-v-csrs-by-using-gcc-c-code

extern volatile int global;
extern volatile uint32_t controller_status;
extern volatile int vip_seq;
extern volatile int cmd_seq;
extern volatile uint32_t *INTER_ENABLE;


volatile uint32_t *INT_PENDING = (volatile uint32_t *)(0x40000004);


// Nuber of sprites: 0~127: small sprite; 128~191: large sprite
int small_sprite_count = 0; // max: 128 small sprites
int medium_sprite_count = 0; // max: 
int large_sprite_count = 0; // max: 64 large sprites
int current_thread_num=1;
int running_thread_pointer=0;

uint32_t ThreadStack[9][2048]={'0'};
TStackRef ThreadPointers[10]={'0'};


volatile int vip_seq=0;
volatile int cmd_seq=0;
volatile uint32_t *INTER_ENABLE=(volatile uint32_t *)(0x40000000);

void init(void){
    uint8_t *Source = _erodata;
    uint8_t *Base = _data < _sdata ? _data : _sdata;
    uint8_t *End = _edata > _esdata ? _edata : _esdata;

    while(Base < End){
        *Base++ = *Source++;
    }
    Base = _bss;
    End = _ebss;
    while(Base < End){
        *Base++ = 0;
    }

    csr_write_mie(0x888);       // Enable all interrupt soruces
    csr_enable_interrupts();    // Global interrupt enable
    MTIMECMP_LOW = 1;
    MTIMECMP_HIGH = 0;
    // *INTER_ENABLE=0x07;

}



void  c_interrupt_handler(int mcause,int mepc){

    switch(mcause){
        case  MACHINE_TIMER:{
            global++;
            handle_time_interrupt();
            if (global == 9999)
            {
                global = 0;
            }
        }
        break;
        case EXTERNAL:{
            if(INTER_PENDING & 0x04 ==1){
                // cmd_interrupt
                cmd_seq++;
            }
            if(INTER_PENDING & 0x02 ==1){
                // video_interrupt
                vip_seq++;
            }
            if(INTER_PENDING & 0x01==1){
                //cart
            }
        }
        break;
        default:
        break;
        
        // controller_status = CONTROLLER;
        // refresh the screen
        const uint32_t BIT_POSITION = 2;
        const uint32_t MASK = ~(1U << BIT_POSITION);
        *INT_PENDING |= (1U << BIT_POSITION) & MASK;
    }

}


uint32_t c_system_call(uint32_t a0,uint32_t a1,uint32_t a2,uint32_t call){
    uint32_t ret=0xffffffff;

    if(call == 0){
        ret=global;
    }else if(call ==1){
        // buttonInterrupt
        ret=CONTROLLER;
    }else if(call ==2){
        // cmdInterrupt
        ret=cmd_seq;

    }else if(call ==3){
        // videoInterrupt
        ret=vip_seq;
    }else if(call ==4){
        // ThreadInit
        if(current_thread_num<=10){
            ThreadPointers[current_thread_num]= ContextInitialize((TStackRef)(ThreadStack[current_thread_num - 1] + 2048), (TContextEntry)a0, (void *)a1);
            current_thread_num++;
        }
    }

    return ret;
}
