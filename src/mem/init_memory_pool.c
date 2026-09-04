#include "mem.h"

// Registers heap pool poolIndex, reserving a MemBlock header at the
// start for the pool's first (and initially only) free block.
void InitMemoryPool(u32 poolIndex, void *start, void *end)
{
    MemBlock *base = (MemBlock *)((u8 *)start + sizeof(MemBlock));
    u32 capacity = (u32)(end - start) - sizeof(MemBlock);
    MemBlock *hdr;

    gMemPool[poolIndex].pBase = base;
    gMemPool[poolIndex].pFreeListHead = base;
    gMemPool[poolIndex].dwCapacity = capacity;
    gMemPool[poolIndex].pEnd = end;

    hdr = gMemPool[poolIndex].pBase;
    hdr->pNextByAddr = NULL;
    hdr->pPrevByAddr = NULL;
    hdr->pNextFree.pBlock = NULL;
    hdr->pPrevFree.pBlock = NULL;

    gMemPoolCount++;
}
