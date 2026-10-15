#include "mem.h"

// Resizes an allocated block in place, returning ptr, or NULL if growing
// it would need more than the free block right after it. Shrinking
// splits the tail off as a new free block.
void *ResizeBlock(void *ptr, u32 size)
{
    MemBlock *block = (MemBlock *)((u8 *)ptr - sizeof(MemBlock));
    u32 poolIndex = block->pNextFree.dwValue;
    u32 blockSize;
    MemBlock *newBlock;
    MemBlock *next;
    u32 available;

    size = (size + 0xf) & ~0xf;
    blockSize = GetFreeBlockSize(block, poolIndex);

    if (size < blockSize) {
        newBlock = (MemBlock *)((u8 *)ptr + size);
        LinkBlockByAddress(block, newBlock);
        PushFreeBlock(newBlock, poolIndex);
        AbsorbNextFreeBlock(newBlock, poolIndex);
    } else if (size > blockSize) {
        next = block->pNextByAddr;
        available = blockSize + sizeof(MemBlock) + GetFreeBlockSize(next, poolIndex);
        if (next->pPrevFree.dwValue == -1 || size > available)
            return NULL;

        if (size < available) {
            newBlock = (MemBlock *)((u8 *)ptr + size);
            LinkBlockByAddress(next, newBlock);
            LinkFreeBlock(next, newBlock);
        }
        UnlinkFreeBlock(next, poolIndex);
        UnlinkBlockByAddress(next, poolIndex);
    }
    return ptr;
}
