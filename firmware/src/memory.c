// #include <string.h>
#include "include/memory.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern char _heap_base[];
extern char _stack[];

char *_sbrk(int numbytes){
  
  char *base;

  if (heap_ptr == NULL) {
    heap_ptr = (char *)&_heap_base;
  }

  if((heap_ptr + numbytes) <=_stack) {
    base = heap_ptr;
    heap_ptr += numbytes;
    return (base);
  }
  else {
    //errno = ENOMEM;
    return NULL;
  }

}

// super-naive allocator
void *kmalloc(size_t size) {
 size_t blk_size = ALIGN(size + SIZE_T_SIZE);
 size_t *header = _sbrk(blk_size);
 return (char *)header + SIZE_T_SIZE;
}

void kfree(void *ptr) {
 size_t *header = (char *)ptr - SIZE_T_SIZE;
}
void kmemcpy(uint8_t* dst, uint8_t* src, size_t num) {
    for (size_t i = 0; i < num; i++) {
        dst[i] = src[i];
    }
};
