#pragma once

#include "types.h"
#include "actor.h"

// The actorType 11 static tile record returned by GetRoomActorStaticRecord.
typedef struct RoomActorRecordUnkB {
    u16 wActorType;
    u16 wUnk2;
    s16 nPixelX;
    s16 nPixelY;
    u16 wArg8;
    u16 wArgA;
    u8 abArgC[3];
} RoomActorRecordUnkB;

extern Actor *SpawnFlamePillarActor(u8 bColumn, u8 bRow);
extern void sub_08044960(Actor *pActor);
extern void sub_08044ADC(Actor *pSelf, Actor *pOther);
extern void GrantPickupMarkerItem(Actor *pActor);
extern const ActorGfxRecord g_aRoomFlamePillarSprites[3];             // ROM 0x0806C12C (US)
extern const ActorGfxRecord *const g_apRoomFlamePillarAnimFrames[3];  // ROM 0x0806C144 (US)
extern const void *const g_apRoomFlamePillarEffectData[3];             // ROM 0x0806C150 (US)
extern const u8 g_abRoomFlamePillarAnimData[22];                       // ROM 0x0806C15C (US)
