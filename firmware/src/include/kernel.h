#pragma once
#include<stdint.h>




// timer
#define INTER_PENDING   (*((volatile uint32_t *)0x40000004))
#define MTIME_LOW       (*((volatile uint32_t *)0x40000008))
#define MTIME_HIGH      (*((volatile uint32_t *)0x4000000C))
#define MTIMECMP_LOW    (*((volatile uint32_t *)0x40000010))
#define MTIMECMP_HIGH   (*((volatile uint32_t *)0x40000014))
#define CONTROLLER      (*((volatile uint32_t *)0x40000018))

#define STATUS_FAILURE      ((TStatus)0x00);
#define STATUS_SUCCESS      ((TStatus)0x01);
#define STATUS_INVALD_ID    ((TStatus)0x02);

extern volatile uint32_t *CARTRIDGE;

// cmd and video
extern volatile int vip_seq;
extern volatile int cmd_seq;
extern volatile uint32_t *MODE_REGISTER;
extern volatile char *VIDEO_MEMORY ;



// controller
extern volatile uint32_t controller_status;



// interrupt pending
extern volatile uint32_t *INT_PENDING;

// hardware interrupt
#define MACHINE_TIMER 0x80000007
#define EXTERNAL 0x8000000b

// def
typedef uint32_t TStatus;// total status

// systemcall implemented in the syscall.s
uint32_t getTicks();
uint32_t getButtonStatus();
uint32_t getCmdInterrupted();
uint32_t getVideoInterrupted();



// thread def

// status
#define INVALD_THREAD_ID ((ThreadID)-1);


// timer

#define TICK_NUM 1
#define MTIME_LOW       (*((volatile uint32_t *)0x40000008))
#define MTIME_HIGH      (*((volatile uint32_t *)0x4000000C))
#define MTIMECMP_LOW    (*((volatile uint32_t *)0x40000010))
#define MTIMECMP_HIGH   (*((volatile uint32_t *)0x40000014))

void set_timer(uint64_t msec);
// millisecond
void handle_time_interrupt();




// global variables




// assembly 
__attribute__((always_inline)) inline uint32_t csr_mstatus_read(void)
{
    uint32_t result;
    asm volatile("csrr %0, mstatus"
                 : "=r"(result));
    return result;
}

__attribute__((always_inline)) inline void csr_mstatus_write(uint32_t val)
{
    asm volatile("csrw mstatus, %0"
                 :
                 : "r"(val));
}

__attribute__((always_inline)) inline void csr_write_mie(uint32_t val)
{
    asm volatile("csrw mie, %0"
                 :
                 : "r"(val));
}

__attribute__((always_inline)) inline void csr_enable_interrupts(void)
{
    asm volatile("csrsi mstatus, 0x8");
}

__attribute__((always_inline)) inline void csr_disable_interrupts(void)
{
    asm volatile("csrci mstatus, 0x8");
}

__attribute__((always_inline)) inline void csr_write_mepc(uint32_t val)
{
    asm volatile("csrw mepc, %0"
                 :
                 : "r"(val));
}

__attribute__((always_inline)) inline uint32_t csr_mepc_read(void)
{
    uint32_t result;
    asm volatile("csrr %0, mepc"
                 : "=r"(result));
    return result;
}

__attribute__((always_inline)) inline uint32_t csr_mcause_read(void)
{
    uint32_t result;
    asm volatile("csrr %0, mcause"
                 : "=r"(result));
    return result;
}

