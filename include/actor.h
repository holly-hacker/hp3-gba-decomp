#pragma once

#include "types.h"
#include "direction.h"
#include "hw/mem.h"
#include "graphics/graphics.h"
#include "graphics/oam.h"

// See docs/formats/graphics.md.

// Actor.dwFlags. Bits confirmed by usage in TickActor/TickActorList and
// their callees (see docs/formats/graphics.md); several names are inferred
// from a single read/write site rather than exhaustively proven.
typedef enum {
    ActorFlagVisible                  = 0x1,        // required (with HasSpriteCells clear)
                                                       // to queue onto the OAM/priority-sort pass
    ActorFlagPendingDestroy           = 0x2,        // TickActor defers to FreeActor instead of ticking
    ActorFlagWantsCollisionCheck      = 0x4,        // queues the actor for the collision-check pass
    ActorFlagHasTickLogic             = 0x8,        // opts into the full movement/pfnTick path
    ActorFlagHasAnimation             = 0x10,       // TickActorAnimation runs
    ActorFlagAnimFrameLoaded          = 0x80,       // new tiles pending CommitQueuedActorTileUpdates
    ActorFlagSkipSpriteFrameUpdate    = 0x100,      // TickActorList skips UpdateActorSpriteFrame
    ActorFlagTerrainCollisionA_candidate = 0x200,   // with ActorFlagTerrainCollisionB_candidate: either
                                                       // bit makes CheckActorTerrainCollision resolve
                                                       // the actor against the room terrain
    ActorFlagOnscreen                 = 0x400,      // set by UpdateActorOnscreenFlags
    ActorFlagTickHandlerSuspendsMovement = 0x800,   // pfnTick asked to skip the rest of this tick
    ActorFlagSpecialMoveTrigger       = 0x8000,
    ActorFlagTerrainCollisionB_candidate = 0x10000, // see ActorFlagTerrainCollisionA_candidate
    ActorFlagHasSpriteCells           = 0x20000,    // distinguishes the sprite-frame-update queue
                                                       // from the OAM/priority-sort queue
    ActorFlagActionAnimDone           = 0x40000,    // set by TickActorAnimation on a non-looping
                                                       // animation's last frame
    ActorFlagFourWayDirections_candidate = 0x100000, // GetDirectionToTarget returns a Direction4
    ActorFlagHasPaletteSlot           = 0x200000,   // AttachActorPalette bound a palette cache slot;
                                                       // ReleaseActorPalette clears it
    ActorFlagOnscreenForTileAlloc     = 0x400000,   // mirrors ActorFlagOnscreen (set/cleared
                                                       // together by UpdateActorOnscreenFlags)
    ActorFlagRoomRecordBound          = 0x800000,   // FreeActor clears the actor's room record
    ActorFlagNoPushTrigger_candidate  = 0x1000000,  // ApplyTerrainTypeEffect does not start a push while set
    ActorFlagSkipTerrainOnce_candidate = 0x2000000, // CheckActorTerrainCollision skips the terrain
                                                       // pass and clears it
    ActorFlagTerrainDrawLayer         = 0x4000000,  // the terrain pass sets oam.priority from the
                                                       // room's collision layer under the actor
    ActorFlagRoomScriptYield          = 0x8000000,  // set by a room script that yielded on this actor
    ActorFlagAnimPaused               = 0x10000000, // TickActorAnimation's frame counter freezes
    ActorFlagKeepPaletteSlot          = 0x20000000, // TickActor skips BindActorPendingPalette/ReleaseActorPalette
    ActorFlagExtraOamPass             = 0x80000000, // TickActorList's extra UpdateActorOamCells pass
} ActorFlags;

