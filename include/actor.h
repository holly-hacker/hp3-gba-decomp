#pragma once

#include "types.h"
#include "particles.h"
#include "oam.h"
#include "math.h"

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
    ActorFlagUnk2000                  = 0x2000,     // set by most room actor constructors; no reader
                                                       // found yet
    ActorFlagCollisionGroup_candidate = 0x4000,     // CheckActorCollisions skips a pair that both set it
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
    ActorFlagSixteenWayDirections     = 0x40000000, // GetDirectionVector reads bFacing as one of 16
                                                       // directions; takes precedence over
                                                       // ActorFlagFourWayDirections_candidate
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
        s8 bState;
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
    u8 bMaxFrameWidth;      // 0x00, pixels: the largest ActorFrameDesc.bWidth
    u8 bMaxFrameHeight;     // 0x01, pixels: the largest ActorFrameDesc.bHeight
    s8 abTerrainBox[4];     // 0x02, left/right/top/bottom; see Actor.bTerrainBoxLeft
    u16 wFrameCount;        // 0x06
    u16 wMaxFrameTileBytes; // 0x08, byte size of the largest frame's tiles (32 per 4bpp tile,
                             // 64 per 8bpp tile)
    u8 bAnchorCount;        // 0x0A, anchor points after each ActorFrameDesc, two s8 x/y
                             // offsets each; see GetActorFrameAnchor
    u8 bFramePartCount;     // 0x0B, count of 6-byte collision boxes after those u16s: s8
                             // left/right/top/bottom, then a state byte and a byte the actor does not copy
    u16 awFrameOffsets[1];  // 0x0C, wFrameCount entries
} ActorFrameData;

// How a frame's tiles are compressed, from its ActorFrameDesc.bCellCount bits 5-6; see
// GetFrameTileCodec. Each matches the type in the tiles' resource header.
typedef enum {
    ActorFrameTileCodecGammaLz = 0,  // resource type 6
    ActorFrameTileCodecRle     = 1,  // bit 5, resource type 3
    ActorFrameTileCodecLzRle   = 2,  // bit 6, resource type 7
} ActorFrameTileCodec;

typedef struct ActorFrameDesc {
    u8 bCellCount;          // 0x00, low 5 bits; bits 5-6 are the ActorFrameTileCodec of the
                             // frame's tiles
    u8 unk_1;
    u8 bWidth;              // 0x02, pixels
    u8 bHeight;             // 0x03, pixels
    u16 wTileGfxOffset;     // 0x04, byte offset of this frame's tiles from pTileGfx
    s16 awOrigin[2];        // 0x06, x/y of the frame's top-left corner, relative to the actor.
                             // The frame's ActorFrameCells start at 0x0A, after
                             // ActorFrameData.bFramePartCount parts and bAnchorCount anchors
} ActorFrameDesc;

// Frame `frame`'s descriptor; ActorFrameData.awFrameOffsets holds byte offsets from the start
// of the array.
#define ACTOR_FRAME_DESC(frameData, frame) \
    ((ActorFrameDesc *)((u8 *)(frameData)->awFrameOffsets + (frameData)->awFrameOffsets[frame]))

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
    ActorFrameData *pFrameData;
    const ObjPalette *pPalette;
    u8 bAnimFrameDelay;
} ActorAssetRecord;

// The tile and frame half of an ActorAssetRecord, for a sprite whose palette
// is loaded separately. It is passed where an ActorAssetRecord is expected;
// the animation code reads only these two fields.
typedef struct ActorGfxRecord {
    void *pTileGfx;
    ActorFrameData *pFrameData;
} ActorGfxRecord;

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
    u16 wDoorDestinationRoom;  // room actor types 2 and 13
    u16 wFlameOutTicks;        // flame pillars: ticks the flame stays out
    struct __attribute__((packed)) {
        u8 bAttackOutcomeState;
        u8 bScriptPageHigh_candidate;
    } bytes;
} ActorScriptState;

