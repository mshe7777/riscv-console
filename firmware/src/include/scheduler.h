#include<stdlib.h>
#include<stdint.h>
#include "thread.h"

extern "C" void context_switch(volatile size_t** oldcontext ,volatile size_t** newcontext );
extern "C"  void startFirstTask(uint32_t stk_ptr);

