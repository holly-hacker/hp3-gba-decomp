#pragma once

#include "types.h"
#include "mem.h"

// See docs/formats/graphics.md.

// The 15-slot resource cache.
typedef struct ResourceCacheSlot {
    void *pData;
    u16 wRefcount;
    u16 wFlags;  // bit 0x1 = in-use; cleared when wRefcount reaches 0
} ResourceCacheSlot;
extern ResourceCacheSlot g_aResourceCache[15];  // 0x03005114

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

extern void DecrementResourceCacheRefcount(s32 slotIndex);
extern void ReleaseParticleEmitter_candidate(ParticleEmitter *emitter);
