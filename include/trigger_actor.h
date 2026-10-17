#pragma once

#include "types.h"
#include "actor.h"

// The actorType 3 static tile record returned by GetRoomActorStaticRecord.
typedef struct RoomActorRecordUnk3 {
    u32 dwActorType;
    s16 nPixelX;
    s16 nPixelY;
    u8 pad_8;
    u8 bVariant;   // 0x09, index into the asset and effect tables; 0-10
    u16 wArgA;     // 0x0A, scaled by 30 into Actor 0x60
    u8 bFlagC;     // 0x0C
    u8 bArgD;      // 0x0D
} RoomActorRecordUnk3;

extern Actor *SpawnSwitchActor(u8 bColumn, u8 bRow);
extern void sub_08044D24(Actor *pActor);
extern void sub_08044F54(Actor *pSelf, Actor *pOther);
extern const ActorGfxRecord g_aRoomSwitchSprites[5];                // ROM 0x0806C178 (US)
extern const ActorGfxRecord *const g_apRoomSwitchAssetRecords[12];  // ROM 0x0806C1A0 (US)
extern const void *const g_apRoomSwitchEffectData[12];               // ROM 0x0806C1D0 (US)
