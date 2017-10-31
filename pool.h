#pragma once
#include <stddef.h>

typedef struct {
    void *ptr;
    size_t used;
    size_t size;
} MEMPool;

MEMPool* initPool(size_t size);
void* poolloc(size_t size, MEMPool *pool);
void freePool(MEMPool *pool);
