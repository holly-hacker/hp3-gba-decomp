#pragma once

#include "types.h"
#include "mem.h"
#include "graphics.h"
#include "oam.h"

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
    ObjectFlagAnimFrameLoaded          = 0x80,       // set once LoadObjectAnimFrameCells has run
    ObjectFlagSkipSpriteFrameUpdate    = 0x100,      // TickObjectList skips UpdateObjectSpriteFrame
    ObjectFlagOnscreen                 = 0x400,      // set by UpdateObjectOnscreenFlags
    ObjectFlagTickHandlerSuspendsMovement = 0x800,   // pfnTick asked to skip the rest of this tick
    ObjectFlagSpecialMoveTrigger       = 0x8000,
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
    ObjectDrawFlagPostActionFlash = 0x10,  // see docs/formats/battle_scripts.md; queues the
                                            // object's OAM entries with SubmitOamAttrsNudged
    ObjectDrawFlagBlink           = 0x20,  // WriteObjectOamCells hides the entries on alternate
                                            // vblanks. UpdateObjectOamCells's own entries are
                                            // queued into the slot it just hid, so they stay visible
    ObjectDrawFlagVariantSlots    = 0x40,  // draw from aVariantSlots, which then own their
                                            // tile allocations (see EnableObjectVariantSlots)
    ObjectDrawFlagExtraOamPass    = 0x80,  // set while TickObjectList's extra pass draws it
} ObjectDrawFlags;

// Signed sprite extents packed as {low s16, high s16} for each axis.
// UpdateObjectOnscreenFlags copies both words together before unpacking them.
typedef struct ObjectSpriteBounds {
    u32 packedX;
    u32 packedY;
} ObjectSpriteBounds;

// A 16.16 fixed-point position, passed by value.
typedef struct FixedPoint {
    s32 x;
    s32 y;
} FixedPoint;

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
// bottom (3) edge offsets from the integer part of nXPrev/nYPrev (+0x36/+0x3A).
// Object.oam.hFlip/vFlip mirror an axis: its edges become position minus the
// opposite offset. GetObjectCollisionBoxRect resolves a slot to an ObjectRect;
// CheckObjectCollisions does the same math inline. bState is compared == 1 to
// take part in the pairwise overlap test; other values are unconfirmed.
typedef struct ObjectCollisionBox {
    u32 dwPackedOffsets;  // 0x00
    u8 bState;            // 0x04
    u8 pad_5[3];          // -> 0x08
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
    u8 unk_0[6];
    u16 wFrameCount;        // 0x06
    u8 unk_8[2];            // -> 0x0A
    u8 bFrameHeaderExtra;   // 0x0A, count of extra u16s after each ObjectFrameDesc
    u8 bFramePartCount;     // 0x0B, count of extra 6-byte parts after each ObjectFrameDesc
    u16 awFrameOffsets[1];  // 0x0C, wFrameCount entries
} ObjectFrameData;

typedef struct ObjectFrameDesc {
    u8 bCellCount;          // 0x00, low 5 bits
    u8 unk_1;
    u8 bWidth;              // 0x02, pixels
    u8 bHeight;             // 0x03, pixels
    u16 wTileGfxOffset;     // 0x04, byte offset of this frame's tiles from pTileGfx
    u8 unk_6[4];            // 0x06; the frame's ObjectFrameCells start at 0x0A, after
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
    void *pPalette;
    u8 bAnimFrameDelay;
    u8 pad_D[3];
} ObjectAssetRecord;

extern const ObjectAssetRecord g_apPortraitTable[72];  // US 0x0804C61C

