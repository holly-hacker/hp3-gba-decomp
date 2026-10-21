#pragma once

#include "types.h"
#include "actor.h"

// Room actor of tile actorType 12, a platform that lifts the party.

// Static tile record of actorType 12, returned by GetRoomActorStaticRecord.
typedef struct RoomActorRecordRaisingPlatform {
    u16 wActorType;
    u16 wUnk2;
    s16 nPixelX;
    s16 nPixelY;
    u8 abArg8[3];
} RoomActorRecordRaisingPlatform;

extern Actor *SpawnRaisingPlatformActor(u8 bColumn, u8 bRow);
extern void TickRaisingPlatformActor(Actor *pActor);
extern void HandleRaisingPlatformTouch(Actor *pSelf, Actor *pOther);
extern const ActorGfxRecord g_RoomRaisingPlatformSprite;  // ROM 0x0806B7D4 (US)
extern const u8 g_abRoomRaisingPlatformAnimData[46];       // ROM 0x0806B7DC (US)

// Actor bytes 0x60-0x65 as set by the constructor from the record arguments.
typedef struct RaisingPlatformState {
    u32 dwInactive;         // 0x60, 1 until a Reparo spell effect hits it
    union __attribute__((packed)) {
        u16 wPair;          // tested as a whole: zero runs nothing
        struct __attribute__((packed)) {
            u8 bRespawnRow;
            u8 bChainRow;
        } rows;
    } finish;               // 0x64, RespawnGroupAndRunChain arguments run once the
                            // platform has lowered the party
} RaisingPlatformState;

#define RAISING_PLATFORM_STATE(pActor) ((RaisingPlatformState *)&(pActor)->scriptState)
