#pragma once

#include "types.h"

// GBA hardware OAM base address (see GBATEK).
#define OAM_BASE ((void *)0x07000000)

// One hardware OAM entry's attributes (see GBATEK). Game code builds these
// in RAM and queues them with QueueOamEntry/SubmitOamAttrsNudged. The first
// word's fields are u32 bitfields and the second word's u16.
typedef struct OamEntry {
    u32 y : 8;
    u32 affineMode : 2;     // 0 = normal, 1 = affine, 2 = hidden, 3 = double-size affine
    u32 objMode : 2;        // 1 = semi-transparent
    u32 mosaic : 1;
    u32 bpp8 : 1;           // 256-color tiles
    u32 shape : 2;
    u32 x : 9;
    u32 matrixNum : 3;      // bits 0-2 of the affine parameter-set index
    u32 hFlip : 1;          // bit 3 of the affine index when affineMode is set
    u32 vFlip : 1;          // bit 4 of the affine index when affineMode is set
    u32 size : 2;
    u16 tileNum : 10;
    u16 priority : 2;
    u16 paletteNum : 4;
    u16 affineParam;
} OamEntry;

// CPU-side OAM staging area, double-buffered so HandleVBlankInterrupt can
// DMA one buffer out to real OAM while game code writes the next frame's
// entries into the other. Each buffer is 0x800 bytes: two 0x400-byte
// (128 OAM entries * 8-byte stride) halves, alternated every vblank by
// g_bOamDmaHalfToggle independently of the buffer-level swap.
extern u8 g_aOamShadowBufferA[0x800];
extern u8 g_aOamShadowBufferB[0x800];

// Buffer game code is currently writing sprite attributes into.
extern void *g_pOamShadowBuffer;
// Buffer HandleVBlankInterrupt is currently DMA-flushing to real OAM;
// snapshotted from g_pOamShadowBuffer when the two buffers are swapped.
extern void *g_pOamDmaShadowBuffer;

// Number of OAM entries queued into g_pOamShadowBuffer this frame; reset to
// 0 once HandleVBlankInterrupt has swapped buffers.
extern u8 g_bOamEntryCount;
// Snapshot of g_bOamEntryCount taken just before it's reset -- the queued
// entry count from the frame that's now being DMA-flushed.
extern u8 g_bOamEntryCountPrev;

extern void HideUnusedOamEntries(void);

// Copy *pEntry into both halves of OAM shadow slot `index` and advance
// g_bOamEntryCount; they return -1 without queuing once the count is negative.
// SubmitOamAttrsNudged also moves the copies 1 pixel right and left respectively.
extern s32 QueueOamEntry(u8 index, OamEntry *pEntry);
extern s32 SubmitOamAttrsNudged(u8 index, OamEntry *pEntry);
// Hides OAM shadow slot `index` in the second half of g_pOamShadowBuffer only,
// so the entry shows on alternate vblanks.
extern void HideOamEntryOnAlternateVblanks(u8 index);
// Writes the pixel width and height of an OAM shape/size pair to dims[0]/dims[1].
extern void GetOamShapeSizeDims(u32 shape, u32 size, s32 *dims);
