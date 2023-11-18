#include "include/memory.h"
#include "include/list.h"


List *createList() {
    List *list = (List *)malloc(sizeof(List));
    if (list != NULL) {
        initializeList(list);
    }
    return list;
}

void initializeList(List *list) {
    if (list != NULL) {
        list->array = NULL;
        list->allocated_length = 0;
        list->num_items = 0;
    }
}

void *getList(List *list, ListID id) {
    if (list == NULL || id >= list->num_items) {
        return NULL;
    }
    return list->array[id];
}

ListID putList(List *list, void *item) {
    if (list == NULL) {
        return UINT32_MAX;  // Invalid ID
    }

    if (list->num_items >= list->allocated_length) {
        reallocateList(list, list->allocated_length * 2 + 1);
    }

    list->array[list->num_items] = item;
    list->num_items++;

    return list->num_items - 1;
}

void reallocateList(List *list, int new_quantity) {
    void **new_array = (void **)realloc(list->array, new_quantity * sizeof(void *));
    if (new_array != NULL) {
        list->array = new_array;
        list->allocated_length = new_quantity;
    }
}