#pragma once

#include "types.h"
#include "actor.h"

// Per-tile room actor constructors, selected by the u16 actorType at +8 of a
// tile record; see docs/formats/rooms.md. The caller stores the returned
// actor in the record and sets its tile column (+0x10) and row (+0x11).
typedef Actor *(*RoomActorConstructor)(u8 bColumn, u8 bRow);

#define ROOM_ACTOR_TYPE_COUNT 14

// Actor bytes 0x60-0x6D as word-sized state, written by the type 10 and 12 constructors.
typedef struct RoomActorWordState {
    s32 n60;
    s32 n64;
    s32 n68;
    u8 b6C;
    u8 b6D;
    u8 pad_6E;
    u8 b6F;
    u8 b70;
} RoomActorWordState;

#define ROOM_ACTOR_WORD_STATE(pActor) ((RoomActorWordState *)&(pActor)->scriptState)

// Types 2 and 13 (doors); see docs/formats/rooms.md.
typedef struct RoomActorDoorRecord {
    u32 dwActorType;
    s16 nPixelX;
    s16 nPixelY;
    u8 bHalfWidth;        // 0x08, collision box extents
    u8 bHalfHeight;       // 0x09
    u8 bExitParam;        // 0x0A, the destination's entry id
    u8 bDestinationRoom;  // 0x0B
    u8 bChain;            // 0x0C, runs instead of leaving when nonzero
    u8 bRequireAPress;    // 0x0D
} RoomActorDoorRecord;

// Shared by types 4 and 7; differ only in where the fields sit in the record.
typedef struct RoomActorRecordUnk4 {
    u32 dwActorType;
    s16 nPixelX;
    s16 nPixelY;
    u8 bHalfWidth;   // 0x08
    u8 bHalfHeight;  // 0x09
    u16 wArgA;       // 0x0A, scaled by 30 into Actor 0x60
    u8 bKind;        // 0x0C
    u8 bArgD;        // 0x0D
} RoomActorRecordUnk4;

typedef struct RoomActorRecordUnk7 {
    u32 dwActorType;
    s16 nPixelX;
    s16 nPixelY;
    u8 bLeft;        // 0x08
    u8 bTop;         // 0x09
    u8 bRight;       // 0x0A
    u8 bBottom;      // 0x0B
    u16 wArgC;       // 0x0C, scaled by 30 into Actor 0x60
    u8 bKind;        // 0x0E
    u8 bArgF;        // 0x0F
} RoomActorRecordUnk7;

typedef struct RoomActorRecordUnk1 {
    u32 dwActorType;
    s16 nPixelX;
    s16 nPixelY;
    u8 bAnimId;     // 0x08
    u8 bFlag;       // 0x09, nonzero: ResumeRoomTileAnimation, zero: HaltRoomTileAnimation
} RoomActorRecordUnk1;
