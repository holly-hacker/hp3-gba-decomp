#pragma once

#include "types.h"
#include "actor.h"

// Room actor of tile actorType 10, a Spongify pad that launches the party to a
// target point; see docs/formats/rooms.md.

// Static tile record of actorType 10, returned by GetRoomActorStaticRecord.
typedef struct RoomActorRecordUnkA {
    u16 wActorType;
    u16 wUnk2;
    s16 nPixelX;
    s16 nPixelY;
    s16 nArg8;
    s16 nArgA;
    u8 bVariant;  // 0x0C
    u8 abArgD[2];
} RoomActorRecordUnkA;

extern Actor *SpawnSpongifyPadActor(u8 bColumn, u8 bRow);
extern void sub_08040114(Actor *pActor);
extern void sub_08040358(Actor *pSelf, Actor *pOther);
// [3] is the spell effect sprite of sub_08040680.
extern const ActorGfxRecord g_aRoomSpongifyPadSprites[4];             // ROM 0x0806B8DC (US)
extern const ActorGfxRecord *const g_apRoomSpongifyPadAnimFrames[3];  // ROM 0x0806B8FC (US)
extern const void *const g_apRoomSpongifyPadEffectData[3];             // ROM 0x0806B908 (US)
extern const u8 g_abRoomSpongifyPadAnimData[30];                       // ROM 0x0806B914 (US)
