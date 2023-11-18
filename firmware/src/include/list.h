#include "include/kernel.h"
#include <stdint.h>

typedef struct List {
    void **array;
    uint32_t allocated_length;
    uint32_t num_items;
} List;

typedef uint32_t ListID;

List *createList();
void initializeList(List *list);

void *getList(List *list, ListID id);
ListID putList(List *list, void *item);

void reallocateList(List *list, int new_quantity);