// Actor.bDrawFlags. With neither tile-sharing bit set, the actor owns
// its VRAM tiles; otherwise they are refcounted in its actor pool aux record
// (see ReleaseActorOffscreenVramTiles).
typedef enum {
    ActorDrawFlagShareTiles      = 0x1,   // one shared allocation, refcount index 0
    ActorDrawFlagShareFrameTiles = 0x2,   // shared per animation frame, refcount index
                                            // bAnimFrameIndex_candidate
    ActorDrawFlagFollowBelow     = 0x4,   // FollowOwnerActor: 1 pixel below the owner
    ActorDrawFlagFollowAbove     = 0x8,   // FollowOwnerActor: 1 pixel above the owner
    ActorDrawFlagPostActionFlash = 0x10,  // see docs/formats/battle_scripts.md; queues the
                                            // actor's OAM entries with SubmitOamAttrsNudged
    ActorDrawFlagBlink           = 0x20,  // WriteActorOamCells hides the entries on alternate
                                            // vblanks. UpdateActorOamCells's own entries are
                                            // queued into the slot it just hid, so they stay visible
    ActorDrawFlagVariantSlots    = 0x40,  // draw from aVariantSlots, which then own their
                                            // tile allocations (see EnableActorVariantSlots)
    ActorDrawFlagExtraOamPass    = 0x80,  // set while TickActorList's extra pass draws it
} ActorDrawFlags;

// Signed sprite extents in pixels from the actor's position, set from the
// current animation frame by LoadActorAnimFrameBounds. UpdateActorOnscreenFlags
// copies both words together before unpacking them.
typedef union ActorSpriteBounds {
    struct {
        u32 packedX;
        u32 packedY;
    } words;
    struct {
        s16 wLeft;
        s16 wRight;
        s16 wTop;
        s16 wBottom;
    } edges;
} ActorSpriteBounds;

// One of Actor's two collision-box slots, tested by CheckActorCollisions.
// dwPackedOffsets is 4 signed bytes: left (byte 0), right (1), top (2) and
// bottom (3) edge offsets from the integer part of posPrev (+0x36/+0x3A).
// Actor.oam.hFlip/vFlip mirror an axis: its edges become position minus the
// opposite offset. GetActorCollisionBoxRect resolves a slot to an ActorRect;
// CheckActorCollisions does the same math inline. bState is compared == 1 to
// take part in the pairwise overlap test; other values are unconfirmed.
typedef struct ActorCollisionBox {
    union {
        u32 dwPackedOffsets;
        struct {
            s8 bLeft;
            s8 bRight;
            s8 bTop;
            s8 bBottom;
        } edges;
    } offsets;            // 0x00
    union {
        u32 dwWord;
        u8 bState;
    } state;              // 0x04
} ActorCollisionBox;

// A collision box resolved to pixel edges; see GetActorCollisionBoxRect.
typedef struct ActorRect {
    s16 left;
    s16 right;
    s16 top;
    s16 bottom;
} ActorRect;

// Header of an ActorAssetRecord.pFrameData block; see docs/formats/graphics.md.
// Each awFrameOffsets entry is a byte offset from awFrameOffsets itself to
// that frame's ActorFrameDesc.
typedef struct ActorFrameData {
    u8 unk_0[2];
    s8 abTerrainBox[4];     // 0x02, left/right/top/bottom; see Actor.bTerrainBoxLeft
    u16 wFrameCount;        // 0x06
    u8 unk_8[2];            // -> 0x0A
    u8 bFrameHeaderExtra;   // 0x0A, count of extra u16s after each ActorFrameDesc
    u8 bFramePartCount;     // 0x0B, count of 6-byte collision boxes after those u16s: s8
                             // left/right/top/bottom, then a state byte and a byte the actor does not copy
    u16 awFrameOffsets[1];  // 0x0C, wFrameCount entries
} ActorFrameData;

typedef struct ActorFrameDesc {
    u8 bCellCount;          // 0x00, low 5 bits
    u8 unk_1;
    u8 bWidth;              // 0x02, pixels
    u8 bHeight;             // 0x03, pixels
    u16 wTileGfxOffset;     // 0x04, byte offset of this frame's tiles from pTileGfx
    s16 awOrigin[2];        // 0x06, x/y of the frame's top-left corner, relative to the actor.
                             // The frame's ActorFrameCells start at 0x0A, after
                             // ActorFrameData.bFramePartCount parts and bFrameHeaderExtra u16s
} ActorFrameDesc;

// One OAM cell of an animation frame, positioned relative to the actor. x/y are
// pixel offsets (doubled for a double-size affine actor); size/shape are the OAM
// attributes; tileOffset is the cell's first tile relative to the frame's tiles.
typedef struct ActorFrameCell {
    s32 x : 9;
    s32 y : 9;
    u32 size : 2;
    u32 shape : 2;
    u32 tileOffset : 10;
} __attribute__((packed)) ActorFrameCell;

