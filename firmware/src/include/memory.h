#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include "kernel.h"


char *_sbrk(int numbytes);

TStatus memoryPoolCreate();
TStatus memoryPoolDelete();
TStatus memoryPoolQuery();
TStatus memoryPoolAllocate();
TStatus memoryPoolDeallocate();




#endif


