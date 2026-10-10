#pragma once

#include "types.h"
#include "hw/mem.h"
#include "graphics/graphics.h"
#include "graphics/oam.h"

// See docs/formats/graphics.md.

// Object.dwFlags. Bits confirmed by usage in TickObject/TickObjectList and
// their callees (see docs/formats/graphics.md); several names are inferred
// from a single read/write site rather than exhaustively proven.
typedef enum {
    ObjectFlagVisible                  = 0x1,        // required (with HasSpriteCells clear)
                                                       // to queue onto the OAM/priority-sort pass
    ObjectFlagPendingDestroy           = 0x2,        // TickObject defers to FreeObject instead of ticking
    ObjectFlagWantsCollisionCheck      = 0x4,        // queues the object for the collision-check pass
    ObjectFlagHasTickLogic             = 0x8,        // opts into the full movement/pfnTick path
    ObjectFlagHasAnimation             = 0x10,       // TickObjectAnimation runs
    ObjectFlagAnimFrameLoaded          = 0x80,       // new tiles pending CommitQueuedObjectTileUpdates
    ObjectFlagSkipSpriteFrameUpdate    = 0x100,      // TickObjectList skips UpdateObjectSpriteFrame
    ObjectFlagTerrainCollisionA_candidate = 0x200,   // with ObjectFlagTerrainCollisionB_candidate: either
                                                       // bit makes CheckObjectTerrainCollision resolve
                                                       // the object against the room terrain
    ObjectFlagOnscreen                 = 0x400,      // set by UpdateObjectOnscreenFlags
    ObjectFlagTickHandlerSuspendsMovement = 0x800,   // pfnTick asked to skip the rest of this tick
    ObjectFlagSpecialMoveTrigger       = 0x8000,
    ObjectFlagTerrainCollisionB_candidate = 0x10000, // see ObjectFlagTerrainCollisionA_candidate
    ObjectFlagHasSpriteCells           = 0x20000,    // distinguishes the sprite-frame-update queue
                                                       // from the OAM/priority-sort queue
    ObjectFlagActionAnimDone           = 0x40000,    // set by TickObjectAnimation on a non-looping
                                                       // animation's last frame
    ObjectFlagFourWayDirections_candidate = 0x100000, // GetDirectionToTarget returns a Direction4
    ObjectFlagHasPaletteSlot           = 0x200000,   // AttachObjectPalette bound a palette cache slot;
                                                       // ReleaseObjectPalette clears it
    ObjectFlagOnscreenForTileAlloc     = 0x400000,   // mirrors ObjectFlagOnscreen (set/cleared
                                                       // together by UpdateObjectOnscreenFlags)
    ObjectFlagRoomRecordBound          = 0x800000,   // FreeObject clears the object's room record
    ObjectFlagNoPushTrigger_candidate  = 0x1000000,  // ApplyTerrainTypeEffect does not start a push while set
    ObjectFlagSkipTerrainOnce_candidate = 0x2000000, // CheckObjectTerrainCollision skips the terrain
                                                       // pass and clears it
    ObjectFlagTerrainDrawLayer         = 0x4000000,  // the terrain pass sets oam.priority from the
                                                       // room's collision layer under the object
    ObjectFlagRoomScriptYield          = 0x8000000,  // set by a room script that yielded on this object
    ObjectFlagAnimPaused               = 0x10000000, // TickObjectAnimation's frame counter freezes
    ObjectFlagSuppressEffectBinding    = 0x20000000, // TickObject skips Claim/BindObjectEffect entirely
    ObjectFlagExtraOamPass             = 0x80000000, // TickObjectList's extra UpdateObjectOamCells pass
} ObjectFlags;

// Object.bDrawFlags. With neither tile-sharing bit set, the object owns
// its VRAM tiles; otherwise they are refcounted in its object pool aux record
// (see ReleaseObjectOffscreenVramTiles).
typedef enum {
    ObjectDrawFlagShareTiles      = 0x1,   // one shared allocation, refcount index 0
    ObjectDrawFlagShareFrameTiles = 0x2,   // shared per animation frame, refcount index
                                            // bAnimFrameIndex_candidate
    ObjectDrawFlagFollowBelow     = 0x4,   // FollowOwnerObject: 1 pixel below the owner
    ObjectDrawFlagFollowAbove     = 0x8,   // FollowOwnerObject: 1 pixel above the owner
    ObjectDrawFlagPostActionFlash = 0x10,  // see docs/formats/battle_scripts.md; queues the
                                            // object's OAM entries with SubmitOamAttrsNudged
    ObjectDrawFlagBlink           = 0x20,  // WriteObjectOamCells hides the entries on alternate
                                            // vblanks. UpdateObjectOamCells's own entries are
                                            // queued into the slot it just hid, so they stay visible
    ObjectDrawFlagVariantSlots    = 0x40,  // draw from aVariantSlots, which then own their
                                            // tile allocations (see EnableObjectVariantSlots)
    ObjectDrawFlagExtraOamPass    = 0x80,  // set while TickObjectList's extra pass draws it
} ObjectDrawFlags;