// One selectable 16-byte sprite resource record. The first two pointers feed
// SetActorAssetRecord's tile/frame pipeline; pPalette is uploaded separately.
typedef struct ActorAssetRecord {
    void *pTileGfx;
    void *pFrameData;
    const ObjPalette *pPalette;
    u8 bAnimFrameDelay;
} ActorAssetRecord;

// The tile and frame half of an ActorAssetRecord, for a sprite whose palette
// is loaded separately. It is passed where an ActorAssetRecord is expected;
// the animation code reads only these two fields.
typedef struct ActorGfxRecord {
    void *pTileGfx;
    void *pFrameData;
} ActorGfxRecord;

extern const ActorAssetRecord g_apPortraitTable[72];  // US 0x0804C61C
extern const ActorAssetRecord g_aHelpSpriteAssets[22];  // US 0x08069AB8
extern const void *const g_apHelpSpritePalettes[22];    // US 0x08069C18

// ActorVariantSlot.bFrameFlags.
typedef enum {
    ActorVariantSlotFlagBlink          = 0x1,  // entries are hidden in the second half of the
                                                 // OAM shadow buffer, so the slot shows on
                                                 // alternate vblanks
    ActorVariantSlotFlagBounds         = 0x2,  // LoadVariantSlotFrameBounds takes the actor's terrain box,
                                                 // sprite bounds and collision boxes from slot 0
    ActorVariantSlotFlagPrevFrameWrap  = 0x4,  // draw the frame before bLastAnimFrameValue,
                                                 // wrapping to the last frame
    ActorVariantSlotFlagPrevFrameClamp = 0x8,  // draw the frame before bLastAnimFrameValue,
                                                 // clamping to frame 0
} ActorVariantSlotFlags;

// One 12-byte sprite-variant slot embedded in Actor: the tile allocation
// for the slot's current variant and the variant tables it selects from.
// While Actor.bDrawFlags has ActorDrawFlagVariantSlots, UpdateActorOamCells
// draws the actor from its variant slots (those with non-null tables) instead of
// pAnimTable; see src/actor/actor_variant_slots.c.
// Code indexes slots by this stride, but only slot 0 exists in the
// 0x128-byte Actor and every caller loops over exactly one slot.
typedef struct ActorVariantSlot {
    u8 bFrameFlags;         // 0x00, ActorVariantSlotFlags
    u8 bPaletteBank;        // 0x01, OBJ palette bank written to the slot's OAM entries
    u8 bDrawOrder;          // 0x02, UpdateActorOamCells queues slots from 7 down to 0;
                             // values above 7 are never drawn
    u8 pad_3[0x01];         // -> 0x04
    u16 wVramPixelCount;    // 0x04, size of wVramTileAllocId in pixels (0 = none)
    u16 wVramTileAllocId;   // 0x06, 0xFFFF = none
    ActorAssetRecord **pSpriteVariantTables;  // 0x08, outer table selected by
                             // Actor.bSpriteVariantTableIndex
} ActorVariantSlot;

// Actor's animation state at Actor+0xD8. The animation functions reach it
// through one pointer to the whole block.
typedef struct ActorAnimState {
    u8 bAnimFrameCounter;   // 0x00, frames-remaining countdown reloaded from
                             // bAnimFrameDelay each time it hits 0; see TickActorAnimation
    u8 bAnimFrameDelay;     // 0x01
    u8 bAnimFrameIndex_candidate;  // 0x02, the frame LoadActorAnimFrameBounds compares with
                             // bLastAnimFrameValue; 0xFF forces a reload. Selects the per-frame
                             // tile refcount in the actor pool's
                             // aux record when ActorDrawFlagShareTiles is clear; see
                             // ReleaseActorOffscreenVramTiles
    u8 bLastAnimFrameValue; // 0x03, current cycling frame index for non-scripted (cursor-less)
                             // animations; see TickActorAnimation
    union {
        u8 bEnemyAttackPhase_candidate;  // TickFighterAttackAnimState_candidate's own
                             // multi-step sentinel: 0xff idle, 0/2/3/4 successive phases
                             // -- real compares it unsigned against 0xff, not as a signed -1
        u16 wOamStripCount;  // copies of oam UpdateActorOamCells queues, each 32 pixels
                             // right of the last, while bForceOnscreen_candidate is set
    } unk_DC;               // 0x04, agbcc rounds the union to 4 bytes (-> 0x08)
    ActorAssetRecord *pAnimTable;  // 0x08, set by SetActorAssetRecord; its pFrameData
                             // holds the animation frames -- see docs/formats/graphics.md
    u8 *pAnimFrameCursor;   // 0x0C
    u8 *pAnimFrameBase;     // 0x10
} ActorAnimState;