// ActorEffectState.bBehaviorFlags: per-tick effects ProcessActorFlagBehaviors runs.
typedef enum {
    EffectBehaviorAffineWobble = 0x02,  // steps the affine rotation by abParams[2] and adds
                                        // abParams[0]/[1] to the scale
    EffectBehaviorAlphaFadeOut = 0x04,  // blends from abLocal[1]/16 down, one step per tick
    EffectBehaviorShrinkOrbit  = 0x08,  // every bParam6C ticks, shrinks the orbit radii by
                                        // abParams[0]/[1]
    EffectBehaviorGrowWindow   = 0x10,  // grows window 0's rectangle each tick
    EffectBehaviorPlaySound    = 0x40,  // plays sound abLocal[1] each tick
    EffectBehaviorAlphaFadeIn  = 0x80,  // blends up one step every bParam6C + 1 ticks until
                                        // abLocal[1] reaches abParams[4], then clears itself
} EffectBehaviorFlags;

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

// An actor's orbit around its position, run by ApplyActorOrbitMotion: X follows
// the cosine and Y the sine of its own angle, scaled by its radius.
typedef struct ActorOrbit {
    s16 wAngleX;            // 0x00, 8.8 in 256ths of a turn; the high byte indexes g_anSineTable
    u16 wAngleY;            // 0x02
    s16 wAngleVelX;         // 0x04, added to the angle each tick
    s16 wAngleVelY;         // 0x06
    s16 wRadiusX;           // 0x08, pixels
    s16 wRadiusY;           // 0x0A
} ActorOrbit;

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
    u8 bRoomTileCol_candidate;  // 0x10, SetRoomActorPtr's column arg
    u8 bRoomTileRow_candidate;  // 0x11, SetRoomActorPtr's row arg
    u8 bFacing;             // 0x12, direction/facing index; see SetActorFacing
    u8 pad_13[0x01];        // -> 0x14
    u16 wMoveDuration;      // 0x14
    u8 bDepthSortBias;      // 0x16, draw-order bias; see SortActorsByDepth
    u8 pad_17[0x01];        // -> 0x18
    u8 bRespawnRow;         // 0x18, RespawnGroupAndRunChain arguments for action
    u8 bChainRow;           // 0x19   state 0x14 and trigger actors. bRespawnRow also holds
                             // the animation StartNpcScriptAnimation plays
    u8 bPauseRange;         // 0x1A, pixels; HandlePausingActorTouch pauses the actor
                             // when the player comes this close
    u8 bResumeActionState;  // 0x1B, action state to return to after a state 6 pause
    u16 wPauseDuration;     // 0x1C, ticks a state 6 pause lasts
    u16 wPauseTimer;        // 0x1E, counted down in action state 6
    u8 pad_20[0x04];        // -> 0x24
    ParticleEmitter *pWindupParticleEmitter;  // 0x24, freed via
                             // ReleaseParticleEmitter and zeroed
                             // when nonzero (see ClearParalyzedFighter_candidate)
    s32 nMoveSpeed;         // 0x28, 16.16 pixels per tick; see SetActorVelocityFromFacing
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
    union {
        ActorOrbit orbit;           // 0x54; see docs/formats/battle_scripts.md
        struct {
            u8 pad_54[0x08];        // -> 0x5C
            u32 dwOrbitRadii;       // 0x5C, both radii at once; nonzero runs ApplyActorOrbitMotion
        } radii;
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
            u8 bDelayedRespawnRow;  // 0x6C, delayed-chain script effect: RespawnGroupAndRunChain
            u8 bDelayedChainRow;    // 0x6D   arguments once dwStateTimer runs out
        } actor;
        struct __attribute__((packed)) {
            u8 pad_62[0x04];
            u16 wFocusX;            // 0x66, pixels the camera cuts away to
            u16 wFocusY;            // 0x68
            u8 bPlayerViewTransition;  // 0x6A, screen transition leaving and returning to the player
            u8 bFocusViewTransition;   // 0x6B, screen transition entering and leaving the focus
            u8 bRespawnRow;         // 0x6C, RespawnGroupAndRunChain arguments run at the focus
            u8 bChainRow;           // 0x6D
        } cutaway;                  // camera cutaway script effect; see TickCameraCutawayActor
        struct __attribute__((packed)) {
            union __attribute__((packed)) {
                u16 wPair;          // tested as a whole: zero runs nothing
                struct __attribute__((packed)) {
                    u8 bRespawnRow;
                    u8 bChainRow;
                } rows;
            } finish;               // 0x62, RespawnGroupAndRunChain arguments run when a
                                    // walk-once route ends
            u8 bRoute;              // 0x64, route walked by action states 7-13; see
                                    // docs/formats/rooms.md's waypoint routes
            u8 bWaypoint;           // 0x65, next waypoint
            u8 pad_66[0x03];
            u8 bForward;            // 0x69, ping-pong walk direction: nonzero toward the last waypoint
        } route;
        struct __attribute__((packed)) {
            u16 wTargetY;           // 0x62, pixels; the X is scriptState.wScriptPc
            union {
                u32 dwWord;         // bits 8-23 are tested as a whole: zero runs nothing
                struct {
                    u8 bFacing;
                    u8 bRespawnRow;     // RespawnGroupAndRunChain arguments run on arrival
                    u8 bChainRow;
                } bytes;
            } args;                 // 0x64
        } scriptWalk;               // action state 15; see RoomScriptOpStartTileActorScript
        struct __attribute__((packed)) {
            u8 pad_62[0x06];
            s32 nCurve;             // 0x68, 100000 * height / width^2 of the parabola
            u16 wApexX;             // 0x6C, pixels
        } arc;                      // action state 0x10; see also wArcEndX
        struct __attribute__((packed)) {
            u8 abExitParams[2];     // 0x62, copied to g_abRoomScriptExitParams_candidate
            u8 pad_64;
            u8 bRequireAPress;      // 0x65
            u8 bChain;              // 0x66, runs instead of leaving when nonzero
        } door;                     // room actor types 2 and 13; see scriptState.wDoorDestinationRoom
        struct __attribute__((packed)) {
            u16 wLitTicks;          // 0x62, ticks the flame burns
            union __attribute__((packed)) {
                u16 wPair;          // tested as a whole: zero runs nothing
                struct __attribute__((packed)) {
                    u8 bRespawnRow;
                    u8 bChainRow;
                } rows;
            } touch;                // 0x64, RespawnGroupAndRunChain arguments run when
                                    // the player touches the flame
        } flamePillar;              // room actor type 11; see TickFlamePillarActor
        u8 bPropBlocksPlayer_candidate;  // 0x62, RoomActorType_ScriptedTrigger: see
                                         // HandlePlayerPropCollision
        ActorEffectState effect;
        ActorChestState chest;
    } modeState;
    u16 wArcEndX;           // 0x6E, action state 0x10: where the Spongify jump lands (pixels)
    u16 wArcApexY;          // 0x70
    u8 pad_72[0x02];        // -> 0x74
    u32 dwArcRightward;     // 0x74
    union __attribute__((packed)) {
        u16 wPair;          // tested as a whole: zero runs nothing
        struct __attribute__((packed)) {
            u8 bRespawnRow;
            u8 bChainRow;
        } rows;
    } padFinish;            // 0x78, RespawnGroupAndRunChain arguments run when a
                            // Spongify pad move ends
    u8 bPadFinalFacing;     // 0x7A, action state 0x11
    u8 pad_7B[0x01];        // -> 0x7C
    u8 bUnk_0x7C;           // 0x7C, set to 5 by AllocActorOfType, zeroed by
                             // InitPlayerBattleActor_candidate
    u8 bTerrainType;        // 0x7D, collision type under the actor, set by RespondToTerrain
    u8 pad_7E[0x02];        // -> 0x80
    u32 dwStateTimer;       // 0x80
    union __attribute__((packed)) {
        s16 nFlightTicks;       // field spell effects: ticks of flight left, from 45; see
                                 // TickDiffindoEffect
        u16 wInteractCooldown;  // NPCs: ticks until they can be talked to again; see
                                 // HandleNpcActorTouch
    } timer84;              // 0x84
    u16 wTimedMoveTicks;    // 0x86, ticks left in a StartActorTimedMove move
    u8 pad_88[0x02];        // -> 0x8a
    u16 wActionVariant;     // 0x8A
    u8 bRoomActorKind_candidate;  // 0x8C, set from the tile record by room actor constructors; 2 selects the second collision box
    u8 bActionState;        // 0x8D, the dispatch key
    u8 bPrevActionState_candidate;  // 0x8E, ExitDialog restores the player to this action state
    u8 bActionSubState;     // 0x8F, secondary per-actor state; see SetActorActionSubState
    u8 bActionFlags;        // 0x90
    u8 bFighterIndex;       // 0x91, wandering monsters: random-encounter id
    u8 bReceivedRewardId;   // 0x92, player: reward id shown by the receive-item action (0x17);
                             // wandering monsters: encounter kind
    u8 bEncounterVariant;   // 0x93, wandering monsters: random-encounter variant
    u8 bFlags_0x94_candidate;  // 0x94, bit 0x4 set by a room script; meaning unconfirmed.
                                // NPCs: 0x1 talked to (until the cooldown ends), 0x2 not
                                // interactable, 0x4 keeps the sprite frame TickNpcActor would set
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
    s8 bAnimSet_candidate;  // 0x117, set by SetActorAnimSet_candidate; GetActorVariantAnchorPosition
                             // selects the slot's variant table with it. Nothing else uses it
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
    RoomActorType_Player           = 0,     // SpawnPlayerActor
    RoomActorType_ScriptedTrigger  = 5,     // sub-behavior picked by a separate per-instance kind field
    RoomActorType_PushResetButton  = 8,     // SpawnPushResetButtonActor
    RoomActorType_Chest            = 9,     // SpawnChestActor
    RoomActorType_UnkA             = 0xA,
    RoomActorType_UnkB             = 0xB,
    RoomActorType_UnkC             = 0xC,
    RoomActorType_ScriptEffect     = 0xE,   // SpawnScriptEffectActor, e.g. delayed chain runs;
                                              // reuses the same value as BattleActorType_FighterSlot0
                                              // since room/overworld and battle never run concurrently
    RoomActorType_FieldSpellEffect = 0xF,   // SpawnFieldSpellEffect; wCharacterId_candidate is the FieldSpell
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