// Signed sprite extents in pixels from the object's position, set from the
// current animation frame by LoadObjectAnimFrameBounds. UpdateObjectOnscreenFlags
// copies both words together before unpacking them.
typedef union ObjectSpriteBounds {
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
} ObjectSpriteBounds;

// Eight-way direction, clockwise from up (screen y grows downward). Odd
// values are diagonals. DirectionAtTarget: within tolerance on both axes.
typedef enum {
    DirectionUp,
    DirectionUpRight,
    DirectionRight,
    DirectionDownRight,
    DirectionDown,
    DirectionDownLeft,
    DirectionLeft,
    DirectionUpLeft,
    DirectionAtTarget,
} Direction;

// Four-way direction returned for ObjectFlagFourWayDirections_candidate.
typedef enum {
    Direction4Up,
    Direction4Right,
    Direction4Down,
    Direction4Left,
    Direction4AtTarget,
} Direction4;

// One of Object's two collision-box slots, tested by CheckObjectCollisions.
// dwPackedOffsets is 4 signed bytes: left (byte 0), right (1), top (2) and
// bottom (3) edge offsets from the integer part of posPrev (+0x36/+0x3A).
// Object.oam.hFlip/vFlip mirror an axis: its edges become position minus the
// opposite offset. GetObjectCollisionBoxRect resolves a slot to an ObjectRect;
// CheckObjectCollisions does the same math inline. bState is compared == 1 to
// take part in the pairwise overlap test; other values are unconfirmed.
typedef struct ObjectCollisionBox {
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
} ObjectCollisionBox;

// A collision box resolved to pixel edges; see GetObjectCollisionBoxRect.
typedef struct ObjectRect {
    s16 left;
    s16 right;
    s16 top;
    s16 bottom;
} ObjectRect;

// Header of an ObjectAssetRecord.pFrameData block; see docs/formats/graphics.md.
// Each awFrameOffsets entry is a byte offset from awFrameOffsets itself to
// that frame's ObjectFrameDesc.
typedef struct ObjectFrameData {
    u8 unk_0[2];
    s8 abTerrainBox[4];     // 0x02, left/right/top/bottom; see Object.bTerrainBoxLeft
    u16 wFrameCount;        // 0x06
    u8 unk_8[2];            // -> 0x0A
    u8 bFrameHeaderExtra;   // 0x0A, count of extra u16s after each ObjectFrameDesc
    u8 bFramePartCount;     // 0x0B, count of 6-byte collision boxes after those u16s: s8
                             // left/right/top/bottom, then a state byte and a byte the object does not copy
    u16 awFrameOffsets[1];  // 0x0C, wFrameCount entries
} ObjectFrameData;

typedef struct ObjectFrameDesc {
    u8 bCellCount;          // 0x00, low 5 bits
    u8 unk_1;
    u8 bWidth;              // 0x02, pixels
    u8 bHeight;             // 0x03, pixels
    u16 wTileGfxOffset;     // 0x04, byte offset of this frame's tiles from pTileGfx
    s16 awOrigin[2];        // 0x06, x/y of the frame's top-left corner, relative to the object.
                             // The frame's ObjectFrameCells start at 0x0A, after
                             // ObjectFrameData.bFramePartCount parts and bFrameHeaderExtra u16s
} ObjectFrameDesc;

// One OAM cell of an animation frame, positioned relative to the object. x/y are
// pixel offsets (doubled for a double-size affine object); size/shape are the OAM
// attributes; tileOffset is the cell's first tile relative to the frame's tiles.
typedef struct ObjectFrameCell {
    s32 x : 9;
    s32 y : 9;
    u32 size : 2;
    u32 shape : 2;
    u32 tileOffset : 10;
} __attribute__((packed)) ObjectFrameCell;

// One selectable 16-byte sprite resource record. The first two pointers feed
// SetObjectAssetRecord's tile/frame pipeline; pPalette is uploaded separately.
typedef struct ObjectAssetRecord {
    void *pTileGfx;
    void *pFrameData;
    const ObjPalette *pPalette;
    u8 bAnimFrameDelay;
} ObjectAssetRecord;

