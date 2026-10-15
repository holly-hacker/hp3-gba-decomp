#include "mem.h"

// If the block before block in address order is free, folds block into it.
// block must be at the head of pool poolIndex's free list, as FreeBlock has
// just pushed it there; its successor in that list becomes the head. That
// successor is written without a NULL check.
void MergeIntoPrevFreeBlock(MemBlock *block, u32 poolIndex)
{
    MemBlock *prev = block->pPrevByAddr;

    if (prev != NULL && prev->pPrevFree.dwValue != -1) {
        MemBlock *head = gMemPool[poolIndex].pFreeListHead;
        MemBlock *nextFree = block->pNextFree.pBlock;

        if (head == block)
            gMemPool[poolIndex].pFreeListHead = nextFree;
        nextFree->pPrevFree.pBlock = NULL;

        prev->pNextByAddr = block->pNextByAddr;
        if (block->pNextByAddr != NULL)
            block->pNextByAddr->pPrevByAddr = prev;
    }
}
