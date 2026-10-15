#pragma once

#include "types.h"
#include "list.h"

// See docs/memory-map/heap.md.

// +8/+0xC's meaning depends on whether the block is free or allocated:
// free, they're the pool's free-list link (a MemBlock*); allocated,
// AllocBlock/AllocZeroed repurpose them as the owning pool index (+8)
// and a -1 live marker (+0xC), so this is a union rather than a plain
// pointer type.
typedef union MemBlockLink {
    struct MemBlock *pBlock;
    u32 dwValue;
} MemBlockLink;

// Free/allocated block header, 0x10 bytes; the block's payload follows
// immediately. pNextByAddr/pPrevByAddr thread every block in the pool
// (free or allocated) in address order; pNextFree/pPrevFree thread only
// the free blocks (see MemBlockLink for the allocated-block reuse).
typedef struct MemBlock {
    struct MemBlock *pNextByAddr;
    struct MemBlock *pPrevByAddr;
    MemBlockLink pNextFree;
    MemBlockLink pPrevFree;
} MemBlock;

// One heap pool's bookkeeping record, 0x10 bytes; gMemPool is indexed by
// pool number, though only pool 0 is ever registered (see InitHeap).
typedef struct MemPool {
    void *pBase;
    MemBlock *pFreeListHead;
    u32 dwCapacity;
    void *pEnd;
} MemPool;

extern MemPool gMemPool[];
extern u32 gMemPoolCount;

void InitMemoryPool(u32 poolIndex, void *start, void *end);
void InitHeap(void);
u32 GetFreeBlockSize(MemBlock *block, u32 poolIndex);
void LinkBlockByAddress(MemBlock *afterBlock, MemBlock *newBlock);
void LinkFreeBlock(MemBlock *afterBlock, MemBlock *newBlock);
void UnlinkFreeBlock(MemBlock *block, u32 poolIndex);
void PushFreeBlock(MemBlock *block, u32 poolIndex);
void UnlinkBlockByAddress(MemBlock *block, u32 poolIndex);
void MergeIntoPrevFreeBlock(MemBlock *block, u32 poolIndex);
void AbsorbNextFreeBlock(MemBlock *block, u32 poolIndex);
void *AllocBlock(u32 size);
void *AllocZeroed(u32 size);
void FreeBlock(void *ptr);
void *ResizeBlock(void *ptr, u32 size);
u32 HeapStubReturnOne(void);

// Ordinary game code, not the vendored newlib copy in src/libc/ -- see
// docs/memory-map/heap.md.
void *memset(void *dst, int val, u32 len);
void *CopyMemory(void *dst, const void *src, u32 len);
void *MoveMemory(void *dst, const void *src, u32 len);

// Start of pool 0, which InitHeap spans to EWRAM_END.
extern u8 g_abEwramHeap[];  // 0x02002800
