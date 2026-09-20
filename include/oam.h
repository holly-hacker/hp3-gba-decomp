#pragma once

#include "types.h"

// GBA hardware OAM base address (see GBATEK).
#define OAM_BASE ((void *)0x07000000)

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
