#pragma once

#include "types.h"
#include "hw/mem.h"
#include "graphics/oam.h"

// See docs/formats/graphics.md.

// The two proprietary resource-compression codecs (dispatch types 4/6;
// not the real BIOS LZ77/Huffman/RLE). InstallIwramDecompressCodecs
// copies both into IWRAM at startup for speed and records each copy's
// address in the matching g_pDecompressType*Entry global; the
// resource-decompression dispatcher calls through those, not the ROM
// copies directly.
typedef void (*DecompressFunc)(const void *src, void *dst, u32 *pSize);
void DecompressLzRle(const void *src, void *dst, u32 *pSize);
void DecompressGammaLz(const void *src, void *dst, u32 *pSize);
void InstallIwramDecompressCodecs(void);
extern DecompressFunc g_pDecompressLzRleEntry;
extern DecompressFunc g_pDecompressGammaLzEntry;
extern u8 g_pDecompressLzRleIwram[0x1F8];
extern u8 g_pDecompressGammaLzIwram[0x33C];

// bios_ObjAffineSet's input struct (see include/hw/bios.h): reciprocal
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

// Header of a particle sprite resource; ParticleEmitter.pSprite points at a
// record whose second word points here.
typedef struct ParticleSpriteHeader {
    u8 pad_00[0x06];
    u16 wFrameCount_candidate;  // 0x06, the spawn code divides a particle's lifetime by it
} ParticleSpriteHeader;

typedef struct ParticleSprite {
    u8 pad_00[0x04];
    const ParticleSpriteHeader *pHeader;  // 0x04
} ParticleSprite;

// One 0x2C-byte record of a particle graphics pool (g_apParticleGfxPools[pool]).
// The OBJ tile allocation is made when the pool is loaded (sub_08030A1C) and released by
// sub_08031668.
typedef struct ParticleGfxEntry {
    u16 wTileAllocId;       // 0x00, 0xFFFF = none
    u16 wTileRow;           // 0x02
    u8 aAnimData[0x20];     // 0x04, ParticleEmitter.pAnimData points here
    const ParticleSprite *pSprite;  // 0x24
    u8 pad_28[0x04];        // -> 0x2C
} ParticleGfxEntry;

// ParticleEmitter.wFlags. Bits not listed here are unused by the code decoded so far.
typedef enum {
    ParticleEmitterFlagFourWayDirections = 0x0001,  // mode 1 picks from the 4-way vector table
    ParticleEmitterFlagRelease          = 0x0002,  // count wDuration down, then release
    ParticleEmitterFlagAnimTicksFixed   = 0x0004,  // particles use bAnimTicks instead of a
                                                    // lifetime-derived value
    ParticleEmitterFlagSpawnDisabled    = 0x0040,  // no spawning while set
    ParticleEmitterFlagPriorityFromTarget = 0x0100,  // particle OAM priority = the target's
    ParticleEmitterFlagScreenPosition   = 0x0200,  // spawn at the target's OAM position, with
                                                    // particle priority 1, even when the target
                                                    // isn't onscreen
    ParticleEmitterFlagPriorityBelow_candidate = 0x0400,  // priority = the target's - 1, but only when the
                                                    // particle's own (zeroed) priority is nonzero,
                                                    // so it always ends up 0
    ParticleEmitterFlagSpawnRoll        = 0x0800,  // spawn only when Mt19937RandMax2(wSpawnRollMax)
                                                    // < wSpawnRollThreshold
    ParticleEmitterFlagAnchorPosition   = 0x1000,  // spawn at anchor point bParam43 of the target's
                                                    // current frame
    ParticleEmitterFlagFixedPosition    = 0x2000,  // spawn at (sPosX, sPosY)
    ParticleEmitterFlagPriorityAbove    = 0x4000,  // particle priority = target's + 1
    ParticleEmitterFlagSkipTick         = 0x8000,  // skip this frame's tick; cleared every frame
} ParticleEmitterFlags;

