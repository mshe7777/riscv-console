#include <stdint.h>
#include "include/timer.h"
#include "include/kernel.h"


extern uint8_t _erodata[];
extern uint8_t _data[];
extern uint8_t _edata[];
extern uint8_t _sdata[];
extern uint8_t _esdata[];
extern uint8_t _bss[];
extern uint8_t _ebss[];

// Adapted from https://stackoverflow.com/questions/58947716/how-to-interact-with-risc-v-csrs-by-using-gcc-c-code
__attribute__((always_inline)) inline uint32_t csr_mstatus_read(void){
    uint32_t result;
    asm volatile ("csrr %0, mstatus" : "=r"(result));
    return result;
}

__attribute__((always_inline)) inline void csr_mstatus_write(uint32_t val){
    asm volatile ("csrw mstatus, %0" : : "r"(val));
}

__attribute__((always_inline)) inline void csr_write_mie(uint32_t val){
    asm volatile ("csrw mie, %0" : : "r"(val));
}

__attribute__((always_inline)) inline void csr_enable_interrupts(void){
    asm volatile ("csrsi mstatus, 0x8");
}

__attribute__((always_inline)) inline void csr_disable_interrupts(void){
    asm volatile ("csrci mstatus, 0x8");
}

extern volatile int global;
extern volatile uint32_t controller_status;
extern volatile int vip_seq;
extern volatile int cmd_seq;
extern volatile uint32_t *INTER_ENABLE;

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
        }
        break;
        
        // controller_status = CONTROLLER;
    }
    if(INTER_PENDING & 0x04 ==1){
        cmd_seq++;
    }
    if(INTER_PENDING & 0x02 ==1){
        vip_seq++;
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
    }

    return ret;
}