// The tile and frame half of an ObjectAssetRecord, for a sprite whose palette
// is loaded separately. It is passed where an ObjectAssetRecord is expected;
// the animation code reads only these two fields.
typedef struct ObjectGfxRecord {
    void *pTileGfx;
    void *pFrameData;
} ObjectGfxRecord;

extern const ObjectAssetRecord g_apPortraitTable[72];  // US 0x0804C61C
extern const ObjectAssetRecord g_aHelpSpriteAssets[22];  // US 0x08069AB8
extern const void *const g_apHelpSpritePalettes[22];    // US 0x08069C18

// ObjectVariantSlot.bFrameFlags.
typedef enum {
    ObjectVariantSlotFlagBlink          = 0x1,  // entries are hidden in the second half of the
                                                 // OAM shadow buffer, so the slot shows on
                                                 // alternate vblanks
    ObjectVariantSlotFlagBounds         = 0x2,  // LoadVariantSlotFrameBounds takes the object's terrain box,
                                                 // sprite bounds and collision boxes from slot 0
    ObjectVariantSlotFlagPrevFrameWrap  = 0x4,  // draw the frame before bLastAnimFrameValue,
                                                 // wrapping to the last frame
    ObjectVariantSlotFlagPrevFrameClamp = 0x8,  // draw the frame before bLastAnimFrameValue,
                                                 // clamping to frame 0
} ObjectVariantSlotFlags;

// One 12-byte sprite-variant slot embedded in Object: the tile allocation
// for the slot's current variant and the variant tables it selects from.
// While Object.bDrawFlags has ObjectDrawFlagVariantSlots, UpdateObjectOamCells
// draws the object from its variant slots (those with non-null tables) instead of
// pAnimTable; see src/object/object_variant_slots.c.
// Code indexes slots by this stride, but only slot 0 exists in the
// 0x128-byte Object and every caller loops over exactly one slot.
typedef struct ObjectVariantSlot {
    u8 bFrameFlags;         // 0x00, ObjectVariantSlotFlags
    u8 bPaletteBank;        // 0x01, OBJ palette bank written to the slot's OAM entries
    u8 bDrawOrder;          // 0x02, UpdateObjectOamCells queues slots from 7 down to 0;
                             // values above 7 are never drawn
    u8 pad_3[0x01];         // -> 0x04
    u16 wVramPixelCount;    // 0x04, size of wVramTileAllocId in pixels (0 = none)
    u16 wVramTileAllocId;   // 0x06, 0xFFFF = none
    ObjectAssetRecord **pSpriteVariantTables;  // 0x08, outer table selected by
                             // Object.bSpriteVariantTableIndex
} ObjectVariantSlot;

// Object's animation state at Object+0xD8. The animation functions reach it
// through one pointer to the whole block.
typedef struct ObjectAnimState {
    u8 bAnimFrameCounter;   // 0x00, frames-remaining countdown reloaded from
                             // bAnimFrameDelay each time it hits 0; see TickObjectAnimation
    u8 bAnimFrameDelay;     // 0x01
    u8 bAnimFrameIndex_candidate;  // 0x02, the frame LoadObjectAnimFrameBounds compares with
                             // bLastAnimFrameValue; 0xFF forces a reload. Selects the per-frame
                             // tile refcount in the object pool's
                             // aux record when ObjectDrawFlagShareTiles is clear; see
                             // ReleaseObjectOffscreenVramTiles
    u8 bLastAnimFrameValue; // 0x03, current cycling frame index for non-scripted (cursor-less)
                             // animations; see TickObjectAnimation
    union {
        u8 bEnemyAttackPhase_candidate;  // TickFighterAttackAnimState_candidate's own
                             // multi-step sentinel: 0xff idle, 0/2/3/4 successive phases
                             // -- real compares it unsigned against 0xff, not as a signed -1
        u16 wOamStripCount;  // copies of oam UpdateObjectOamCells queues, each 32 pixels
                             // right of the last, while bForceOnscreen_candidate is set
    } unk_DC;               // 0x04, agbcc rounds the union to 4 bytes (-> 0x08)
    ObjectAssetRecord *pAnimTable;  // 0x08, set by SetObjectAssetRecord; its pFrameData
                             // holds the animation frames -- see docs/formats/graphics.md
    u8 *pAnimFrameCursor;   // 0x0C
    u8 *pAnimFrameBase;     // 0x10
} ObjectAnimState;

