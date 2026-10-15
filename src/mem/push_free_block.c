#include "mem.h"

// Pushes block onto the front of pool poolIndex's free list.
void PushFreeBlock(MemBlock *block, u32 poolIndex)
{
    MemBlock *head;

    block->pPrevFree.pBlock = NULL;
    head = gMemPool[poolIndex].pFreeListHead;
    block->pNextFree.pBlock = head;
    gMemPool[poolIndex].pFreeListHead = block;
    if (head != NULL)
        head->pPrevFree.pBlock = block;
}
