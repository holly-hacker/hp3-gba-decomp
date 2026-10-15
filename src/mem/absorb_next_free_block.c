#include "mem.h"

// If the block after block in address order is free, unlinks it from its
// free list and folds it into block.
void AbsorbNextFreeBlock(MemBlock *block, u32 poolIndex)
{
    MemBlock *next = block->pNextByAddr;

    if (next != NULL && next->pPrevFree.dwValue != -1) {
        if (next->pPrevFree.pBlock != NULL)
            next->pPrevFree.pBlock->pNextFree.pBlock = next->pNextFree.pBlock;
        if (next->pNextFree.pBlock != NULL)
            next->pNextFree.pBlock->pPrevFree.pBlock = next->pPrevFree.pBlock;

        block->pNextByAddr = next->pNextByAddr;
        if (next->pNextByAddr != NULL)
            next->pNextByAddr->pPrevByAddr = block;
    }
}
