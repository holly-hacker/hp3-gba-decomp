#pragma once

#include "types.h"
#include "actor.h"

// Room actor of tile actorType 12, a platform that lifts the party; see
// docs/formats/rooms.md.

// Static tile record of actorType 12, returned by GetRoomActorStaticRecord.
typedef struct RoomActorRecordUnkC {
    u16 wActorType;
    u16 wUnk2;
    s16 nPixelX;
    s16 nPixelY;
    u8 abArg8[3];
} RoomActorRecordUnkC;

extern Actor *SpawnRaisingPlatformActor(u8 bColumn, u8 bRow);
extern void sub_0803B71C(Actor *pActor);
extern void sub_0803BA18(Actor *pSelf, Actor *pOther);
extern const ActorGfxRecord g_RoomRaisingPlatformSprite;  // ROM 0x0806B7D4 (US)
extern const u8 g_abRoomRaisingPlatformAnimData[46];       // ROM 0x0806B7DC (US)
