#pragma once
#include "include/kernel.h"
#include "include/dqueue.h"
#include <stdint.h>

// referene https://github.com/nqgl/riscv-console/tree/main

typedef struct FreeListNode {

    struct FreeListNode *next;
    // struct FreeListNode *prev; //?
    char * begin; 
    TMemorySize size;

} FreeListNode;



typedef struct FreeList{

    FreeListNode *head;
    //freesize?
} FreeList;


typedef struct MemPool{
    char *base;
    TMemoryPoolID poolid;
    TMemorySize size;
    TMemorySize freesize;
    FreeList freeList;


} MemPool;

typedef struct MemoryHeader {
    TMemorySize chunksize;
    uint64_t chkvalue;
} MemoryHeader;


TStatus RVCMemoryPoolCreate(void *base, TMemorySize size, TMemoryPoolIDRef memoryref);
TStatus RVCMemoryPoolDelete(TMemoryPoolID memory);
TStatus RVCMemoryPoolQuery(TMemoryPoolID memory, TMemorySizeRef bytesleft);
TStatus RVCMemoryPoolAllocate(TMemoryPoolID memory, TMemorySize size, void **pointer);
TStatus RVCMemoryPoolDeallocate(TMemoryPoolID memory, void *pointer);


FreeListNode* allocateNewFreeListNode();
void MEMORY_init();
void FREELIST_initialize(FreeList *freelist, TMemorySize size, char* base);
void* FREELIST_reserve_first_fit(FreeList *freelist, TMemorySize size);
void FREELIST_free_and_coalesce(FreeList *freelist, char* base, TMemorySize amount_to_free);
void FREELISTNODE_delete(FreeListNode* deleteMe);
void FREELISTNODE_delete_recursive(FreeListNode* deleteMe);