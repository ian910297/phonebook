#include <stdlib.h>

#include "pool.h"

MEMPool* initPool(size_t size)
{
    MEMPool *pool = (MEMPool*)malloc(sizeof(MEMPool));

    pool->ptr = malloc(size);
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
    free(pool);
}
