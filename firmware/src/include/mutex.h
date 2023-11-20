#ifndef MUTEX_H
#define MUTEX_H

#include <stdint.h>
#include "kernel.h"


TStatus mutexLock();
TStatus mutexRelease();



#endif