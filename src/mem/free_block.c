#include "mem.h"

// Returns an AllocBlock/AllocZeroed block to its pool's free list,
// coalescing it with free neighbors on both sides.
void FreeBlock(void *ptr)
{
    MemBlock *block = (MemBlock *)((u8 *)ptr - sizeof(MemBlock));
    u32 poolIndex = block->pNextFree.dwValue;

    PushFreeBlock(block, poolIndex);
    AbsorbNextFreeBlock(block, poolIndex);
    MergeIntoPrevFreeBlock(block, poolIndex);
}