// wActorType values of actors spawned in any game mode. ActorType_Text shares
// its value with BattleActorType_FighterSlot0 + 6.
typedef enum {
    ActorType_Text = 0x14,  // SpawnTextActor and the other text actor spawners
} ActorType;

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
    struct Actor *apTileUpdateQueue[0x69];  // 0x0C, actors whose OAM update returned 2
    u8 bExtraOamPassEnabled_candidate;   // 0x1B0, nonzero enables TickActorList's extra pass;
                                         // bits 0-1 are the OAM priority of the vertically
                                         // mirrored, alternate-vblank copies it draws
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
    u32 dwAllocTick;         // 0x30, g_dwTickCount when the ShareTiles allocation was made
} ActorPoolAuxRecord;
extern ActorPoolAuxRecord *g_pActorPoolAuxBuffer;
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
// IWRAM copies of the ARM actor passes, installed by InitActorPool.
extern void SortActorsByDepthIwram(struct Actor **actors, u32 count);
extern void CheckActorCollisionsIwram(s32 count, struct Actor **actors);

void FreeAllActors(ListNode **activeListHead);

void InitActorPool(void);

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
extern Actor *SpawnActor(u32 type, s32 x, s32 y, const ObjPalette *pPalette);
extern void SetActorPosition(Actor *actor, s32 x, s32 y);
extern void SnapActorPosition(Actor *actor, u32 x, u32 y);
extern void SetActorVelocity(Actor *actor, u32 velX, u32 velY);
extern void SetActorMoveTarget(Actor *actor, u32 x, u32 y);
extern void StartActorMove(Actor *actor, u32 x, u32 y, u16 mode);
extern void ReleaseActorAffineSlot(Actor *actor);
extern u32 AllocActorAffineSlot(Actor *actor);  // memoized: returns the slot already in oam if
                             // oam.affineMode is set (1 or 3), else calls AllocAffineSlot and
                             // stores the result
