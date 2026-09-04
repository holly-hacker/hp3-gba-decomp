#include "mem.h"

// Same first-fit search as AllocBlock, but memsets the returned block to
// 0. The round-up's stepwise shape and the loop below are both required
// to match -- see docs/memory-map/heap.md.
void *AllocZeroed(u32 size)
{
    u32 len = size;
    u32 searchLen;
    u32 poolIndex;
    MemBlock **pFreeListHeadSlot;
    MemBlock *block;
    u32 blockSize;
    void *dst;

    len += 0xf;
    len &= ~0xf;
    searchLen = len;
    searchLen += 0xf;
    searchLen &= ~0xf;

    poolIndex = 0;
    if (poolIndex < gMemPoolCount) {
        MemBlock **base = (MemBlock **)gMemPool;
        pFreeListHeadSlot = (MemBlock **)((u8 *)base + 4);
        do {
            block = *pFreeListHeadSlot;
            if (block != NULL) {
                do {
                    blockSize = GetFreeBlockSize(block, poolIndex);
                    if (blockSize >= searchLen) {
                        goto found;  // inlining this instead compiles the match-path as fallthrough, not a branch, and misplaces real's literal pool
                    }
                    block = block->pNextFree.pBlock;
                } while (block != NULL);
            }
            goto nextPool;

        found:
            if (blockSize > searchLen) {
                MemBlock *newBlock = (MemBlock *)((u8 *)block + (searchLen + sizeof(MemBlock)));

                LinkBlockByAddress(block, newBlock);
                LinkFreeBlock(block, newBlock);
            }
            UnlinkFreeBlock(block, poolIndex);
            block->pNextFree.dwValue = poolIndex;
            block->pPrevFree.dwValue = -1;
            dst = (u8 *)block + sizeof(MemBlock);
            goto done;

        nextPool:
            pFreeListHeadSlot = (MemBlock **)((u8 *)pFreeListHeadSlot + sizeof(MemPool));
            poolIndex++;
        } while (poolIndex < gMemPoolCount);
    }
    dst = NULL;

done:
    if (dst != NULL) {
        memset(dst, 0, len);
    }
    return dst;
}