// Node in the particle-emitter active/free lists (see below). ListNode
// must be the first member -- List_MoveToHead/List_Remove address a
// ParticleEmitter* directly as a ListNode*. Most spawn parameters remain
// undecoded.
typedef struct ParticleEmitter {
    ListNode node;           // 0x00
    struct Object *pTarget;  // 0x08, object the emitter follows
    const ParticleSprite *pSprite;  // 0x0C
    s32 nVelX;               // 0x10, mode 8 direction vector
    s32 nVelY;               // 0x14
    u8 pad_18[0x02];         // -> 0x1A
    s16 sPosX;               // 0x1A, spawn position with ParticleEmitterFlagFixedPosition
    u8 pad_1C[0x02];         // -> 0x1E
    s16 sPosY;               // 0x1E
    u32 dwSpeed;             // 0x20
    const u8 *pAnimData;     // 0x24
    u16 wSpawnPeriod;        // 0x28, ticks between spawn attempts minus one
    u16 wLifetimeBase;       // 0x2A
    u16 wLifetimeRange;      // 0x2C, 0 = random 1-5, 5 = exactly 5, else random wLifetimeRange-5
    u16 wFlags;              // 0x2E
    u16 wSpread;             // 0x30, position jitter in pixels
    u16 wSpawnTimer;         // 0x32
    u16 wTileAllocId;        // 0x34
    u16 wDuration;           // 0x36
    u16 wParam38;            // 0x38
    u16 wSpawnRollMax;       // 0x3A
    u16 wSpawnRollThreshold; // 0x3C
    u8 bResourceCacheSlot;   // 0x3E, index into g_aResourceCache
    u8 bMode;                // 0x3F
    u8 bDirection;           // 0x40
    u8 bSpawnsPerPeriod;     // 0x41
    u8 bOamSize;             // 0x42
    u8 bParam43;             // 0x43
    s8 abVelRange[4];        // 0x44
    u8 bAnimTicks;           // 0x48
    u8 bParalysisEffectFlag_candidate;  // 0x49, set on the emitter spawned by SpawnParalysisEffect
    u8 pad_4A[0x02];        // -> 0x4C
} ParticleEmitter;

// ParticleEmitter.bMode / Particle.bMode: how a particle's velocity is chosen.
typedef enum {
    ParticleModeStill           = 0,  // no velocity; bParam follows the target's facing
    ParticleModeDirectional     = 1,  // away from the emitter's bDirection at dwSpeed
    ParticleModeRandomDirection = 2,  // a random one of 8 directions at dwSpeed
    ParticleModeFixedDirection  = 3,  // along bDirection at dwSpeed; particles become mode 1
    ParticleModeStillAlt        = 4,  // as 0; also spawns along a segment between two anchors
    ParticleModeRandomDirectionAlt = 5,  // as 2; also spawns along a segment between two anchors
    ParticleModeRandomVelocity  = 6,  // x/y velocity drawn from abVelRange
    ParticleModeRandomSpeed     = 7,  // along bDirection at a random speed; particles become mode 1
    ParticleModeRandomSpeedVector = 8,  // along (nVelX, nVelY) at a random speed
} ParticleMode;

// One live particle, 0x48 bytes; the free/active lists are g_pParticleFreeListHead and
// g_pParticleActiveListHead, and at most 0x3F are live at once.
typedef struct Particle {
    ListNode node;           // 0x00
    const ParticleSprite *pSprite;  // 0x08
    s32 nX;                  // 0x0C, 16.16
    s32 nY;                  // 0x10
    s32 nDrawX;              // 0x14, 16.16; the integer part is at 0x16
    s32 nDrawY;              // 0x18
    s32 nVelX;               // 0x1C
    s32 nVelY;               // 0x20
    OamEntry oam;            // 0x24
    s32 dwSpeed;             // 0x2C
    s32 dwInitialSpeed;      // 0x30
    const u8 *pAnimData;     // 0x34
    s16 sLife;               // 0x38
    u16 wFlags;              // 0x3A, the emitter's wFlags when spawned
    u16 wTileAllocId;        // 0x3C
    u16 wFrameCounter;       // 0x3E
    u8 bAnimTicks;           // 0x40
    s8 bFrame;               // 0x41
    u8 bMode;                // 0x42
    u8 bParam;               // 0x43, direction index
    u8 bUnk44;               // 0x44
    u8 pad_45;
    u16 wParam46;            // 0x46
} Particle;

