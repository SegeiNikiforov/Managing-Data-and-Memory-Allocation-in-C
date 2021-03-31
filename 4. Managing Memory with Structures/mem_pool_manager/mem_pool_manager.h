#include <memory.h>
#include <stdbool.h>

#ifndef MEM_POOL_MANAGER_H
#define MEM_POOL_MANAGER_H

typedef struct MemoryPoolBlock {
    void* data;
    bool is_alloc;
    size_t size;
    struct MemoryPoolBlock *next;
} MemoryPoolBlock;

typedef struct MemoryPoolManager {
    size_t pool_size;
    size_t mem_block_size;
    u_int32_t mem_block_count;
    MemoryPoolBlock *head;
} MemoryPoolManager;

typedef enum {
    MEMORY_POOL_INIT_ERROR,
    MEMORY_POOL_DESTROY_ERROR,
    MEMORY_POOL_ALLOC_ERROR,
    MEMORY_POOL_OK
} MemoryPoolError;

MemoryPoolError mem_pool_init(MemoryPoolManager **pool, size_t mem_block_size, u_int32_t mem_block_count);

MemoryPoolError mem_pool_destroy(MemoryPoolManager *pool);

MemoryPoolError mem_pool_alloc(MemoryPoolManager *pool, MemoryPoolBlock **block);

MemoryPoolError mem_pool_free(MemoryPoolManager *pool, MemoryPoolBlock *block);

void print_mem_blocks(MemoryPoolManager *pool);

void print_block(MemoryPoolBlock *block);

#endif