typedef union __attribute__((packed)) ActorScriptState {
    u16 wScriptPc;
    struct __attribute__((packed)) {
        u8 bAttackOutcomeState;
        u8 bScriptPageHigh_candidate;
    } bytes;
} ActorScriptState;

// Bytes 0x62-0x6D of an effect script actor. Read back each tick by
// ProcessActorFlagBehaviors; bBehaviorFlags selects which fields apply.
typedef struct __attribute__((packed)) ActorEffectState {
    u8 bEffectId;           // 0x62, index into g_apEffectScripts
    u8 abLocal[2];          // 0x63-0x64, script variables A and B; spawned children inherit
                             // each one plus 1
    u8 pad_65;
    u8 bBehaviorFlags;      // 0x66, EffectBehaviorFlags bitmask
    u8 abParams[5];         // 0x67-0x6B, meaning depends on the active behavior flags
    u8 bParam6C;            // 0x6C
    u8 bParam6D;            // 0x6D
} ActorEffectState;

// Actor 0x62-0x6D for a chest (room actor type 9), from its record; see
// SpawnChestActor.
typedef struct __attribute__((packed)) ActorChestState {
    u16 wRewardId;          // 0x62, see rewards.h
    u8 bKind;               // 0x64, 0-3
    u8 bOpened;             // 0x65, set once opening starts or when spawned already open
    u8 bUnchaining;         // 0x66, kind 1: set when spell effect 3 starts unchaining it
    u8 bUnk67;              // 0x67, cleared by the constructor
    union __attribute__((packed)) {
        u16 wPair;          // tested as a whole: zero means no pair
        struct __attribute__((packed)) {
            u8 bRespawnGroup;   // 0x68
            u8 bChain;          // 0x69
        } bytes;
    } pair;                 // 0x68, run instead of a reward above REWARD_ID_GOLD
} ActorChestState;

