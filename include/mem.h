#pragma once

#include "types.h"

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
void *AllocBlock(u32 size);
void *AllocZeroed(u32 size);
void FreeBlock(void *ptr);
void *BuildFreeList(void *buffer, u32 count, s32 stride);

// Generic intrusive doubly-linked-list node: List_PushHead's `node`
// argument must point at one of these.
typedef struct ListNode {
    struct ListNode *pNext;
    struct ListNode *pPrev;
} ListNode;

void List_PushHead(ListNode **listHead, ListNode *node);
ListNode *List_PopHead(ListNode **listHead);
void List_Remove(ListNode **listHead, ListNode *node);
void List_MoveToHead(ListNode **destListHead, ListNode **srcListHead, ListNode *node);

// Ordinary game code, not the vendored newlib copy in src/libc/ -- see
// docs/memory-map/heap.md.
void *memset(void *dst, int val, u32 len);

// Object pool: a 0x69-slot, 0x128-byte-stride free list carved out of a
// bulk AllocZeroed'd buffer by InitObjectPool, plus a small auxiliary
// buffer and IWRAM-relocated copies of the two per-frame object-list
// passes (see docs/memory-map/heap.md).
// pBuffer/pFreeListHead are adjacent words (0x03001C08/0x03001C0C) --
// InitObjectPool's real code loads pBuffer's address once and reaches
// pFreeListHead through it at +4, so this stays one struct rather than
// two independent globals.
typedef struct ObjectPoolState {
    void *pBuffer;
    void *pFreeListHead;
} ObjectPoolState;
extern ObjectPoolState g_ObjectPoolState;
#define g_pObjectPoolBuffer g_ObjectPoolState.pBuffer
#define sFreeObjectListHead g_ObjectPoolState.pFreeListHead
extern void *g_pObjectPoolAuxBuffer;
extern u8 g_pSortObjectsIwram[0xC4];
extern u8 g_pCheckObjectCollisionsIwram[0x1F4];
extern u32 g_dwObjectListActive_candidate;
// Zeroed by InitObjectPool; read in WriteObjectOamCells as what looks
// like a fixed-point rounding/scale constant, unrelated to the pool
// itself. Not enough evidence yet for a real name.
extern u32 g_dwUnk03001DC4;

// Head of the active-object list; objects join it via
// AllocObjectFromFreeList and List_MoveToHead.
extern ListNode *sActiveObjectListHead;

void *AllocObjectFromFreeList(ListNode **freeListHead, ListNode **activeListHead, u32 size);
extern void sub_080015D4(ListNode **listHead);  // called by ExitBattle with &sActiveObjectListHead

void SortObjectsByDepth_candidate(void);
void CheckObjectCollisions_candidate(void);
void InitObjectPool(void);