extern void SetActorAffineTransform(Actor *actor, u32 nScaleX, u32 nScaleY, s16 wAngle, u8 bMode);
extern void StartActorAffineScaleTween(Actor *actor, u32 nTargetScaleX, u32 nTargetScaleY, s32 nFrames);  // see actor_inline.h
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
extern void SetActorSprite(Actor *actor, const void *pRecord);  // an ActorAssetRecord
extern void SetActorAnimFrame(Actor *actor, u8 bFrameIndex);  // sets bLastAnimFrameValue, reloading cells if changed
extern void SetActorDepthSortBias(Actor *actor, u8 bias);
extern void RunActorAnimCommands(Actor *actor);
extern void LoadActorAnimFrameBounds(Actor *actor);
extern void LoadVariantSlotFrameBounds(Actor *actor);
extern void SetActorActionState(Actor *actor, u8 state);
extern void SetActorFlags(Actor *actor, ActorFlags flags);
extern void ClearActorFlags(Actor *actor, ActorFlags flags);
extern s32 ActorHasFlags(Actor *actor, ActorFlags flags);  // 1 when every bit of flags is set
extern void SetActorActionSubState(Actor *actor, u8 state);
extern void SetActorFacing(Actor *actor, u8 facing);  // raises bActionFlags bit 0x10 on a change
extern void SetActorDrawLayer(Actor *actor, u8 layer);
extern void SetActorPrevActionState(Actor *actor, u8 state);
// Clears the actor's queued move (Actor+0x3C..0x48).
extern void CancelActorMove_candidate(Actor *actor);
extern void SetActorAssetRecord(Actor *actor, const void *rec);