// General-purpose sprite/animation actor, 0x128 bytes (confirmed by
// ExitBattle's Folio Universitas/Help resume path, which memcpys a whole one
// into FightState.aSuspendedFighterActors_candidate -- see battle.h). Only
// the fields touched by UpdateBattle/TickPlayerActionState/ExitBattle are
// named; see those files' plate comments for the rest.
typedef struct Actor {
    ListNode node;          // 0x00, active/free actor-pool list link (see
                             // FreeActor/List_MoveToHead); pNext/pPrev
    u16 wActorType;       // 0x08, AllocActorOfType's type param; meaning is
                             // caller-defined. In the battle subsystem, values are
                             // a small per-kind index (player fighter 0-3, monster
                             // type id) -- see InitPlayerBattleActor/InitMonsterBattleActor
    u16 wCharacterId_candidate;  // 0x0A, party members' character id (compared against a script's character operand)
    ActorFlags dwFlags;    // 0x0C
    u8 bRoomTileCol_candidate;  // 0x10, SetRoomActorRecordPtr_candidate's column arg
    u8 bRoomTileRow_candidate;  // 0x11, SetRoomActorRecordPtr_candidate's row arg
    u8 bFacing;             // 0x12, direction/facing index; see SetActorFacing
    u8 pad_13[0x01];        // -> 0x14
    u16 wMoveDuration;      // 0x14
    u8 bDepthSortBias;      // 0x16, draw-order bias; see SortActorsByDepth
    u8 pad_17[0x0D];        // -> 0x24
    ParticleEmitter *pWindupParticleEmitter;  // 0x24, freed via
                             // ReleaseParticleEmitter_candidate and zeroed
                             // when nonzero (see ClearParalyzedFighter_candidate)
    u32 dwUnk_0x28;         // 0x28, set to 1 by InitPlayerBattleActor_candidate
    FixedPoint pos;         // 0x2C
    FixedPoint posPrev;     // 0x34, pending position: IntegrateActorVelocity sets it
                             // to pos plus velocity, and TickActorList copies it into pos
                             // after collisions. See docs/formats/battle_scripts.md's
                             // StartOrbitMotion/ApplyActorOrbitMotion writeup.
                             // SetActorPosition/SnapActorPosition also set this
                             // equal to pos (no interpolation pending after a teleport)
    FixedPoint vel;         // 0x3C
    FixedPoint accel;       // 0x44, added to vel each tick by IntegrateActorVelocity
    FixedPoint moveTarget;  // 0x4C, set by SetActorMoveTarget/StartActorMove
    union __attribute__((packed)) {
        // 0x54-0x5F, {angleX, angleY, velX, velY, radiusX, radiusY}; see
        // CopyOrbitParamsFromTable and docs/formats/battle_scripts.md
        u16 awOrbit[6];
        struct __attribute__((packed)) {
            u8 pad_54[0x04];        // -> 0x58
            s16 wUnk58;             // 0x58, scaled (>> 7) by DivinationTea's leaf drift
            u8 pad_5A[0x02];        // -> 0x5C
            u32 dwOrbitRadii;       // 0x5C, packed radiusX/radiusY; nonzero runs ApplyActorOrbitMotion
        } fields;
        struct __attribute__((packed)) {
            s16 wAngleX;            // 0x54, 8.8; the high byte indexes g_anSineTable
            u16 wAngleY;            // 0x56
            u16 wAngleVelX;         // 0x58
            u16 wAngleVelY;         // 0x5A
            s16 wRadiusX;           // 0x5C, pixels
            s16 wRadiusY;           // 0x5E
        } orbit;
    } orbitState;
    ActorScriptState scriptState;  // 0x60: actor script PC or battle outcome/page bytes
    // 0x62-0x6D is per-mode state: the actor view serves fighter and room
    // actors, the effect view serves battle-effect script actors
    // (see InterpretActorScript).
    union __attribute__((packed)) {
        struct __attribute__((packed)) {
            u16 wStagedDamage;      // 0x62
            u8 bRoomScriptArg64_candidate;  // 0x64, set by room script animation handlers
            u8 bFollowResumeDistance;  // 0x65, action state 0x12: resume following beyond this (pixels)
            u8 bRoomScriptArg66_candidate;  // 0x66, set by StartTileActorScript
            u8 bRoomActorArg67_candidate;  // 0x67
            u8 bFollowStopDistance; // 0x68, action state 0x12: stop following within this (pixels)
            u8 bRoomActorArg69_candidate;  // 0x69
            u8 bRoomScriptArg6A_candidate;  // 0x6A, set by StartActorAnimSequence
            u8 bRoomScriptArg6B_candidate;  // 0x6B, set by StartActorAnimSequence
            u8 bDelayedRespawnRow;  // 0x6C, delayed-chain script effect: RespawnRowAndRunChain_candidate
            u8 bDelayedChainRow;    // 0x6D   arguments once dwStateTimer runs out
        } actor;
        ActorEffectState effect;
        ActorChestState chest;
    } modeState;
    u8 pad_6E[0x0E];        // -> 0x7C
    u8 bUnk_0x7C;           // 0x7C, set to 5 by AllocActorOfType, zeroed by
                             // InitPlayerBattleActor_candidate
    u8 bTerrainType;        // 0x7D, collision type under the actor, set by RespondToTerrain
    u8 pad_7E[0x02];        // -> 0x80
    u32 dwStateTimer;       // 0x80
    u16 wUnk84;             // 0x84, zeroed by the type 6 room actor constructor
    u16 wUnk86;             // 0x86, zeroed alongside wMoveDuration
    u8 pad_88[0x02];        // -> 0x8a
    u16 wActionVariant;     // 0x8A
    u8 bRoomActorKind_candidate;  // 0x8C, set from the tile record by room actor constructors; 2 selects the second collision box
    u8 bActionState;        // 0x8D, the dispatch key
    u8 bPrevActionState_candidate;  // 0x8E, ExitDialogue restores the player to this action state
    u8 bActionSubState;     // 0x8F, secondary per-actor state; see SetActorActionSubState
    u8 bActionFlags;        // 0x90
    u8 bFighterIndex;       // 0x91
    u8 bReceivedRewardId;   // 0x92, player: reward id shown by the receive-item action (0x17)
    u8 pad_93[0x01];        // -> 0x94
    u8 bFlags_0x94_candidate;  // 0x94, bit 0x4 set by a room script; meaning unconfirmed
    u8 pad_95[0x03];        // -> 0x98
    void (*pfnTick)(struct Actor *actor);  // 0x98, per-frame tick (player fighters: TickPlayerActionState)
    void (*pfnDestructor)(struct Actor *actor);  // 0x9C, called by FreeActor if non-null
    struct Actor *pShadowActor;  // 0xA0, companion actor (main -> shadow); the
                                   // actor followed in action state 0x12
    struct Actor *pLinkedActor_candidate;  // 0xA4, one of three linked-actor slots
                                     // (see docs/formats/room_scripts.md); caller-defined
    struct Actor *pOwnerActor;   // 0xA8, back-link (shadow -> main)
    u16 wFlags_0xAC;        // 0xAC, bit 0x1 set by AllocDefaultActor; also read by
                             // CheckActorTerrainCollision as one of several "movement stopped"
                             // conditions. Not enough evidence yet for a real name.
    u8 pad_AE[0x01];        // -> 0xAF
    u8 bCollisionBoxCount;  // 0xAF, aCollisionBoxes in use: the animation frame's box count,
                             // or 1 or 2 from the room actor constructors
    ActorCollisionBox aCollisionBoxes[2];  // 0xB0, see CheckActorCollisions;
                             // slot 0 at 0xB0, slot 1 at 0xB8
    // 0xC0-0xC3: terrain bounding box, signed pixel offsets from the actor's
    // integer position, copied from the sprite record's ActorFrameData by
    // LoadActorAnimFrameBounds (the same box for every frame).
    // Terrain probes (GetUnblockedDirectionToTarget, GetActorTerrainBox) test pixels
    // at these edges.
    s8 bTerrainBoxLeft;     // 0xC0
    s8 bTerrainBoxRight;    // 0xC1
    s8 bTerrainBoxTop;      // 0xC2
    s8 bTerrainBoxBottom;   // 0xC3
    u8 pad_C4[0x04];        // -> 0xC8
    void (*apfnCollisionCallback[2])(struct Actor *self, struct Actor *other);
                             // 0xC8, called by CheckActorCollisions on an
                             // overlap of the matching-index box, per actor
    OamEntry oam;           // 0xD0, the actor's base OAM attributes. affineMode holds the
                             // affine-slot allocation state (see ReleaseActorAffineSlot/
                             // FreeActor); objMode is 1 for menu cursors; bpp8 is passed to
                             // FreeObjVramTileAllocation; tileNum is copied from
                             // wVramTileAllocId by CommitQueuedActorTileUpdates; priority is
                             // the draw layer (see SetActorDrawLayer/SortActorsByDepth/
                             // TickActorList); paletteNum is the g_aObjPaletteSlots slot (see
                             // AttachActorPalette/ReleaseActorPalette).
                             // UpdateActorOamCells fills in x/y each frame
    ActorAnimState anim;   // 0xD8
    s32 nAffineScaleX;      // 0xEC, 16.16 fixed-point affine scale X (0x10000 = 1.0x); see
                             // TickActorAffineEffect/SetActorAffineTransform/
                             // StartActorAffineScaleTween
    s32 nAffineScaleY;      // 0xF0
    s32 nAffineScaleVelX;   // 0xF4, per-tick delta TickActorAffineEffect adds to
                             // nAffineScaleX; set by StartActorAffineScaleTween to linearly
                             // tween to a target scale over N ticks
    s32 nAffineScaleVelY;   // 0xF8
    u16 wAffineAngle;       // 0xFC
    u8 bAffineEffectTimer;  // 0xFE, ticks remaining for the current scale tween; nonzero keeps
                             // TickActorAffineEffect running
    u8 bAffineMode;         // 0xFF, mirrors oam.affineMode
    ActorSpriteBounds spriteBounds;  // 0x100, signed X/Y extent pairs used for visibility
    const void *pPendingPalette;  // 0x108, ObjPalette to bind once onscreen; ReleaseActorPalette
                                   // saves the bound palette here while offscreen
    u32 dwPendingPaletteFlags;    // 0x10C, ObjPaletteSlotFlags of pPendingPalette
    u16 wVramPixelCount;    // 0x110, size of wVramTileAllocId in pixels (0 = none)
    u16 wVramTileAllocId;   // 0x112, VRAM tile allocation id passed to
                             // FreeObjVramTileAllocation (0xFFFF = none); set to 0xFFFF by
                             // ExitBattle when suspending a fighter for the Folio Universitas/
                             // Help resume path
    u8 bForceOnscreen_candidate;  // 0x114, value 1 prevents visibility flags being cleared
    u8 bDrawFlags;          // 0x115, ActorDrawFlags
    u8 bActorPoolAuxSlot;  // 0x116, index into g_pActorPoolAuxBuffer's 0x34-byte-stride
                             // records; see ReleaseActorOffscreenVramTiles
    u8 pad_117[0x01];       // -> 0x118
    ActorVariantSlot aVariantSlots[1];  // 0x118
    s8 bSpriteVariantTableIndex;  // 0x124, shared by every variant slot
    s8 bSpriteVariantIndex;       // 0x125
    u8 pad_126[0x02];       // -> 0x128
} Actor;

