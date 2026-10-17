#pragma once

#include "types.h"
#include "actor.h"

// Room actor of tile actorType 8, a button that a spell presses to respawn a push
// puzzle's actors; see docs/formats/rooms.md.

// Static tile record of actorType 8, returned by GetRoomActorStaticRecord.
typedef struct RoomActorRecordUnk8 {
    u16 wActorType;
    u16 wUnk2;
    s16 nPixelX;
    s16 nPixelY;
    u8 bVariant;  // 0x08
    u8 abPairs[16];  // 0x09, eight {A, B} pairs, copied to Actor 0x60 (A) and 0x68 (B)
} RoomActorRecordUnk8;

extern Actor *SpawnPushResetButtonActor(u8 bColumn, u8 bRow);
extern void sub_08035664(Actor *pActor);
extern void sub_08035724(Actor *pSelf, Actor *pOther);
extern const ActorGfxRecord g_RoomActorUnk8Sprite;                    // ROM 0x080693CC (US)
extern const ActorGfxRecord *const g_apRoomActorUnk8AssetRecords[2];  // ROM 0x080693D4 (US)
extern const void *const g_apRoomActorUnk8EffectData[2];               // ROM 0x080693DC (US)

// Actor bytes 0x60-0x6F as written by the type 8 constructor.
typedef struct RoomActorUnk8State {
    u8 abA[8];
    u8 abB[8];
} RoomActorUnk8State;

#define ROOM_ACTOR_UNK8_STATE(pActor) ((RoomActorUnk8State *)&(pActor)->scriptState)
