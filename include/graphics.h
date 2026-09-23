#pragma once

#include "types.h"
#include "mem.h"

// See docs/formats/graphics.md.

// The two proprietary resource-compression codecs (dispatch types 4/6;
// not the real BIOS LZ77/Huffman/RLE). InstallIwramDecompressCodecs
// copies both into IWRAM at startup for speed and records each copy's
// address in the matching g_pDecompressType*Entry global; the
// resource-decompression dispatcher calls through those, not the ROM
// copies directly.
typedef void (*DecompressFunc)(const void *src, void *dst, u32 *pSize);
void DecompressType4(const void *src, void *dst, u32 *pSize);
void DecompressType6(const void *src, void *dst, u32 *pSize);
void InstallIwramDecompressCodecs(void);
extern DecompressFunc g_pDecompressType4Entry;
extern DecompressFunc g_pDecompressType6Entry;
extern u8 g_pDecompressType4Iwram[0x1F8];
extern u8 g_pDecompressType6Iwram[0x33C];

// bios_ObjAffineSet's input struct (see include/bios.h): reciprocal
// scale (8.8 fixed) plus rotation angle; the trailing pad word gives
// each entry an 8-byte stride. AllocAffineSlot/FreeAffineSlot manage
// g_abAffineSlotUsed/g_bAffineSlotHighWaterMark (see ram_symbols.us.inc);
// GetObjectAffineSlotId/SetObjectAffineSlotId read/write the allocated
// index out of Object.wAffineSlotIndexPacked.
typedef struct ObjAffineSource {
    s16 sx;
    s16 sy;
    u16 theta;
    u16 pad6;
} ObjAffineSource;
extern ObjAffineSource g_aObjAffineSetSource[32];  // 0x03005014

// OBJ palette resource: 16 BGR555 entries. Entry 0 is the transparent color and is
// not uploaded; entries 1-15 fill the OBJ palette bank (see AttachObjectPalette).
typedef struct ObjPalette {
    u16 aColors[16];
} ObjPalette;

// The 16-slot OBJ palette bank cache (slot index = OBJ palette bank; see
// AttachObjectPalette).
typedef struct ResourceCacheSlot {
    void *pData;
    u16 wRefcount;
    u16 wFlags;  // bit 0x1 = in-use; cleared when wRefcount reaches 0
} ResourceCacheSlot;
extern ResourceCacheSlot g_aResourceCache[16];  // 0x03005114
extern void ClearResourceCacheSlots(void);
extern u32 FindResourceCacheSlot(const ObjPalette *pPalette);
extern u32 AllocResourceCacheSlot(void);

// Node in the particle-emitter active/free lists (see below). ListNode
// must be the first member -- List_MoveToHead/List_Remove address a
// ParticleEmitter* directly as a ListNode*. Only `node` and the
// resource-cache-slot byte are confirmed; the rest of the struct's shape
// (spawn params) isn't decoded.
typedef struct ParticleEmitter {
    ListNode node;           // 0x00
    u8 pad_08[0x3E - 0x08];
    u8 bResourceCacheSlot;   // 0x3E, index into g_aResourceCache
} ParticleEmitter;

// See docs/formats/battle_scripts.md's TickParticleEmitters note --
// TickParticleEmitters walks g_pParticleEmitterActiveListHead each frame.
extern ListNode *g_pParticleEmitterFreeListHead;    // 0x030051B0
extern u16 g_wActiveParticleEmitterCount;           // 0x030051A0
extern ListNode *g_pParticleEmitterActiveListHead;  // 0x03005198
extern void TickParticleEmitters(void);

extern void DecrementResourceCacheRefcount(s32 slotIndex);
extern void ReleaseParticleEmitter_candidate(ParticleEmitter *emitter);