typedef union __attribute__((packed)) ObjectScriptState {
    u16 wScriptPc;
    struct __attribute__((packed)) {
        u8 bAttackOutcomeState;
        u8 bScriptPageHigh_candidate;
    } bytes;
} ObjectScriptState;

// Bytes 0x62-0x6D of an effect script object. Read back each tick by
// ProcessObjectFlagBehaviors; bBehaviorFlags selects which fields apply.
typedef struct __attribute__((packed)) ObjectEffectState {
    u8 bEffectId;           // 0x62, index into g_apEffectScripts
    u8 abLocal[2];          // 0x63-0x64, script variables A and B; spawned children inherit
                             // each one plus 1
    u8 pad_65;
    u8 bBehaviorFlags;      // 0x66, EffectBehaviorFlags bitmask
    u8 abParams[5];         // 0x67-0x6B, meaning depends on the active behavior flags
    u8 bParam6C;            // 0x6C
    u8 bParam6D;            // 0x6D
} ObjectEffectState;

// Object 0x62-0x6D for a chest (room object type 9), from its record; see
// SpawnChestObject.
typedef struct __attribute__((packed)) ObjectChestState {
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
} ObjectChestState;

// General-purpose sprite/animation object, 0x128 bytes (confirmed by
// ExitBattle's Folio Universitas/Help resume path, which memcpys a whole one
// into FightState.aSuspendedFighterObjects_candidate -- see battle.h). Only
// the fields touched by UpdateBattle/TickPlayerActionState/ExitBattle are
// named; see those files' plate comments for the rest.
typedef struct Object {
    ListNode node;          // 0x00, active/free object-pool list link (see
                             // FreeObject/List_MoveToHead); pNext/pPrev
    u16 wObjectType;       // 0x08, AllocObjectOfType's type param; meaning is
                             // caller-defined. In the battle subsystem, values are
                             // a small per-kind index (player fighter 0-3, monster
                             // type id) -- see InitPlayerBattleActor/InitMonsterBattleActor
    u16 wCharacterId_candidate;  // 0x0A, party members' character id (compared against a script's character operand)
    ObjectFlags dwFlags;    // 0x0C
    u8 bRoomTileCol_candidate;  // 0x10, SetRoomObjectRecordPtr_candidate's column arg
    u8 bRoomTileRow_candidate;  // 0x11, SetRoomObjectRecordPtr_candidate's row arg
    u8 bFacing;             // 0x12, direction/facing index; see SetObjectFacing
    u8 pad_13[0x01];        // -> 0x14
    u16 wMoveDuration;      // 0x14
    u8 bDepthSortBias;      // 0x16, draw-order bias; see SortObjectsByDepth
    u8 pad_17[0x0D];        // -> 0x24
    ParticleEmitter *pWindupParticleEmitter;  // 0x24, freed via
                             // ReleaseParticleEmitter_candidate and zeroed
                             // when nonzero (see ClearParalyzedFighter_candidate)
    u32 dwUnk_0x28;         // 0x28, set to 1 by InitPlayerBattleActor_candidate
    FixedPoint pos;         // 0x2C
    FixedPoint posPrev;     // 0x34, pending position: IntegrateObjectVelocity sets it
                             // to pos plus velocity, and TickObjectList copies it into pos
                             // after collisions. See docs/formats/battle_scripts.md's
                             // StartOrbitMotion/ApplyObjectOrbitMotion writeup.
                             // SetObjectPosition/SnapObjectPosition also set this
                             // equal to pos (no interpolation pending after a teleport)
    FixedPoint vel;         // 0x3C
    FixedPoint accel;       // 0x44, added to vel each tick by IntegrateObjectVelocity
    FixedPoint moveTarget;  // 0x4C, set by SetObjectMoveTarget/StartObjectMove
    union __attribute__((packed)) {
        // 0x54-0x5F, {angleX, angleY, velX, velY, radiusX, radiusY}; see
        // CopyOrbitParamsFromTable and docs/formats/battle_scripts.md
        u16 awOrbit[6];
        struct __attribute__((packed)) {
            u8 pad_54[0x04];        // -> 0x58
            s16 wUnk58;             // 0x58, scaled (>> 7) by DivinationTea's leaf drift
            u8 pad_5A[0x02];        // -> 0x5C
            u32 dwOrbitRadii;       // 0x5C, packed radiusX/radiusY; nonzero runs ApplyObjectOrbitMotion
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
    ObjectScriptState scriptState;  // 0x60: object script PC or battle outcome/page bytes
    // 0x62-0x6D is per-mode state: the actor view serves fighter and room
    // objects, the effect view serves battle-effect script objects
    // (see InterpretObjectScript).
    union __attribute__((packed)) {
        struct __attribute__((packed)) {
            u16 wStagedDamage;      // 0x62
            u8 bRoomScriptArg64_candidate;  // 0x64, set by room script animation handlers
            u8 bFollowResumeDistance;  // 0x65, action state 0x12: resume following beyond this (pixels)
            u8 bRoomScriptArg66_candidate;  // 0x66, set by StartTileObjectScript
            u8 bRoomObjectArg67_candidate;  // 0x67
            u8 bFollowStopDistance; // 0x68, action state 0x12: stop following within this (pixels)
            u8 bRoomObjectArg69_candidate;  // 0x69
            u8 bRoomScriptArg6A_candidate;  // 0x6A, set by StartObjectAnimSequence
            u8 bRoomScriptArg6B_candidate;  // 0x6B, set by StartObjectAnimSequence
            u8 bDelayedRespawnRow;  // 0x6C, delayed-chain script effect: RespawnRowAndRunChain_candidate
            u8 bDelayedChainRow;    // 0x6D   arguments once dwStateTimer runs out
        } actor;
        ObjectEffectState effect;
        ObjectChestState chest;
    } modeState;
    u8 pad_6E[0x0E];        // -> 0x7C
    u8 bUnk_0x7C;           // 0x7C, set to 5 by AllocObjectOfType, zeroed by
                             // InitPlayerBattleActor_candidate
    u8 bTerrainType;        // 0x7D, collision type under the object, set by RespondToTerrain
    u8 pad_7E[0x02];        // -> 0x80
    u32 dwStateTimer;       // 0x80
    u16 wUnk84;             // 0x84, zeroed by the type 6 room object constructor
    u16 wUnk86;             // 0x86, zeroed alongside wMoveDuration
    u8 pad_88[0x02];        // -> 0x8a
    u16 wActionVariant;     // 0x8A
    u8 bRoomObjectKind_candidate;  // 0x8C, set from the tile record by room object constructors; 2 selects the second collision box
    u8 bActionState;        // 0x8D, the dispatch key
    u8 bPrevActionState_candidate;  // 0x8E, ExitDialogue restores the player to this action state
    u8 bActionSubState;     // 0x8F, secondary per-object state; see SetObjectActionSubState
    u8 bActionFlags;        // 0x90
    u8 bFighterIndex;       // 0x91
    u8 bReceivedRewardId;   // 0x92, player: reward id shown by the receive-item action (0x17)
    u8 pad_93[0x01];        // -> 0x94
    u8 bFlags_0x94_candidate;  // 0x94, bit 0x4 set by a room script; meaning unconfirmed
    u8 pad_95[0x03];        // -> 0x98
    void (*pfnTick)(struct Object *obj);  // 0x98, per-frame tick (player fighters: TickPlayerActionState)
    void (*pfnDestructor)(struct Object *obj);  // 0x9C, called by FreeObject if non-null
    struct Object *pShadowObject;  // 0xA0, companion object (main -> shadow); the
                                   // object followed in action state 0x12
    struct Object *pLinkedObject_candidate;  // 0xA4, one of three linked-object slots
                                     // (see docs/formats/room_scripts.md); caller-defined
    struct Object *pOwnerObject;   // 0xA8, back-link (shadow -> main)
    u16 wFlags_0xAC;        // 0xAC, bit 0x1 set by AllocDefaultObject; also read by
                             // CheckObjectTerrainCollision as one of several "movement stopped"
                             // conditions. Not enough evidence yet for a real name.
    u8 pad_AE[0x01];        // -> 0xAF
    u8 bCollisionBoxCount;  // 0xAF, aCollisionBoxes in use: the animation frame's box count,
                             // or 1 or 2 from the room object constructors
    ObjectCollisionBox aCollisionBoxes[2];  // 0xB0, see CheckObjectCollisions;
                             // slot 0 at 0xB0, slot 1 at 0xB8
    // 0xC0-0xC3: terrain bounding box, signed pixel offsets from the object's
    // integer position, copied from the sprite record's ObjectFrameData by
    // LoadObjectAnimFrameBounds (the same box for every frame).
    // Terrain probes (GetUnblockedDirectionToTarget, GetObjectTerrainBox) test pixels
    // at these edges.
    s8 bTerrainBoxLeft;     // 0xC0
    s8 bTerrainBoxRight;    // 0xC1
    s8 bTerrainBoxTop;      // 0xC2
    s8 bTerrainBoxBottom;   // 0xC3
    u8 pad_C4[0x04];        // -> 0xC8
    void (*apfnCollisionCallback[2])(struct Object *self, struct Object *other);
                             // 0xC8, called by CheckObjectCollisions on an
                             // overlap of the matching-index box, per object
    OamEntry oam;           // 0xD0, the object's base OAM attributes. affineMode holds the
                             // affine-slot allocation state (see ReleaseObjectAffineSlot/
                             // FreeObject); objMode is 1 for menu cursors; bpp8 is passed to
                             // FreeObjectVramTileAllocation; tileNum is copied from
                             // wVramTileAllocId by CommitQueuedObjectTileUpdates; priority is
                             // the draw layer (see SetObjectDrawLayer/SortObjectsByDepth/
                             // TickObjectList); paletteNum is the graphics-cache slot (see
                             // ReleaseObjectPalette/BindEffectChannelSlot_candidate).
                             // UpdateObjectOamCells fills in x/y each frame
    ObjectAnimState anim;   // 0xD8
    s32 nAffineScaleX;      // 0xEC, 16.16 fixed-point affine scale X (0x10000 = 1.0x); see
                             // TickObjectAffineEffect/SetObjectAffineTransform/
                             // StartObjectAffineScaleTween
    s32 nAffineScaleY;      // 0xF0
    s32 nAffineScaleVelX;   // 0xF4, per-tick delta TickObjectAffineEffect adds to
                             // nAffineScaleX; set by StartObjectAffineScaleTween to linearly
                             // tween to a target scale over N ticks
    s32 nAffineScaleVelY;   // 0xF8
    u16 wAffineAngle;       // 0xFC
    u8 bAffineEffectTimer;  // 0xFE, ticks remaining for the current scale tween; nonzero keeps
                             // TickObjectAffineEffect running
    u8 bAffineMode;         // 0xFF, mirrors oam.affineMode
    ObjectSpriteBounds spriteBounds;  // 0x100, signed X/Y extent pairs used for visibility
    void *pEffectData;      // 0x108, direct pointer form of the same graphics-cache resource
                             // oam.paletteNum indexes (mutually exclusive with
                             // it -- see ReleaseObjectPalette/BindEffectChannelSlot_candidate)
    u32 dwEffectFlags;      // 0x10C
    u16 wVramPixelCount;    // 0x110, size of wVramTileAllocId in pixels (0 = none)
    u16 wVramTileAllocId;   // 0x112, VRAM tile allocation id passed to
                             // FreeObjectVramTileAllocation (0xFFFF = none); set to 0xFFFF by
                             // ExitBattle when suspending a fighter for the Folio Universitas/
                             // Help resume path
    u8 bForceOnscreen_candidate;  // 0x114, value 1 prevents visibility flags being cleared
    u8 bDrawFlags;          // 0x115, ObjectDrawFlags
    u8 bObjectPoolAuxSlot;  // 0x116, index into g_pObjectPoolAuxBuffer's 0x34-byte-stride
                             // records; see ReleaseObjectOffscreenVramTiles
    u8 pad_117[0x01];       // -> 0x118
    ObjectVariantSlot aVariantSlots[1];  // 0x118
    s8 bSpriteVariantTableIndex;  // 0x124, shared by every variant slot
    s8 bSpriteVariantIndex;       // 0x125
    u8 pad_126[0x02];       // -> 0x128
} Object;

// wObjectType values used by room/overworld object spawners (room-tile
// constructor dispatch at g_apRoomObjectConstructors, 0x0804C054). Several
// constructor slots (1-4, 6, 7, 13) forward a per-instance type value already
// stored in the room's own tile record instead of a fixed constant, so this
// list only covers the values actually hardcoded in code.
typedef enum {
    RoomObjectType_Player           = 0,     // SpawnPlayerObject_candidate
    RoomObjectType_ScriptedTrigger  = 5,     // sub-behavior picked by a separate per-instance kind field
    RoomObjectType_Unk8             = 8,
    RoomObjectType_Chest            = 9,     // SpawnChestObject
    RoomObjectType_UnkA             = 0xA,
    RoomObjectType_UnkB             = 0xB,
    RoomObjectType_UnkC             = 0xC,
    RoomObjectType_ScriptEffect     = 0xE,   // SpawnScriptEffectObject, e.g. delayed chain runs;
                                              // reuses the same value as BattleObjectType_FighterSlot0
                                              // since room/overworld and battle never run concurrently
    RoomObjectType_WanderingMonster = 0x10,  // SpawnWanderingMonsterObject; reuses
                                              // BattleObjectType_FighterSlot0 + 2 for the same reason
} RoomObjectType;

// wObjectType values used by battle-mode object spawners. See RoomObjectType
// above for why these overlap with room/overworld values.
typedef enum {
    BattleObjectType_FighterSlot0 = 0xE,   // InitializeBattle: + fighter slot index 0-6
    BattleObjectType_MessageIcon  = 0x15,  // InitializeBattle: FighterSlot0 + 7
    BattleObjectType_EffectScript = 0x17,  // CreateEffectScriptObject, spell/attack visual effect
} BattleObjectType;

extern Object *AllocObjectOfType(s32 type);
extern Object *AllocDefaultObject(void);
extern void FreeObject(Object *obj);
extern u32 TickActiveObjects(void);
extern s32 UpdateObjectOnscreenFlags(Object *obj);
extern void SetObjectSpriteVariant(Object *obj, s8 tableIndex, s8 variantIndex);
extern void GetObjectVariantFrameSize(Object *obj, u32 *dims, u8 slot);
extern void *GetObjectVariantFrameTileGfx(Object *obj, u8 slot);
extern u8 GetDirectionToTarget(u32 objectFlags, FixedPoint pos, FixedPoint target, s32 tolerance);
extern u8 GetUnblockedDirectionToTarget(Object *obj, FixedPoint pos, FixedPoint target, s32 tolerance);
extern ObjectRect GetObjectCollisionBoxRect(Object *obj, s32 boxIndex);
extern s32 DoObjectsOverlap(Object *a, Object *b);  // tests collision box 0 of each
extern void ReleaseObjectOffscreenVramTiles(Object *obj);  // 0x08001300
// Frees the OBJ VRAM tiles of an allocation of pixelCount pixels.
extern void FreeObjectVramTileAllocation(u16 allocId, u32 pixelCount, u8 is8bpp);  // 0x08045514
// Returns the first allocated tile, or 0xFFFF when none are free.
extern u32 AllocObjectVramTiles(ObjectAssetRecord *record, u32 pixelCount, u32 is8bpp);
// Decompresses every frame of record's tile graphics into consecutive OBJ VRAM tiles starting at
// tile firstTile.
extern void LoadObjTileSheet(ObjectAssetRecord *record, u16 firstTile);
// Releases an allocation immediately; FreeObjectVramTileAllocation defers it to the next OAM swap.
extern void FreeObjectVramTileAllocationNow(u16 allocId, u32 pixelCount, u8 is8bpp);
// Decompresses tileGfx into OBJ VRAM at the object's wVramTileAllocId.
extern void LoadObjTile(Object *obj, void *tileGfx);
// Decompresses tileGfx into OBJ VRAM at tile allocId; other arguments are unused.
extern void LoadObjTileAt(ObjectFrameData *frameData, void *tileGfx, u16 allocId, u16 frame,
                          u16 pixelCount);
extern void ReleaseObjectPalette(Object *obj);  // 0x080308D8
extern void SetRoomObjectRecordPtr_candidate(Object *obj, u8 col, u8 row);
extern Object *SpawnObject(u32 type, s32 x, s32 y, const ObjPalette *pPalette);
extern void SetObjectPosition(Object *obj, s32 x, s32 y);
extern void SnapObjectPosition(Object *obj, u32 x, u32 y);
extern void SetObjectVelocity(Object *obj, u32 velX, u32 velY);
extern void SetObjectMoveTarget(Object *obj, u32 x, u32 y);
extern void StartObjectMove(Object *obj, u32 x, u32 y, u16 mode);
extern void ReleaseObjectAffineSlot(Object *obj);
extern u32 GetObjectAffineSlotId(OamEntry *oam);
extern void SetObjectAffineSlotId(OamEntry *oam, u16 slot);
extern u32 AllocObjectAffineSlot(Object *obj);  // memoized: returns the slot already in oam if
                             // oam.affineMode is set (1 or 3), else calls AllocAffineSlot and
                             // stores the result
extern void SetObjectAffineTransform(Object *obj, u32 nScaleX, u32 nScaleY, s16 wAngle, u8 bMode);
// Double-size affine with both scales set to step 0..8 of a table: 0x666, then 0x2000 * step.
extern void SetObjectScaleStep(Object *obj, u32 step);
extern void StartObjectAffineScaleTween(Object *obj, u32 nTargetScaleX, u32 nTargetScaleY, s32 nFrames);  // ramps nAffineScaleX/Y to the target over nFrames ticks (0 = set immediately)
extern void SetObjectFlippedX(Object *obj, s32 flip);
// pAnimTable is the sprite record; the stream starts at command startCommand
// of pAnimData (see graphics/object_anim.h).
extern void SetObjectAnimData(Object *obj, const void *pAnimTable, const void *pAnimData, u8 startCommand);
extern u32 TickObjectList(ActiveObjectListState *list, u8 mode);
extern void TickObject(Object *obj, u32 mode);
extern s32 IsObjectTickAllowed(void);
extern void CheckObjectTerrainCollision(Object *obj);
extern void TickObjectMove(Object *obj);
extern void TickObjectAnimation(Object *obj);
extern void TickObjectAffineEffect(Object *obj);  // steps the scale tween while bAffineEffectTimer runs
extern void IntegrateObjectVelocity(Object *obj);
extern void BindObjectEffectData(Object *obj);  // binds pEffectData to a resource-cache slot, then clears it
extern u8 UpdateObjectOamCells(Object *obj);
// Queues the OAM cells of one frame of frameData, copying the other attributes
// from pTemplate and placing them relative to the screen position pos[0]/pos[1].
// cellFlags bit 0 hides the cells on alternate vblanks; bit 1 is set for
// TickObjectList's extra OAM pass (see docs/memory-map/heap.md).
extern void WriteObjectOamCells(ObjectFrameData *frameData, u16 frame, u8 cellFlags, s32 *pos,
                                u16 tileBase, OamEntry *pTemplate, Object *obj);
extern void UpdateObjectSpriteFrame(Object *obj, u32 mode);
extern void ApplyObjectOrbitMotion(Object *obj);
// Moves an object to its pOwnerObject's pending position and draw layer.
extern void FollowOwnerObject(Object *obj);
extern void CommitQueuedObjectTileUpdates(void);  // run from vblank callbacks
extern void sub_08001690(Object *obj, const void *pAssetRecord);
extern void SetObjectAnimFrame(Object *obj, u8 bFrameIndex);  // sets bLastAnimFrameValue, reloading cells if changed
extern void RunObjectAnimCommands(Object *obj);
extern void LoadObjectAnimFrameBounds(Object *obj);
extern void LoadVariantSlotFrameBounds(Object *obj);
extern void SetObjectActionState(Object *obj, u8 state);
extern void SetObjectFlags(Object *obj, ObjectFlags flags);
// Starts animation `animId` from the object's animation table.
extern void SetObjectAnimData_candidate(Object *obj, u32 animId);
extern void SetObjectActionSubState(Object *obj, u8 state);
extern void SetObjectDrawLayer(Object *obj, u8 layer);
extern void SetObjectAnimSubState_candidate(Object *obj, u8 state);
// Clears the object's queued move (Object+0x3C..0x48).
extern void CancelObjectMove_candidate(Object *obj);
extern void SetObjectAssetRecord(Object *obj, const void *rec);
// Like AttachObjectPalette, but always binds a newly allocated cache slot
// instead of sharing one already holding pPalette, and marks the slot
// ResourceCacheFlagUnshared. Returns the slot index.
extern u8 AttachObjectPaletteUnshared_candidate(Object *obj, const ObjPalette *pPalette);
extern Object *SpawnMenuIconObject(u32 slot, u32 arg1);  // allocs a type 0x13 object and files it under slot
extern u32 AttachObjectPalette(Object *obj, const ObjPalette *pPalette);  // 0x08030878
extern void BindObjectToResourceCacheSlot(u32 slotIndex, Object *obj, const ObjPalette *pPalette);

// Bodies of AttachObjectPalette and AttachObjectPaletteUnshared_candidate, which the
// ROM also inlines in BindObjectEffectData.
static inline u32 AttachSharedPalette(Object *obj, const ObjPalette *pPalette)
{
    u32 slot = FindResourceCacheSlot(pPalette);

    if (slot != 0xFF)
        pPalette = NULL;
    else
        slot = AllocResourceCacheSlot();

    BindObjectToResourceCacheSlot(slot, obj, pPalette);
    return slot;
}

static inline u32 AttachUnsharedPalette(Object *obj, const ObjPalette *pPalette)
{
    u32 slot = AllocResourceCacheSlot();

    BindObjectToResourceCacheSlot(slot, obj, pPalette);
    g_aResourceCache[slot].wFlags |= ResourceCacheFlagUnshared;
    return slot;
}
extern void sub_080039E8(Object *obj);
extern void sub_080039F8(Object *obj);
extern void sub_08003A0C(Object *obj);
extern void sub_08003A44(Object *obj, s32 a, s32 b, s32 c);
extern void sub_0801BCB0(void *linkedObject);
extern Object *CreateEffectScriptObject(s32 effectId, s32 kind);  // 0x08018BE0