// wActorType values used by room/overworld actor spawners (room-tile
// constructor dispatch at g_apRoomActorConstructors, 0x0804C054). Several
// constructor slots (1-4, 6, 7, 13) forward a per-instance type value already
// stored in the room's own tile record instead of a fixed constant, so this
// list only covers the values actually hardcoded in code.
typedef enum {
    RoomActorType_Player           = 0,     // SpawnPlayerActor_candidate
    RoomActorType_ScriptedTrigger  = 5,     // sub-behavior picked by a separate per-instance kind field
    RoomActorType_Unk8             = 8,
    RoomActorType_Chest            = 9,     // SpawnChestActor
    RoomActorType_UnkA             = 0xA,
    RoomActorType_UnkB             = 0xB,
    RoomActorType_UnkC             = 0xC,
    RoomActorType_ScriptEffect     = 0xE,   // SpawnScriptEffectActor, e.g. delayed chain runs;
                                              // reuses the same value as BattleActorType_FighterSlot0
                                              // since room/overworld and battle never run concurrently
    RoomActorType_WanderingMonster = 0x10,  // SpawnWanderingMonsterActor; reuses
                                              // BattleActorType_FighterSlot0 + 2 for the same reason
} RoomActorType;

// wActorType values used by battle-mode actor spawners. See RoomActorType
// above for why these overlap with room/overworld values.
typedef enum {
    BattleActorType_FighterSlot0 = 0xE,   // InitializeBattle: + fighter slot index 0-6
    BattleActorType_MessageIcon  = 0x15,  // InitializeBattle: FighterSlot0 + 7
    BattleActorType_EffectScript = 0x17,  // CreateEffectScriptActor, spell/attack visual effect
} BattleActorType;

