#pragma once

#include "types.h"
#include "actor.h"
#include "flipbook.h"

// The snapshot of the current room's non-default actors saved with each slot
// (g_pRoomActorStateBuffer, ROOM_ACTOR_STATE_BUFFER_SIZE bytes).
// CaptureRoomActorState fills it from the live actors and
// RestoreRoomActorState respawns each record's tile actor and writes the saved
// fields back. Most records start with the tile (column, row) of the actor's
// room record; the rest are copies of Actor fields.

// Actor bytes 0x60-0x7B (script state and per-mode state), copied as a block.
typedef struct { u32 adw[7]; } RoomActorScriptBlock;

typedef struct {
    u32 dwFlags;               // 0x00, without ActorFlagHasPaletteSlot
    s32 nMoveSpeed;            // 0x04
    u32 dwStateTimer;          // 0x08
    u16 wTimedMoveTicks;       // 0x0C
    u16 wActionVariant;        // 0x0E
    u8 abShadowTile[2];        // 0x10, room tiles of the linked actors; not restored
    u8 abLinkedTile[2];        // 0x12
    u8 abOwnerTile[2];         // 0x14
    u8 bFacing;                // 0x16
    u8 bActionState;           // 0x17
    u8 bActionSubState;        // 0x18
    u8 bRoomActorKind;         // 0x19
    u8 bFighterIndex;          // 0x1A
    u8 bTileCol;               // 0x1B
    u8 bTileRow;               // 0x1C
    ActorAnimState anim;       // 0x20
    u8 pad_34[0x0C];
    RoomActorScriptBlock script;  // 0x40
    u16 wMoveTargetX;          // 0x5C, pixels
    u16 wMoveTargetY;          // 0x5E
    u16 wPosX;                 // 0x60, pixels
    u16 wPosY;                 // 0x62
    FixedPoint vel;            // 0x64
} RoomActorDefaultRecord;

// RoomActorType_TriggerZone and RoomActorType_TriggerRect.
typedef struct {
    u8 bTileCol;               // 0x00
    u8 bTileRow;               // 0x01
    u8 pad_02;
    u8 bActionState;           // 0x03
    u32 dwFlags;               // 0x04
    u32 dwStateTimer;          // 0x08
} RoomActorTriggerZoneRecord;

// RoomActorType_WorldActor other than the switch kind.
typedef struct {
    u8 bTileCol;               // 0x00
    u8 bTileRow;               // 0x01
    u8 bActionSubState;        // 0x02
    u8 bDepthSortBias;         // 0x03
    u8 bBrokenFrame;           // 0x04
    u8 bScriptStateLow;        // 0x05
    u16 wTimedMoveTicks;       // 0x06
    u32 dwFlags;               // 0x08, without ActorFlagHasPaletteSlot
    ActorAnimState anim;       // 0x0C
    u16 wPosX;                 // 0x20, pixels
    u16 wPosY;                 // 0x22
    FixedPoint vel;            // 0x24
    FixedPoint accel;          // 0x2C
} RoomActorWorldActorRecord;

// RoomActorType_TileAnimation: the room tile animation at the actor's position.
typedef struct {
    u8 bTileCol;               // 0x00
    u8 bTileRow;               // 0x01
    RoomTileAnimation tileAnim;  // 0x04
} RoomActorTileAnimationRecord;

// RoomActorType_WorldActor, switch kind.
typedef struct {
    u8 bTileCol;
    u8 bTileRow;
    u8 bConsumed;              // ActorFlagWantsCollisionCheck was clear
} RoomActorSwitchRecord;

// RoomActorType_FlamePillar.
typedef struct {
    u8 bTileCol;
    u8 bTileRow;
    u8 bStateTimer;            // low byte of dwStateTimer, restored plus 1
    u8 bActionSubState;
} RoomActorFlamePillarRecord;

// An actor whose default state is restored by respawning it.
typedef struct {
    u8 bTileCol;
    u8 bTileRow;
} RoomActorTileRecord;

// A wandering monster; kept in memory only, not saved.
typedef struct {
    u16 wActorType;            // 0x00
    u16 wMonsterId;            // 0x02
    FixedPoint pos;            // 0x04
    FixedPoint moveTarget;     // 0x0C
    FixedPoint vel;            // 0x14
    u8 bFacing;                // 0x1C
    u8 bEncounterId;           // 0x1D
    u8 bEncounterVariant;      // 0x1E
    u8 bKind;                  // 0x1F
    u8 pad_20[4];
} RoomActorWanderingMonsterRecord;

#define ROOM_ACTOR_STATE_MAX_RECORDS 32
#define ROOM_ACTOR_STATE_MAX_PRESENCE_MARKERS 120
#define ROOM_ACTOR_STATE_MAX_WANDERING_MONSTERS 50

typedef struct {
    u8 bPlayerFacing;          // 0x00
    u8 bDefaultCount;          // 0x01: entries of aDefault
    u8 bTriggerZoneCount;      // 0x02
    u8 bWorldActorCount;       // 0x03
    u8 bTileAnimationCount;    // 0x04
    u8 bPresenceMarkerCount;   // 0x05
    u8 bWorldActorSwitchCount; // 0x06
    u8 bFlamePillarCount;      // 0x07
    u8 bWanderingMonsterCount; // 0x08: not serialized
    u8 bSwitchState;           // 0x09
    FixedPoint playerPos;      // 0x0C
    RoomActorDefaultRecord aDefault[ROOM_ACTOR_STATE_MAX_RECORDS];              // 0x14
    RoomActorTriggerZoneRecord aTriggerZone[ROOM_ACTOR_STATE_MAX_RECORDS];      // 0xD94
    RoomActorWorldActorRecord aWorldActor[ROOM_ACTOR_STATE_MAX_RECORDS];        // 0xF14
    RoomActorTileAnimationRecord aTileAnimation[ROOM_ACTOR_STATE_MAX_RECORDS];  // 0x1594
    RoomActorSwitchRecord aWorldActorSwitch[ROOM_ACTOR_STATE_MAX_RECORDS];      // 0x1714
    RoomActorFlamePillarRecord aFlamePillar[16];                                // 0x1794
    RoomActorTileRecord aPresenceMarker[ROOM_ACTOR_STATE_MAX_PRESENCE_MARKERS];  // 0x17D4
    RoomActorWanderingMonsterRecord aWanderingMonster[ROOM_ACTOR_STATE_MAX_WANDERING_MONSTERS];  // 0x19B4
} RoomActorStateBuffer;