extern void AllocActorVramTiles(Actor *actor, ActorAssetRecord *record);
extern void SetActorAnimStream(Actor *actor, const void *pAnimData, u8 startCommand);
extern void SetActorAnimDataAtCommand(Actor *actor, const void *pAnimTable, const void *pAnimData,
                                      u8 startCommand);
// Velocity components mirrored on the axis the sprite is flipped on.
extern void SetActorLocalVelocityX(Actor *actor, s32 velX);
extern void SetActorLocalVelocityY(Actor *actor, s32 velY);
extern void SetActorAccelInDirection16(Actor *actor, u32 direction, s32 magnitude);
extern void SetActorVelocityFromFacing(Actor *actor);
extern void OffsetActorPosition(Actor *actor, s32 dx, s32 dy);
extern void SetActorMoveTargetWithDuration(Actor *actor, s32 x, s32 y, u16 duration);
// Anchor points: per-frame pixel offsets from the actor's position, such as
// where effects attach. Each returns 0 when the frame has no such anchor.
extern s32 GetActorFrameAnchor(Actor *actor, ActorFrameData *frameData, u32 index, IntPoint *out);
extern s32 GetActorAnchor(Actor *actor, u32 index, IntPoint *out);
extern s32 GetActorFlippedAnchor(Actor *actor, u32 index, IntPoint *out);
extern s32 GetActorAnchorPosition(Actor *actor, u32 index, FixedPoint *out);
extern s32 GetActorVariantAnchorPosition(Actor *actor, u8 slot, u8 index, FixedPoint *out);
extern void GetActorMaxFrameSize(Actor *actor, u32 *dims);
extern void GetActorFrameSize(Actor *actor, u32 *dims);
extern void *GetActorFrameTileGfx(Actor *actor);
extern void GetActorOamPosition(Actor *actor, IntPoint *out);
extern u8 GetDirectionToActor(Actor *actor, Actor *target);
extern u8 GetDirectionFromActor(Actor *actor, Actor *source);
extern void GetDirectionVector(FixedPoint *out, u32 actorFlags, u32 direction, s32 speed);
// Unit vectors in 16.16 fixed point, see src/actor/direction_vectors.c.
extern const s32 g_aDirection4Vectors[4][2];        // 0x0804BDBC
extern const s32 g_aDirection8Vectors[8][2];        // 0x0804BDDC
extern const s32 g_aDirection16Vectors[16][2];      // 0x0804BE1C
extern const s32 g_aDirection32Vectors[32][2];      // 0x0804BE9C
extern u8 FindActorsByType(u8 type, u8 characterId, Actor **out, u8 maxCount);
extern s32 ActorIsNullActorType(Actor *actor);
extern void SetActorAnimSet_candidate(Actor *actor, u8 animSet);
extern void UnsetActorHasAnimation(Actor *actor);

