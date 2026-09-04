#include "mem.h"

// NULL pNextByAddr means block is the last one in the pool, so measure
// against the pool's end address instead.
u32 GetFreeBlockSize(MemBlock *block, u32 poolIndex)
{
    void *next = block->pNextByAddr;

    if (next == NULL) {
        next = gMemPool[poolIndex].pEnd;
    }
    return (u32)(next - (void *)block) - sizeof(MemBlock);
}
