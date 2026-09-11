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
extern void ClearPaletteRam(void);

// General-purpose sprite/animation object, 0x128 bytes (confirmed by
// ExitBattle's Folio Universitas/Help resume path, which memcpys a whole one
// into FightState.aSuspendedFighterObjects_candidate -- see battle.h). Only
// the fields touched by UpdateBattle/TickPlayerActionState/ExitBattle are
// named; see those files' plate comments for the rest.
typedef struct Object {
    u8 pad_00[0x08];
    u16 wFighterType;       // 0x08
    u8 pad_0A[0x02];        // -> 0x0C
    u32 dwFlags;            // 0x0C, bit 0x40000 = action-animation-done, bit 0x8000 = special-move trigger
    u8 pad_10[0x04];        // -> 0x14
    u16 wMoveDuration;      // 0x14
    u8 bUnk16;              // 0x16
    u8 pad_17[0x0D];        // -> 0x24
    ParticleEmitter *pWindupParticleEmitter;  // 0x24, freed via
                             // ReleaseParticleEmitter_candidate and zeroed
                             // when nonzero (see ClearParalyzedFighter_candidate)
    u32 dwUnk_0x28;         // 0x28, set to 1 by InitPlayerBattleActor_candidate
    u32 nX;                 // 0x2C, 16.16
    u32 nY;                 // 0x30, 16.16
    u8 pad_34[0x08];        // -> 0x3C
    u32 nVelX;              // 0x3C
    u32 nVelY;              // 0x40
    u8 pad_44[0x1C];        // -> 0x60
    u8 bAttackOutcomeState; // 0x60
    u8 pad_61[0x01];        // -> 0x62
    u16 wStagedDamage;      // 0x62
    u8 pad_64[0x18];        // -> 0x7C
    u8 bUnk_0x7C;           // 0x7C, zeroed by InitPlayerBattleActor_candidate
    u8 pad_7D[0x03];        // -> 0x80
    u32 dwStateTimer;       // 0x80
    u8 pad_84[0x02];        // -> 0x86
    u16 wUnk86;             // 0x86, zeroed alongside wMoveDuration
    u8 pad_88[0x02];        // -> 0x8a
    u16 wActionVariant;     // 0x8A
    u8 pad_8C[0x01];        // -> 0x8D
    u8 bActionState;        // 0x8D, the dispatch key
    u8 pad_8E[0x02];        // -> 0x90
    u8 bActionFlags;        // 0x90
    u8 bFighterIndex;       // 0x91
    u8 pad_92[0x06];        // -> 0x98
    void (*pfnTick)(struct Object *obj);  // 0x98, per-frame tick (player fighters: TickPlayerActionState)
    u8 pad_9C[0x04];        // -> 0xA0
    struct Object *pShadowObject;  // 0xA0, companion object (main -> shadow)
    void *pLinkedObject_candidate;  // 0xA4; see docs/formats/room_scripts.md and
                                     // docs/formats/save.md's per-object save table
                                     // (Object+0xa0/+0xa4/+0xa8, three linked-object slots)
    struct Object *pOwnerObject;   // 0xA8, back-link (shadow -> main)
    u8 pad_AC[0x25];        // -> 0xD1
    u8 bFlags_0xD1;         // 0xD1, bit 0x20 set / bits 0x0C cleared by InitializeBattle
    u8 pad_D2[0x03];        // -> 0xD5
    u8 bGfxSlotAndFlags;    // 0xD5, upper nibble = graphics-cache slot
    u8 pad_D6[0x03];        // -> 0xD9
    u8 bAnimFrameDelay;     // 0xD9
    u8 pad_DA[0x02];        // -> 0xDC
    u8 bEnemyAttackPhase_candidate;  // 0xDC, TickFighterAttackAnimState_candidate's own
                             // multi-step sentinel: 0xff idle, 0/2/3/4 successive phases
                             // -- real compares it unsigned against 0xff, not as a signed -1
    u8 pad_DD[0x07];        // -> 0xE4
    u8 *pAnimFrameCursor;   // 0xE4
    u8 *pAnimFrameBase;     // 0xE8
    u8 pad_EC[0x112 - 0xEC];  // -> 0x112
    u16 wUnk_112;           // 0x112, set to 0xFFFF by ExitBattle when suspending a fighter for the
                             // Folio Universitas/Help resume path -- meaning otherwise unconfirmed
    u8 pad_114[0x128 - 0x114];  // -> 0x128
} Object;
