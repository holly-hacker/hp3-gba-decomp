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
void *AllocBlock(u32 size);
void *AllocZeroed(u32 size);
void FreeBlock(void *ptr);

// Ordinary game code, not the vendored newlib copy in src/libc/ -- see
// docs/memory-map/heap.md.
void *memset(void *dst, int val, u32 len);
void *CopyMemory(void *dst, const void *src, u32 len);

// Actor pool: a 0x69-slot, 0x128-byte-stride free list carved out of a
// bulk AllocZeroed'd buffer by InitActorPool, plus a small auxiliary
// buffer and IWRAM-relocated copies of the two per-frame actor-list
// passes (see docs/memory-map/heap.md).
// pBuffer/pFreeListHead are adjacent words (0x03001C08/0x03001C0C) --
// InitActorPool's real code loads pBuffer's address once and reaches
// pFreeListHead through it at +4, so this stays one struct rather than
// two independent globals.
//
// The rest of the state follows: a queue that TickActorList fills with the
// actors whose UpdateActorOamCells result was 2, and a byte that gates its
// extra OAM pass (see docs/memory-map/heap.md).
typedef struct ActorPoolState {
    void *pBuffer;
    void *pFreeListHead;
    u8 bTileUpdateQueueCount;  // 0x08, consumed and reset by CommitQueuedActorTileUpdates
    u8 pad_9[0x03];            // -> 0x0C
    struct Actor *apTileUpdateQueue[0x69];  // 0x0C, actors whose OAM update returned 2
    u8 bExtraOamPassEnabled_candidate;   // 0x1B0, nonzero enables TickActorList's extra pass;
                                         // bits 0-1 are the OAM priority of the vertically
                                         // mirrored, alternate-vblank copies it draws
    u8 pad_1B1[0x03];
} ActorPoolState;
extern ActorPoolState g_ActorPoolState;

// One 0x34-byte record of g_pActorPoolAuxBuffer (5 records), selected by
// Actor.bActorPoolAuxSlot. Tracks VRAM tile allocations shared between
// actors: abRefCounts[i] counts the actors holding the allocation whose id
// is in awTileAllocIds[i] (0xFFFF = none). Index 0 is the ShareTiles
// allocation; ShareFrameTiles indexes by animation frame.
typedef struct ActorPoolAuxRecord {
    u8 pad_00[0x04];
    struct ActorAssetRecord *pAnimTable;  // 0x04, sprite record of the ShareTiles allocation
    u16 awTileAllocIds[12];  // 0x08
    u8 abRefCounts[12];      // 0x20
    u8 bAnimFrame;           // 0x2C, animation frame of the ShareTiles allocation
    u8 pad_2D[0x03];         // -> 0x30
    u32 dwAllocTick;         // 0x30, g_dwTickCount when the ShareTiles allocation was made
} ActorPoolAuxRecord;
extern ActorPoolAuxRecord *g_pActorPoolAuxBuffer;
// IWRAM copies of the ARM routines above, made by InitActorPool and
// InstallIwramFindFreeObjTileRun. They are declared as functions so callers
// can take their address; the ROM calls them through that pointer.
extern void SortActorsByDepthIwram(struct Actor **queue, u32 count);
extern void CheckActorCollisionsIwram(u32 count, struct Actor **queue);
extern u32 FindFreeObjTileRunIwram(const u8 *pBitmap, u32 runLength, u32 startBit);
u32 FindFreeObjTileRun(const u8 *pBitmap, u32 runLength, u32 startBit);
// Nonzero lets TickActorList depth-sort the OAM queue.
extern u32 g_dwActorListActive_candidate;
extern void SetActorListActive_candidate(u32 active);
// Rounding bias for WriteActorOamCells' scaled cell offsets; always 0.
extern u32 g_dwUnk03001DC4;
// Set to 1 by every TickActiveActors call and never cleared, so it is 0
// only until the active list's first tick. FreeActor releases the actor's
// shared VRAM tile allocation (ReleaseActorOffscreenVramTiles) only when it
// is 1; those allocations are made by UpdateActorSpriteFrame during a tick.
extern u32 g_dwActorListTicked_candidate;

// pHead/pUnk4 are adjacent words (0x030015B0/0x030015B4) -- FreeActor loads
// the base address once and reaches pUnk4 through it at +4, so this stays
// one struct rather than two independent globals (see ActorPoolState for
// the same pattern).
typedef struct ActiveActorListState {
    ListNode *pHead;  // actors join it via AllocObjectFromFreeList and List_MoveToHead
    ListNode *pUnk4;  // FreeActor advances this to the freed actor's pPrev when
                       // it points at that actor. Not enough evidence yet for a real name.
} ActiveActorListState;
extern ActiveActorListState g_ActiveActorListState;

// Per-tick queues TickActor fills from the active list and TickActorList drains.
// Counts are reset at the start of every TickActorList call.
extern struct Actor *g_apSpriteFrameQueue[15];  // 0x03001760, visible actors with sprite cells
extern u8 g_bSpriteFrameQueueCount;              // 0x0300179C
extern struct Actor *g_apOamQueue[0x69];        // 0x030015B8, onscreen actors drawn by depth order
extern u32 g_dwOamQueueCount;                    // 0x0300175C
extern struct Actor *g_apCollisionQueue[0x69];  // 0x030017A4, actors awaiting the pairwise check
extern u32 g_dwCollisionQueueCount;              // 0x03001948
// Cleared by the next TickActor pass that ticks an actor's movement; that
// actor plays sound 0x47 if its position changed. Its writer is unidentified.
extern u32 g_dwUnk03003234;

void FreeAllActors(ListNode **activeListHead);

void SortActorsByDepth(void);
void CheckActorCollisions(void);
void InitActorPool(void);

// Start/end of the statically linked IWRAM and EWRAM sections, as ROM
// pointer constants. kramInstall copies the ROM image of these sections
// to RAM; ClearWorkRam zeroes the RAM above them.
extern u8 g_IwramSectionStart[];  // 0x03000000
extern u8 g_IwramSectionEnd[];    // 0x03001598
extern u8 g_EwramSectionStart[];  // 0x02000000
extern u8 g_EwramSectionEnd[];    // 0x020027F8
// ROM images of those sections, stored back to back.
extern const u8 g_IwramSectionRomImage[];
extern const u8 g_EwramSectionRomImage[];
extern u8 *const g_pIwramSectionStart;
extern u8 *const g_pIwramSectionEnd;
extern u8 *const g_pEwramSectionStart;
extern u8 *const g_pEwramSectionEnd;

// ClearWorkRam leaves IWRAM from here up alone: the IRQ and system stacks
// (gIrqStackTop, gSystemStackTop) and the BIOS area.
#define IWRAM_STACKS ((u8 *)0x03007D00)

// Start of pool 0, which InitHeap spans to EWRAM_END.
extern u8 g_abEwramHeap[];  // 0x02002800

void ClearSystemMemory(void);
void ClearWorkRam(void);