extern Actor *AllocActorOfType(s32 type);
extern Actor *AllocDefaultActor(void);
extern void FreeActor(Actor *actor);
extern u32 TickActiveActors(void);
extern s32 UpdateActorOnscreenFlags(Actor *actor);
extern void SetActorSpriteVariant(Actor *actor, s8 tableIndex, s8 variantIndex);
extern void GetActorVariantFrameSize(Actor *actor, u32 *dims, u8 slot);
extern void *GetActorVariantFrameTileGfx(Actor *actor, u8 slot);
extern u8 GetDirectionToTarget(u32 actorFlags, FixedPoint pos, FixedPoint target, s32 tolerance);
extern u8 GetUnblockedDirectionToTarget(Actor *actor, FixedPoint pos, FixedPoint target, s32 tolerance);
extern ActorRect GetActorCollisionBoxRect(Actor *actor, s32 boxIndex);
extern s32 DoActorsOverlap(Actor *a, Actor *b);  // tests collision box 0 of each
extern void ReleaseActorOffscreenVramTiles(Actor *actor);  // 0x08001300
extern void SetRoomActorRecordPtr_candidate(Actor *actor, u8 col, u8 row);
extern Actor *SpawnActor(u32 type, s32 x, s32 y, const ObjPalette *pPalette);
extern void SetActorPosition(Actor *actor, s32 x, s32 y);
extern void SnapActorPosition(Actor *actor, u32 x, u32 y);
extern void SetActorVelocity(Actor *actor, u32 velX, u32 velY);
extern void SetActorMoveTarget(Actor *actor, u32 x, u32 y);
extern void StartActorMove(Actor *actor, u32 x, u32 y, u16 mode);
extern void ReleaseActorAffineSlot(Actor *actor);
extern u32 GetActorAffineSlotId(OamEntry *oam);
extern void SetActorAffineSlotId(OamEntry *oam, u16 slot);
extern u32 AllocActorAffineSlot(Actor *actor);  // memoized: returns the slot already in oam if
                             // oam.affineMode is set (1 or 3), else calls AllocAffineSlot and
                             // stores the result
