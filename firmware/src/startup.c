#include <stdint.h>
#include <stddef.h>
#include "include/kernel.h"
#include "include/thread.h"
#include "include/memory.h"
#include "include/mutex.h"



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
extern volatile uint32_t *INTER_ENABLE;



volatile int vip_seq=1;
volatile int cmd_seq=1;

// Nuber of sprites: 0~127: small sprite; 128~191: large sprite
int small_sprite_count = 0; // max: 128 small sprites
int medium_sprite_count = 0; // max: 
int large_sprite_count = 0; // max: 64 large sprites
int current_thread_num=0;// not exist main()
int running_thread_pointer=0;

uint32_t ThreadStack[9][2048]={'0'};
TStackRef ThreadPointers[10]={'0'};


volatile uint32_t *INT_PENDING = (volatile uint32_t *)(0x40000004);
volatile uint32_t *MODE_REGISTER = (volatile uint32_t *)(0x500F6780);
volatile uint32_t *INTER_ENABLE=(volatile uint32_t *)(0x40000000);
volatile uint32_t controller_status = 0;
volatile uint32_t *CARTRIDGE=(volatile uint32_t *)(0x4000001C);
volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xF4800);

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
    *MODE_REGISTER=0;
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
            // update the systick
            // updateAllTick();
        }
        break;
        case EXTERNAL:{
            // if(INTER_PENDING & 0x04 ==1){
            //     // cmd_interrupt
            //     // cmd_seq++;
            //     cmd_interrupt();
                
            // }
            // if(INTER_PENDING & 0x02 ==1){
            //     // video_interrupt
            //     vip_seq++;
            // }
            // if(INTER_PENDING & 0x01==1){
            //     //cart
            // }
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
    if(INTER_PENDING & 0x04 ==1){
                // cmd_interrupt
                // cmd_seq++;
        cmd_interrupt();
                
    }
    if(INTER_PENDING & 0x02 ==1){
        // video_interrupt
        vip_seq++;
    }
    if(INTER_PENDING & 0x01==1){
        //cart
    }

}


uint32_t c_system_call(uint32_t a0,uint32_t a1,uint32_t a2,uint32_t a3, uint32_t a4, uint32_t call){
    uint32_t ret=0xffffffff;
    if(call ==0){
        // OSinitialize
        // Deprecated!
        ret=OSinitialize((void *)a0);
    }
    else if(call == 1){
        ret=global;
    }else if(call ==2){
        // buttonInterrupt
        ret=CONTROLLER;
    }else if(call ==3){
        // cmdInterrupt
        ret=cmd_seq;

    }else if(call ==4){
        // videoInterrupt
        ret=vip_seq;
    }else if(call ==5){
        // ThreadInit
        if(current_thread_num<=10){
            ThreadPointers[current_thread_num]= ContextInitialize((TStackRef)(ThreadStack[current_thread_num - 1] + 2048), 
            (TContextEntry)a0, (void *)a1);
            current_thread_num++;
        }
    }else if(call==6){
        // thread_create
        if(current_thread_num<=MAX_THREAD_NUM){
            return threadCreate((TContextEntry)a0,(void *)a1,(uint32_t)a2,(ThreadPriority)a3);
        }
    }else if(call==7){
        // thread_yield
        return threadActivate((ThreadID) a0);
    }else if(call==8){
        // thread_exit  // no params
        // first terminate then delete
        threadTerminate((ThreadID)running_thread_id,ret);
        return ret;
    }else if(call==9){
        // _memcpy
        kmemcpy((uint8_t*)(a0),(uint8_t*)(a1),(size_t)(a2));
        return ret;
    }else if(call==10){
        // _malloc
        kmalloc((size_t)(a0));
    }else if(call==11){
        // _free
        kfree((void*)(a0));
    }else if(call==12){
        // lock
        mutexLock(sched,mutexArray[(MutexId)a0]);
    }else if(call==13){
        // unlock
        mutexRelease(sched,mutexArray[(MutexId)a0]);
    }else if(call==14){
        // initLock
        ret=mutexCreate();
    }else if(call==15){
        // destoryLock
        // if(mutexArray[])
        if(mutexArray[(MutexId)a0]!=NULL){
            ret=STATUS_SUCCESS;
        }else{
            ret=STATUS_FAILURE;
        }
        mutexArray[(MutexId)a0]=NULL;
    }


    return ret;
}


void cmd_interrupt(){
    VIDEO_MEMORY[0x40*3]='C';
    if(*MODE_REGISTER){
        *MODE_REGISTER=0;
    }else{
        *MODE_REGISTER = 1;
    }
}
