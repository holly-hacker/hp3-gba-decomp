#include "mem.h"

// Inserts newBlock into the per-pool free list right after afterBlock.
void LinkFreeBlock(MemBlock *afterBlock, MemBlock *newBlock)
{
    MemBlock *next;

    newBlock->pPrevFree.pBlock = afterBlock;

    next = afterBlock->pNextFree.pBlock;
    newBlock->pNextFree.pBlock = next;

    afterBlock->pNextFree.pBlock = newBlock;

    if (next != NULL) {
        next->pPrevFree.pBlock = newBlock;
    }
}
