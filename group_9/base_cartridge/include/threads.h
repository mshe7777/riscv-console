#ifndef _THREAD_H
#define _THREAD_H

#include <stdint.h>
#include <stdio.h>

typedef uint32_t (*threadEntry)(void *);
uint32_t threadInitialize(uint32_t *threadStackTop, threadEntry entry, void *param);

#endif