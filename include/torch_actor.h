#pragma once

#include "types.h"
#include "actor.h"

// The actorType 11 static tile record returned by GetRoomActorStaticRecord.
typedef struct RoomActorRecordFlamePillar {
    u32 dwActorType;
    s16 nPixelX;
    s16 nPixelY;
    u16 wArg8;
    u16 wArgA;
    u8 abArgC[3];
} RoomActorRecordFlamePillar;

extern Actor *SpawnFlamePillarActor(u8 bColumn, u8 bRow);
extern void TickFlamePillarActor(Actor *pActor);
extern void IgniteFlamePillar(Actor *pActor);
extern void HandleFlamePillarTouch(Actor *pSelf, Actor *pOther);
extern s32 g_nFlamePillarSoundHandle;
extern const ActorGfxRecord g_aRoomFlamePillarSprites[3];
extern const ActorGfxRecord *const g_apRoomFlamePillarAnimFrames[3];
extern const void *const g_apRoomFlamePillarEffectData[3];
extern const u8 g_abRoomFlamePillarAnimData[22];
