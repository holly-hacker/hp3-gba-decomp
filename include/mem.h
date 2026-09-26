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
//
// The rest of the state follows: a queue that TickObjectList fills with the
// objects whose UpdateObjectOamCells result was 2, and a byte that gates its
// extra OAM pass (see docs/memory-map/heap.md).
typedef struct ObjectPoolState {
    void *pBuffer;
    void *pFreeListHead;
    u8 bTileUpdateQueueCount;  // 0x08, consumed and reset by CommitQueuedObjectTileUpdates
    u8 pad_9[0x03];            // -> 0x0C
    struct Object *apTileUpdateQueue[0x69];  // 0x0C, objects whose OAM update returned 2
    u8 bExtraOamPassEnabled_candidate;   // 0x1B0, nonzero enables TickObjectList's extra pass
    u8 pad_1B1[0x03];
} ObjectPoolState;
extern ObjectPoolState g_ObjectPoolState;

// One 0x34-byte record of g_pObjectPoolAuxBuffer (5 records), selected by
// Object.bObjectPoolAuxSlot. Tracks VRAM tile allocations shared between
// objects: abRefCounts[i] counts the objects holding the allocation whose id
// is in awTileAllocIds[i] (0xFFFF = none). Field extents past the ones
// ReleaseObjectOffscreenVramTiles touches are unconfirmed.
typedef struct ObjectPoolAuxRecord {
    u8 pad_00[0x08];
    u16 awTileAllocIds[12];  // 0x08
    u8 abRefCounts[0x14];    // 0x20
} ObjectPoolAuxRecord;
extern ObjectPoolAuxRecord *g_pObjectPoolAuxBuffer;
extern u8 g_pSortObjectsIwram[0xC4];
extern u8 g_pCheckObjectCollisionsIwram[0x1F4];
extern u8 g_pFindFreeObjTileRunIwram[0x9C];
u32 FindFreeObjTileRun(const u8 *pBitmap, u32 runLength, u32 startBit);
// OBJ VRAM tile allocator bitmaps, one bit per 32-byte tile (1024 tiles).
// A set bit in g_adwObjTileAllocBitmap marks a tile in use. Freeing a run
// clears its bits in g_adwObjTileFreeMask only; ApplyDeferredObjTileFrees
// folds the mask into the bitmap on a vblank that swaps the OAM buffers.
extern u32 g_adwObjTileAllocBitmap[32];
extern u32 g_adwObjTileFreeMask[32];
void ApplyDeferredObjTileFrees(void);
extern u32 g_dwObjectListActive_candidate;
// Zeroed by InitObjectPool; read in WriteObjectOamCells as what looks
// like a fixed-point rounding/scale constant, unrelated to the pool
// itself. Not enough evidence yet for a real name.
extern u32 g_dwUnk03001DC4;
// Set to 1 by every TickActiveObjects call and never cleared, so it is 0
// only until the active list's first tick. FreeObject releases the object's
// shared VRAM tile allocation (ReleaseObjectOffscreenVramTiles) only when it
// is 1; those allocations are made by UpdateObjectSpriteFrame during a tick.
extern u32 g_dwObjectListTicked_candidate;

// pHead/pUnk4 are adjacent words (0x030015B0/0x030015B4) -- FreeObject loads
// the base address once and reaches pUnk4 through it at +4, so this stays
// one struct rather than two independent globals (see ObjectPoolState for
// the same pattern).
typedef struct ActiveObjectListState {
    ListNode *pHead;  // objects join it via AllocObjectFromFreeList and List_MoveToHead
    ListNode *pUnk4;  // FreeObject advances this to the freed object's pPrev when
                       // it points at that object. Not enough evidence yet for a real name.
} ActiveObjectListState;
extern ActiveObjectListState g_ActiveObjectListState;

// Per-tick queues TickObject fills from the active list and TickObjectList drains.
// Counts are reset at the start of every TickObjectList call.
extern struct Object *g_apSpriteFrameQueue[15];  // 0x03001760, visible objects with sprite cells
extern u8 g_bSpriteFrameQueueCount;              // 0x0300179C
extern struct Object *g_apOamQueue[0x69];        // 0x030015B8, onscreen objects drawn by depth order
extern u32 g_dwOamQueueCount;                    // 0x0300175C
extern struct Object *g_apCollisionQueue[0x69];  // 0x030017A4, objects awaiting the pairwise check
extern u32 g_dwCollisionQueueCount;              // 0x03001948

void *AllocObjectFromFreeList(ListNode **freeListHead, ListNode **activeListHead, u32 size);
void FreeAllObjects(ListNode **activeListHead);

void SortObjectsByDepth(void);
void CheckObjectCollisions(void);
void InitObjectPool(void);