extern void StartActorTimedMove(Actor *actor, s32 x, s32 y, u16 ticks);
extern s32 TickActorTimedMove(Actor *actor);  // returns 1 on arrival
extern void SetActorFlippedY(Actor *actor, s32 flip);
extern s32 IsActorFlippedX(Actor *actor);
extern s32 IsActorFlippedY(Actor *actor);
extern void ClearActorOrbit(Actor *actor);
extern void ClearActorOrbitX(Actor *actor);
extern void ClearActorOrbitY(Actor *actor);
extern void CopyOrbitParamsFromTable(Actor *actor, const ActorOrbit *row);
extern void SetActorOrbitX(Actor *actor, s32 angle, s16 angleVel, s16 radius);
extern void SetActorOrbitY(Actor *actor, s32 angle, s16 angleVel, s16 radius);
extern void SetActorOrbitAngles(Actor *actor, s32 angleX, s32 angleY);
extern void SetActorOrbitAngleVels(Actor *actor, s16 angleVelX, s16 angleVelY);
extern void SetActorOrbitRadii(Actor *actor, s16 radiusX, s16 radiusY);
// Overworld action states (Actor.bActionState), dispatched by TickActorActionState.
extern void TickActorActionState(Actor *actor);
extern void TickActorWalkToTarget(Actor *actor);
extern void TickActorCastFieldSpell(Actor *actor);
extern void TickActorReceiveReward(Actor *actor);
// Sets the walk velocity for D-pad `direction`, following stairs and ice under the actor;
// returns the facing to show.
extern s8 ApplyTerrainToWalkVelocity(Actor *actor, s8 direction);
extern void TickPlayerControl(Actor *actor);
extern void TickActorTurnAround(Actor *actor);
extern void TickActorRespawnRow(Actor *actor);
extern void TickActorStopAndStand(Actor *actor);
extern void TickActorInDialog(Actor *actor);
extern s32 FaceActorTowardMoveTarget(Actor *actor);
extern void TickActorWalkRouteLoop(Actor *actor);
extern void TickActorWalkRoutePingPong(Actor *actor);
extern void TickActorWalkRouteOnce(Actor *actor);
extern void TickActorSpongifyJump(Actor *actor);
extern void TickActorPadWalk(Actor *actor);
extern void TickActorScriptWalk(Actor *actor);
extern void TickActorFollow(Actor *actor);
extern void TickActorFollowSimple(Actor *actor);
extern const u8 g_abTurnAroundDirection[8];
extern const u8 g_abTurnAroundDirection4[4];
extern const ActorAssetRecord g_CoinIconAsset;
extern const u8 g_sSpace[];
extern ActorGfxRecord g_ReceivedItemGfx;

extern u16 GetAnimMaxFrameTileBytes(ActorAnimState *anim);
extern void GetSpriteMaxFrameSize(const ActorAssetRecord *record, u32 *dims);
extern void GetSpriteFrameSize(const ActorAssetRecord *record, u32 *dims, u8 frame);
extern u16 GetAnimFrameCount(ActorAnimState *anim);
extern u32 GetFrameTileCodec(ActorFrameData *frameData, u16 frame);
extern u8 GetFrameCellCount(ActorFrameDesc *frameDesc);
extern void GetOamShapeSizeDims(u32 shape, u32 size, s32 *dims);
extern const OamShapeSize g_aOamShapeSizes[3][4];

