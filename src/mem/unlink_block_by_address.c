#include "mem.h"

// Removes block from pool poolIndex's address-ordered block list.
void UnlinkBlockByAddress(MemBlock *block, u32 poolIndex)
{
    if (block->pPrevByAddr != NULL)
        block->pPrevByAddr->pNextByAddr = block->pNextByAddr;
    else
        gMemPool[poolIndex].pBase = block->pNextByAddr;

    if (block->pNextByAddr != NULL)
        block->pNextByAddr->pPrevByAddr = block->pPrevByAddr;
}
