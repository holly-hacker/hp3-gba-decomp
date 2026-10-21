#pragma once

#include "types.h"

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

// The entry's attribute 1 as a whole halfword. When affineMode is set, bits 9-13
// (matrixNum, hFlip, vFlip) hold the affine parameter-set index.
#define OAM_ATTR1(oam) (((u16 *)(oam))[1])

// Double-buffered OAM staging area. The vblank DMA alternates between the
// two halves (g_bOamDmaHalfToggle), so an entry that differs between them
// shows on alternate vblanks.
typedef struct OamShadowBuffer {
    OamEntry aHalves[2][128];
} OamShadowBuffer;
extern OamShadowBuffer g_OamShadowBufferA;
extern OamShadowBuffer g_OamShadowBufferB;

// Buffer game code is currently writing sprite attributes into.
extern OamShadowBuffer *g_pOamShadowBuffer;
// Buffer HandleVBlankInterrupt is currently DMA-flushing to real OAM;
// snapshotted from g_pOamShadowBuffer when the two buffers are swapped.
extern OamShadowBuffer *g_pOamDmaShadowBuffer;

// Number of OAM entries queued into g_pOamShadowBuffer this frame; reset to
// 0 once HandleVBlankInterrupt has swapped buffers.
extern u8 g_bOamEntryCount;
// Snapshot of g_bOamEntryCount taken just before it's reset -- the queued
// entry count from the frame that's now being DMA-flushed.
extern u8 g_bOamEntryCountPrev;

extern void InitOamSystem(void);
extern void ClearOamShadowBuffers(void);
extern void HideUnusedOamEntries(void);

// Return -1 when the queue is full. SubmitOamAttrsNudged jitters the entry by
// 1 pixel between the halves.
extern s32 QueueOamEntry(u8 index, OamEntry *pEntry);
extern s32 SubmitOamAttrsNudged(u8 index, OamEntry *pEntry);
// Hides the entry in the second half only.
extern void HideOamEntryOnAlternateVblanks(u32 index);
// Sets an entry visible (non-affine) or hidden in both halves.
extern void ShowOamEntry(u32 index);
extern void HideOamEntry(u32 index);
// Claims the first entry hidden in the first half, or returns 0xFF if none.
extern u32 AllocOamEntry(void);
extern void FreeOamEntry(u8 index);

// bios_ObjAffineSet's input struct (see include/hw/bios.h): reciprocal
// scale (8.8 fixed) plus rotation angle, in 8-byte entries.
// AllocAffineSlot/FreeAffineSlot manage g_abAffineSlotUsed/g_bAffineSlotHighWaterMark (see ram_symbols.us.inc);
// GetActorAffineSlotId/SetActorAffineSlotId read/write the allocated
// index in an OamEntry's affine index bits (see OAM_ATTR1).
typedef struct ObjAffineSource {
    s16 sx;
    s16 sy;
    u16 theta;
} ObjAffineSource;
extern ObjAffineSource g_aObjAffineSetSource[32];  // 0x03005014
extern u8 g_bAffineSlotHighWaterMark;
extern u8 g_abAffineSlotUsed[32];
extern void ResetAffineSlots(void);
extern u32 AllocAffineSlot(void);  // lowest free slot, or 32 when all are in use
extern void FreeAffineSlot(u16 slot);
extern void CommitObjAffineMatrices(void);
extern u32 GetActorAffineSlotId(OamEntry *oam);
extern void SetActorAffineSlotId(OamEntry *oam, u16 slot);

// Dimensions of each OAM shape/size pair, indexed [shape][size].
typedef struct OamShapeSize {
    u8 bWidth;            // pixels
    u8 bHeight;           // pixels
    u16 wTileBytes4bpp;   // bWidth * bHeight / 2
} OamShapeSize;
