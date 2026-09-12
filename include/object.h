#pragma once

#include "types.h"
#include "mem.h"
#include "graphics.h"

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
    ObjectFlagOnscreenForTileAlloc     = 0x400000,   // mirrors ObjectFlagOnscreen (set/cleared
                                                       // together by UpdateObjectOnscreenFlags);
                                                       // gates ReleaseObjectOffscreenVramTiles
    ObjectFlagRoomRecordBound          = 0x800000,   // FreeObject clears the object's room record
    ObjectFlagAnimPaused               = 0x10000000, // TickObjectAnimation's frame counter freezes
    ObjectFlagSuppressEffectBinding    = 0x20000000, // TickObject skips Claim/BindObjectEffect entirely
} ObjectFlags;

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
    u8 pad_0A[0x02];        // -> 0x0C
    ObjectFlags dwFlags;    // 0x0C
    u8 bRoomTileCol_candidate;  // 0x10, SetRoomObjectRecordPtr_candidate's column arg
    u8 bRoomTileRow_candidate;  // 0x11, SetRoomObjectRecordPtr_candidate's row arg
    u8 pad_12[0x02];        // -> 0x14
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
    void (*pfnDestructor)(struct Object *obj);  // 0x9C, called by FreeObject if non-null
    struct Object *pShadowObject;  // 0xA0, companion object (main -> shadow)
    void *pLinkedObject_candidate;  // 0xA4; see docs/formats/room_scripts.md and
                                     // docs/formats/save.md's per-object save table
                                     // (Object+0xa0/+0xa4/+0xa8, three linked-object slots)
    struct Object *pOwnerObject;   // 0xA8, back-link (shadow -> main)
    u8 pad_AC[0x25];        // -> 0xD1
    u8 bFlags_0xD1;         // 0xD1: bits 0-1 = affine-transform slot allocation state (0 = free,
                             // 1/3 = allocated -- see ReleaseObjectAffineSlot/FreeObject's
                             // (bFlags_0xD1 & 3) checks), bit 0x20 = large/8bpp-sprite flag
                             // consumed by FreeObjectVramTileAllocation; bit 0x20 set / bits
                             // 0x0C cleared by InitializeBattle
    u16 wAffineSlotIndexPacked;  // 0xD2, bits 9-13 = allocated hardware affine parameter-set
                             // index (0-31); see GetObjectAffineSlotId/SetObjectAffineSlotId/
                             // AllocAffineSlot/FreeAffineSlot
    u8 pad_D4;               // -> 0xD5
    u8 bGfxSlotAndFlags;    // 0xD5, upper nibble = graphics-cache slot (see
                             // ClaimObjectEffectResource/AllocEffectChannelSlot_candidate/
                             // BindEffectChannelSlot_candidate), bits 2-3 = terrain type written
                             // by UpdateObjectTileCollisionState
    u8 pad_D6[0x02];        // -> 0xD8
    u8 bAnimFrameCounter;   // 0xD8, frames-remaining countdown reloaded from bAnimFrameDelay
                             // each time it hits 0; see TickObjectAnimation
    u8 bAnimFrameDelay;     // 0xD9
    u8 pad_DA;               // -> 0xDB
    u8 bLastAnimFrameValue; // 0xDB, current cycling frame index for non-scripted (cursor-less)
                             // animations; see TickObjectAnimation
    u8 bEnemyAttackPhase_candidate;  // 0xDC, TickFighterAttackAnimState_candidate's own
                             // multi-step sentinel: 0xff idle, 0/2/3/4 successive phases
                             // -- real compares it unsigned against 0xff, not as a signed -1
    u8 pad_DD[0x03];        // -> 0xE0
    void *pAnimTable;       // 0xE0, animation-frame table; the dword at +4 points to a
                             // per-frame entry array (frame count in its own +6 field). Same
                             // format as `LoadObjTileSheet`/LoadObjectAnimFrameCells's
                             // `pFrameData` -- see docs/formats/graphics.md
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
    u8 bAffineMode;         // 0xFF, mirrors bFlags_0xD1's low 2 bits (affine slot state)
    u8 pad_100[0x08];       // -> 0x108, two u16 pairs read by UpdateObjectOnscreenFlags as an
                             // onscreen bounding box; not yet decoded
    void *pEffectData;      // 0x108, direct pointer form of the same graphics-cache resource
                             // bGfxSlotAndFlags's upper nibble indexes (mutually exclusive with
                             // it -- see ClaimObjectEffectResource/BindEffectChannelSlot_candidate)
    u32 dwEffectFlags;      // 0x10C
    u16 wVramTileRow;       // 0x110, row passed to FreeObjectVramTileAllocation
    u16 wVramTileAllocId;   // 0x112, VRAM tile allocation id passed to
                             // FreeObjectVramTileAllocation (0xFFFF = none); set to 0xFFFF by
                             // ExitBattle when suspending a fighter for the Folio Universitas/
                             // Help resume path
    u8 pad_114[0x02];       // -> 0x116
    u8 bObjectPoolAuxSlot;  // 0x116, index into g_pObjectPoolAuxBuffer's 0x34-byte-stride
                             // records; see ReleaseObjectOffscreenVramTiles
    u8 pad_117[0x11];       // -> 0x128
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
extern void ReleaseObjectOffscreenVramTiles(Object *obj);
extern void ClaimObjectEffectResource(Object *obj);
extern void SetRoomObjectRecordPtr_candidate(Object *obj, u8 col, u8 row);
extern void SetObjectPosition(Object *obj, s32 x, s32 y);
extern void SnapObjectPosition(Object *obj, u32 x, u32 y);
extern void StartObjectMove(Object *obj, u32 x, u32 y, s16 mode);
extern void ReleaseObjectAffineSlot(Object *obj);
extern void SetObjectAffineTransform(Object *obj, u32 nScaleX, u32 nScaleY, s32 wAngle, s32 bMode);
extern void StartObjectAffineScaleTween(Object *obj, u32 nTargetScaleX, u32 nTargetScaleY, s32 nFrames);  // ramps nAffineScaleX/Y to the target over nFrames ticks (0 = set immediately)
extern void SetObjectFlippedX(Object *obj, s32 flip);
extern void SetObjectAnimData(Object *obj, void *a, void *b, s32 c);
extern void SetObjectAssetRecord(Object *obj, void *rec);
extern u8 AttachObjectEffectSlot_candidate(Object *obj, s32 effectPtr);
extern void AttachEffectOwner_candidate(Object *obj, void *pEffectData);  // 0x08030878
extern void sub_08001958(Object *obj, s32 v);
extern void sub_080039E8(Object *obj);
extern void sub_080039F8(Object *obj);
extern void sub_08003A0C(Object *obj);
extern void sub_08003A44(Object *obj, s32 a, s32 b, s32 c);
extern void sub_0801BCB0(void *linkedObject);
extern Object *CreateEffectScriptObject(s32 effectId, s32 kind);  // 0x08018BE0