// ObjectVariantSlot.bFrameFlags.
typedef enum {
    ObjectVariantSlotFlagBlink          = 0x1,  // entries are hidden in the second half of the
                                                 // OAM shadow buffer, so the slot shows on
                                                 // alternate vblanks
    ObjectVariantSlotFlagBounds         = 0x2,  // sub_080024B0 takes the object's terrain box,
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
    u16 wVramTileRow;       // 0x04, second argument to FreeObjectVramTileAllocation
    u16 wVramTileAllocId;   // 0x06, 0xFFFF = none
    ObjectAssetRecord **pSpriteVariantTables;  // 0x08, outer table selected by
                             // Object.bSpriteVariantTableIndex
} ObjectVariantSlot;

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
    u32 nX;                 // 0x2C, 16.16
    u32 nY;                 // 0x30, 16.16
    u32 nXPrev;             // 0x34, 16.16; see docs/formats/battle_scripts.md's
                             // StartOrbitMotion/ApplyObjectOrbitMotion writeup.
                             // SetObjectPosition/SnapObjectPosition also set this
                             // equal to nX (no interpolation pending after a teleport)
    u32 nYPrev;              // 0x38, see nXPrev
    u32 nVelX;              // 0x3C
    u32 nVelY;              // 0x40
    u8 pad_44[0x08];        // -> 0x4C
    u32 nMoveTargetX;       // 0x4C, 16.16; set by SetObjectMoveTarget/StartObjectMove
    u32 nMoveTargetY;       // 0x50
    u8 pad_54[0x04];        // -> 0x58
    s16 wUnk58;             // 0x58, scaled (>> 7) by DivinationTea's leaf drift
    u8 pad_5A[0x02];        // -> 0x5C
    u32 dwOrbitRadii;       // 0x5C, packed radiusX/radiusY; nonzero runs ApplyObjectOrbitMotion
    u8 bAttackOutcomeState; // 0x60
    u8 bScriptPageHigh_candidate;  // 0x61, written by a room script
    u16 wStagedDamage;      // 0x62
    u8 pad_64[0x18];        // -> 0x7C
    u8 bUnk_0x7C;           // 0x7C, set to 5 by AllocObjectOfType, zeroed by
                             // InitPlayerBattleActor_candidate
    u8 pad_7D[0x03];        // -> 0x80
    u32 dwStateTimer;       // 0x80
    u8 pad_84[0x02];        // -> 0x86
    u16 wUnk86;             // 0x86, zeroed alongside wMoveDuration
    u8 pad_88[0x02];        // -> 0x8a
    u16 wActionVariant;     // 0x8A
    u8 pad_8C[0x01];        // -> 0x8D
    u8 bActionState;        // 0x8D, the dispatch key
    u8 pad_8E[0x01];        // -> 0x8F
    u8 bActionSubState;     // 0x8F, secondary per-object state; see SetObjectActionSubState
    u8 bActionFlags;        // 0x90
    u8 bFighterIndex;       // 0x91
    u8 pad_92[0x02];        // -> 0x94
    u8 bFlags_0x94_candidate;  // 0x94, bit 0x4 set by a room script; meaning unconfirmed
    u8 pad_95[0x03];        // -> 0x98
    void (*pfnTick)(struct Object *obj);  // 0x98, per-frame tick (player fighters: TickPlayerActionState)
    void (*pfnDestructor)(struct Object *obj);  // 0x9C, called by FreeObject if non-null
    struct Object *pShadowObject;  // 0xA0, companion object (main -> shadow)
    struct Object *pLinkedObject_candidate;  // 0xA4, one of three linked-object slots
                                     // (see docs/formats/room_scripts.md); caller-defined
    struct Object *pOwnerObject;   // 0xA8, back-link (shadow -> main)
    u16 wFlags_0xAC;        // 0xAC, bit 0x1 set by AllocDefaultObject; also read by
                             // sub_08001F40 as one of several "movement stopped"
                             // conditions. Not enough evidence yet for a real name.
    u8 pad_AE[0x02];        // -> 0xB0
    ObjectCollisionBox aCollisionBoxes[2];  // 0xB0, see CheckObjectCollisions;
                             // slot 0 at 0xB0, slot 1 at 0xB8
    // 0xC0-0xC3: terrain bounding box, signed pixel offsets from the object's
    // integer position, copied from the current animation frame (sub_080023B4).
    // Terrain probes (GetUnblockedDirectionToTarget, sub_0802D868) test pixels
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
    u8 bAnimFrameCounter;   // 0xD8, frames-remaining countdown reloaded from bAnimFrameDelay
                             // each time it hits 0; see TickObjectAnimation
    u8 bAnimFrameDelay;     // 0xD9
    u8 bAnimFrameIndex_candidate;  // 0xDA, selects the per-frame tile refcount in the object pool's
                             // aux record when ObjectDrawFlagShareTiles is clear; see
                             // ReleaseObjectOffscreenVramTiles
    u8 bLastAnimFrameValue; // 0xDB, current cycling frame index for non-scripted (cursor-less)
                             // animations; see TickObjectAnimation
    union {
        u8 bEnemyAttackPhase_candidate;  // TickFighterAttackAnimState_candidate's own
                             // multi-step sentinel: 0xff idle, 0/2/3/4 successive phases
                             // -- real compares it unsigned against 0xff, not as a signed -1
        u16 wOamStripCount;  // copies of oam UpdateObjectOamCells queues, each 32 pixels
                             // right of the last, while bForceOnscreen_candidate is set
    } unk_DC;               // 0xDC, agbcc rounds the union to 4 bytes (-> 0xE0)
    ObjectAssetRecord *pAnimTable;  // 0xE0, set by SetObjectAssetRecord; its pFrameData
                             // holds the animation frames -- see docs/formats/graphics.md
    u8 *pAnimFrameCursor;   // 0xE4
    u8 *pAnimFrameBase;     // 0xE8
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
    u16 wVramTileRow;       // 0x110, row passed to FreeObjectVramTileAllocation
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
    RoomObjectType_ScriptedOneTime  = 9,     // SpawnScriptedOneTimeObject
    RoomObjectType_UnkA             = 0xA,
    RoomObjectType_UnkB             = 0xB,
    RoomObjectType_UnkC             = 0xC,
    RoomObjectType_ScriptEffect     = 0xE,   // SpawnScriptEffectObject_candidate, camera-pan effect;
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
extern void FreeObjectVramTileAllocation(u16 allocId, u16 tileRow, u8 is8bpp);  // 0x08045514
extern void ReleaseObjectPalette(Object *obj);  // 0x080308D8
extern void SetRoomObjectRecordPtr_candidate(Object *obj, u8 col, u8 row);
extern Object *SpawnObject(u32 type, s32 x, s32 y, const ObjPalette *pPalette);
extern void SetObjectPosition(Object *obj, s32 x, s32 y);
extern void SnapObjectPosition(Object *obj, u32 x, u32 y);
extern void SetObjectVelocity(Object *obj, u32 velX, u32 velY);
extern void SetObjectMoveTarget(Object *obj, u32 x, u32 y);
extern void StartObjectMove(Object *obj, u32 x, u32 y, u16 mode);
extern void ReleaseObjectAffineSlot(Object *obj);
extern u32 AllocObjectAffineSlot(Object *obj);  // memoized: returns the already-allocated slot
                             // id from wAffineSlotIndexPacked if oam.affineMode is
                             // set (1 or 3), else calls AllocAffineSlot and stores the result