// See docs/formats/battle_scripts.md's TickParticleEmitters note --
// TickParticleEmitters walks g_pParticleEmitterActiveListHead each frame.
extern ListNode *g_pParticleEmitterFreeListHead;    // 0x030051B0
extern u16 g_wActiveParticleEmitterCount;           // 0x030051A0
extern ListNode *g_pParticleEmitterActiveListHead;  // 0x03005198
extern u16 g_wActiveParticleCount;                  // 0x0300519C
extern u16 g_wParticleHighWaterMark;                // 0x0300519E
extern ListNode *g_pParticleFreeListHead;           // 0x030051AC
extern ListNode *g_pParticleActiveListHead;         // 0x030051CC
extern const s32 g_aDirection4Vectors[4][2];        // 0x0804BDBC
extern const s32 g_aDirection8Vectors[8][2];        // 0x0804BDDC
extern const u8 g_abOppositeDirection8[8];          // 0x08068BFC
extern const u8 g_abOppositeDirection4[4];          // 0x08068C04
extern s32 FixedMultiply(s32 a, s32 b);  // 16.16 multiply that keeps 10 bits of each operand

// Takes a particle from the free list, zeroed, and counts it.
static inline Particle *AllocParticle(void)
{
    Particle *particle;

    particle = AllocObjectFromFreeList(&g_pParticleFreeListHead, &g_pParticleActiveListHead,
                                       sizeof(Particle));
    g_wActiveParticleCount++;
    if (g_wActiveParticleCount > g_wParticleHighWaterMark)
        g_wParticleHighWaterMark = g_wActiveParticleCount;
    return particle;
}

// Returns a particle to the free list.
static inline void FreeParticle(Particle *particle)
{
    List_MoveToHead(&g_pParticleFreeListHead, &g_pParticleActiveListHead, &particle->node);
    g_wActiveParticleCount--;
}  // 16.16 multiply keeping 10 bits of each operand
extern u8 g_bParticleSpawnBlocked;                  // 0x030051D0
extern void TickParticleEmitters(void);
extern u16 g_wParticleEmitterHighWaterMark;         // 0x030051A2
extern ParticleGfxEntry *g_apParticleGfxPools[];    // 0x030051D8

extern ParticleEmitter *g_pMenuCursorEmitter;       // 0x030028C0

extern void CreateMenuCursorEmitter(struct Object *pCursor);
extern void TickParticleEmitter(ParticleEmitter *emitter);
extern void SpawnParticle(ParticleEmitter *emitter);
extern ParticleEmitter *AllocParticleEmitter(const ObjPalette *pPalette, u32 poolIndex, u32 entryIndex);

extern void DecrementResourceCacheRefcount(s32 slotIndex);
extern void ReleaseParticleEmitter_candidate(ParticleEmitter *emitter);

// Drops the emitter's resource-cache reference and returns it to the free list. The ROM
// inlines this in the emitter tick and in ReleaseParticleEmitter_candidate.
static inline void FreeParticleEmitter(ParticleEmitter *emitter)
{
    DecrementResourceCacheRefcount(emitter->bResourceCacheSlot);
    List_MoveToHead(&g_pParticleEmitterFreeListHead, &g_pParticleEmitterActiveListHead,
                    &emitter->node);
    g_wActiveParticleEmitterCount--;
}
