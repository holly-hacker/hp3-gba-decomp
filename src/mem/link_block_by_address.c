#include "mem.h"

// Inserts newBlock into the address-ordered block list right after
// afterBlock; used to link a split's leftover remainder.
void LinkBlockByAddress(MemBlock *afterBlock, MemBlock *newBlock)
{
    MemBlock *next;

    newBlock->pPrevByAddr = afterBlock;

    next = afterBlock->pNextByAddr;
    newBlock->pNextByAddr = next;

    afterBlock->pNextByAddr = newBlock;

    if (next != NULL) {
        next->pPrevByAddr = newBlock;
    }
}