extern void SetObjectAffineTransform(Object *obj, u32 nScaleX, u32 nScaleY, s16 wAngle, u8 bMode);
extern void StartObjectAffineScaleTween(Object *obj, u32 nTargetScaleX, u32 nTargetScaleY, s32 nFrames);  // ramps nAffineScaleX/Y to the target over nFrames ticks (0 = set immediately)
extern void SetObjectFlippedX(Object *obj, s32 flip);
extern void SetObjectAnimData(Object *obj, void *a, void *b, s32 c);
extern u32 TickObjectList(ActiveObjectListState *list, u8 mode);
extern void TickObject(Object *obj, u32 mode);
extern s32 IsObjectTickAllowed(void);
extern void CheckObjectTerrainCollision(Object *obj);
extern void TickObjectMove(Object *obj);
extern void TickObjectAnimation(Object *obj);
extern void TickObjectAffineEffect(Object *obj);  // steps the scale tween while bAffineEffectTimer runs
extern void IntegrateObjectVelocity(Object *obj);  // adds +0x44/+0x48 to the velocity, then sets
                             // nXPrev/nYPrev to the position plus velocity
extern void BindObjectEffectData(Object *obj);  // binds pEffectData to a resource-cache slot, then clears it
extern u8 UpdateObjectOamCells(Object *obj);
// Queues the OAM cells of one frame of frameData, copying the other attributes
// from pTemplate and placing them relative to the screen position pos[0]/pos[1].
// cellFlags bit 0 hides the cells on alternate vblanks; bit 1 is set for
// TickObjectList's extra OAM pass (see docs/memory-map/heap.md).
extern void WriteObjectOamCells(ObjectFrameData *frameData, u16 frame, u8 cellFlags, s32 *pos,
                                u16 tileBase, OamEntry *pTemplate, Object *obj);
extern void UpdateObjectSpriteFrame(Object *obj, u8 mode);
extern void ApplyObjectOrbitMotion(Object *obj);
extern void sub_080034B8(Object *obj);
extern void sub_08030C00(void);
extern void sub_080317EC(u8 layer);  // flushes the particles queued for one draw layer
extern void sub_08030140(void);
extern void CommitQueuedObjectTileUpdates(void);  // run from vblank callbacks
extern void sub_08001690(Object *obj, const void *pAssetRecord);
extern void SetObjectAnimFrame(Object *obj, u8 bFrameIndex);  // sets bLastAnimFrameValue, reloading cells if changed
extern void SetObjectActionState(Object *obj, u8 state);
// Starts animation `animId` from the object's animation table.
extern void SetObjectAnimData_candidate(Object *obj, u32 animId);
extern void SetObjectActionSubState(Object *obj, u8 state);
extern void SetObjectAnimSubState_candidate(Object *obj, u8 state);
// Clears the object's queued move (Object+0x3C..0x48).
extern void CancelObjectMove_candidate(Object *obj);
extern void SetObjectAssetRecord(Object *obj, void *rec);
extern u8 AttachObjectEffectSlot_candidate(Object *obj, s32 effectPtr);
extern Object *sub_0802C90C(u32 slot, u32 arg1);  // allocs a type 0x13 object and files it under slot
extern u32 AttachObjectPalette(Object *obj, const ObjPalette *pPalette);  // 0x08030878
extern void BindObjectToResourceCacheSlot(u32 slotIndex, Object *obj, const ObjPalette *pPalette);
extern void sub_080039E8(Object *obj);
extern void sub_080039F8(Object *obj);
extern void sub_08003A0C(Object *obj);
extern void sub_08003A44(Object *obj, s32 a, s32 b, s32 c);
extern void sub_0801BCB0(void *linkedObject);
extern Object *CreateEffectScriptObject(s32 effectId, s32 kind);  // 0x08018BE0
