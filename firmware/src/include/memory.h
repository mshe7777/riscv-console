#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>
#include "kernel.h"
#define ALIGNMENT 8 // must be a power of 2
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~(ALIGNMENT-1))
#define SIZE_T_SIZE (ALIGN(sizeof(size_t))) // header size

typedef struct free_blk_header {
 size_t size;
 struct free_blk_header *next;
 struct free_blk_header *prior;
} free_blk_header_t;

char *_sbrk(int numbytes);


static char *heap_ptr = NULL;
// static struct Block *free_list = NULL;


// system_calls
void *kmalloc(size_t size);
void kfree(void* ptr);
void kmemcpy(uint8_t* dst, uint8_t* src, size_t num);

void* Memcpy(uint8_t* dst,uint8_t* src,size_t num);
void Free(void* ptr);
void *Malloc(size_t size);


#endif