extern void SetActorAffineTransform(Actor *actor, u32 nScaleX, u32 nScaleY, s16 wAngle, u8 bMode);
// Double-size affine with both scales set to step 0..8 of a table: 0x666, then 0x2000 * step.
extern void SetActorScaleStep(Actor *actor, u32 step);
extern void StartActorAffineScaleTween(Actor *actor, u32 nTargetScaleX, u32 nTargetScaleY, s32 nFrames);  // ramps nAffineScaleX/Y to the target over nFrames ticks (0 = set immediately)
extern void SetActorFlippedX(Actor *actor, s32 flip);
// pAnimTable is the sprite record; the stream starts at command startCommand
// of pAnimData (see actor_anim.h).
extern void SetActorAnimData(Actor *actor, const void *pAnimTable, const void *pAnimData, u8 startCommand);
extern u32 TickActorList(ActiveActorListState *list, u8 mode);
extern void TickActor(Actor *actor, u32 mode);
extern s32 IsActorTickAllowed(void);
extern void CheckActorTerrainCollision(Actor *actor);
extern void TickActorMove(Actor *actor);
extern void TickActorAnimation(Actor *actor);
extern void TickActorAffineEffect(Actor *actor);  // steps the scale tween while bAffineEffectTimer runs
extern void IntegrateActorVelocity(Actor *actor);
extern u8 UpdateActorOamCells(Actor *actor);
// Queues the OAM cells of one frame of frameData, copying the other attributes
// from pTemplate and placing them relative to the screen position pos[0]/pos[1].
// cellFlags bit 0 hides the cells on alternate vblanks; bit 1 is set for
// TickActorList's extra OAM pass (see docs/memory-map/heap.md).
extern void WriteActorOamCells(ActorFrameData *frameData, u16 frame, u8 cellFlags, s32 *pos,
                                u16 tileBase, OamEntry *pTemplate, Actor *actor);
extern void UpdateActorSpriteFrame(Actor *actor, u32 mode);
extern void ApplyActorOrbitMotion(Actor *actor);
// Moves an actor to its pOwnerActor's pending position and draw layer.
extern void FollowOwnerActor(Actor *actor);
extern void CommitQueuedActorTileUpdates(void);  // run from vblank callbacks
extern void sub_08001690(Actor *actor, const void *pAssetRecord);
extern void SetActorAnimFrame(Actor *actor, u8 bFrameIndex);  // sets bLastAnimFrameValue, reloading cells if changed
extern void RunActorAnimCommands(Actor *actor);
extern void LoadActorAnimFrameBounds(Actor *actor);
extern void LoadVariantSlotFrameBounds(Actor *actor);
extern void SetActorActionState(Actor *actor, u8 state);
extern void SetActorFlags(Actor *actor, ActorFlags flags);
// Starts animation `animId` from the actor's animation table.
extern void SetActorAnimData_candidate(Actor *actor, u32 animId);
extern void SetActorActionSubState(Actor *actor, u8 state);
extern void SetActorDrawLayer(Actor *actor, u8 layer);
extern void SetActorAnimSubState_candidate(Actor *actor, u8 state);
// Clears the actor's queued move (Actor+0x3C..0x48).
extern void CancelActorMove_candidate(Actor *actor);
extern void SetActorAssetRecord(Actor *actor, const void *rec);
extern Actor *SpawnMenuIconActor(u32 slot, u32 arg1);  // allocs a type 0x13 actor and files it under slot

extern void sub_080039E8(Actor *actor);
extern void sub_080039F8(Actor *actor);
extern void sub_08003A0C(Actor *actor);
extern void sub_08003A44(Actor *actor, s32 a, s32 b, s32 c);
extern void sub_0801BCB0(void *linkedActor);
extern Actor *CreateEffectScriptActor(s32 effectId, s32 kind);  // 0x08018BE0
