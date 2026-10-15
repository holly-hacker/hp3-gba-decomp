#include "mem.h"

// First-fit allocator: walks each pool's free list for the first block
// that fits, splitting off the remainder if it's bigger than needed.
// Returns NULL if no pool has room. AllocZeroed is the zero-initializing
// twin.
void *AllocBlock(u32 size)
{
    u32 len = (size + 0xf) & ~0xf;
    u32 poolIndex;
    MemBlock **pFreeListHeadSlot;
    MemBlock *block;
    u32 blockSize;

    poolIndex = 0;
    if (poolIndex < gMemPoolCount) {
        MemBlock **base = (MemBlock **)gMemPool;
        pFreeListHeadSlot = (MemBlock **)((u8 *)base + 4);
        do {
            block = *pFreeListHeadSlot;
            if (block != NULL) {
                do {
                    blockSize = GetFreeBlockSize(block, poolIndex);
                    if (blockSize >= len) {
                        goto found;  // inlining this instead compiles the match-path as fallthrough, not a branch, and misplaces real's literal pool
                    }
                    block = block->pNextFree.pBlock;
                } while (block != NULL);
            }
            goto nextPool;

        found:
            if (blockSize > len) {
                MemBlock *newBlock = (MemBlock *)((u8 *)block + (len + sizeof(MemBlock)));

                LinkBlockByAddress(block, newBlock);
                LinkFreeBlock(block, newBlock);
            }
            UnlinkFreeBlock(block, poolIndex);
            block->pNextFree.dwValue = poolIndex;
            block->pPrevFree.dwValue = -1;
            return (u8 *)block + sizeof(MemBlock);

        nextPool:
            pFreeListHeadSlot = (MemBlock **)((u8 *)pFreeListHeadSlot + sizeof(MemPool));
            poolIndex++;
        } while (poolIndex < gMemPoolCount);
    }
    return NULL;
}
