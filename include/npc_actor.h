#pragma once

#include "types.h"
#include "actor.h"

typedef struct RoomActorRecordUnk6 {
    u32 dwActorType;
    s16 nPixelX;
    s16 nPixelY;
    u8 bKind;      // 0x08, index into the asset tables
    u8 bFacing;    // 0x09, stored halved
    u8 pad_A[2];
    union {
        u32 dwWord;
        u8 bFirst;
    } argC;        // 0x0C; bFirst goes to Actor 0x8C, bytes 1 and 2 are tested as a pair
} RoomActorRecordUnk6;

extern Actor *SpawnNpcActor(u8 bColumn, u8 bRow);
extern Actor *sub_0802F6C0(u32 characterId);
extern void sub_0802F7F0(Actor *pActor);
extern void sub_0802FCC0(Actor *pSelf, Actor *pOther);
extern Actor *SpawnShadowActor(Actor *pActor);
// Starts animation `animId` from the actor's animation table.
extern void SetActorAnimData_candidate(Actor *actor, u32 animId);

extern const u32 g_adwRoomActorUnk6FrameRows[110];      // ROM 0x08066E44 (US)
extern const ActorAssetRecord g_aActorTypeAssets[137];  // ROM 0x08066FFC (US), indexed by an actor kind
extern const u8 g_abRoomActorUnk6Frames[12][4];         // ROM 0x0806788C (US)
