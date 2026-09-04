#include "mem.h"

// Removes block from pool poolIndex's free list.
void UnlinkFreeBlock(MemBlock *block, u32 poolIndex)
{
    if (block->pPrevFree.pBlock != NULL) {
        block->pPrevFree.pBlock->pNextFree.pBlock = block->pNextFree.pBlock;
    } else {
        gMemPool[poolIndex].pFreeListHead = block->pNextFree.pBlock;
    }

    if (block->pNextFree.pBlock != NULL) {
        block->pNextFree.pBlock->pPrevFree.pBlock = block->pPrevFree.pBlock;
    }
}
