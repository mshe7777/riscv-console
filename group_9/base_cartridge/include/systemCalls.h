#ifndef __SYSTEMCALLS_H
#define __SYSTEMCALLS_H 

#include <stdint.h>
//#include <stdlib.h>
#include <stddef.h>

volatile uint32_t controller_status = 0;

uint32_t GetTicks(void);
uint32_t GetController(void);

uint32_t print(char *);
uint32_t clear(int);

uint32_t delay(int);

uint32_t setModeRegister(int);

typedef void (*FunctionPtr)(void);
void setCallbackHandler(char, FunctionPtr);

#endif