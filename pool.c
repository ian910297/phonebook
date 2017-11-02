#include <stdlib.h>
#include <malloc.h>

#include "pool.h"

//#define MEM_ALIGN

MEMPool* initPool(size_t size)
{
    MEMPool *pool = (MEMPool*)malloc(sizeof(MEMPool));

#ifndef MEM_ALIGN
    pool->ptr = malloc(size);
#else
    pool->ptr = memalign(16, size);
#endif
    pool->used = 0;
    pool->size = size;

    return pool;
}

void* poolloc(size_t size, MEMPool *pool)
{
    if (pool->used + size <= pool->size) {
        void *p = pool->ptr + pool->used;
        pool->used += size;
        return p;
    }

    return NULL;
}

void freePool(MEMPool *pool)
{
    free(pool->ptr);
    free(pool);
}
