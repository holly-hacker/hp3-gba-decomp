#pragma once

#include "types.h"
#include "actor.h"

// Scripted trigger actor. bKind (0-82) selects the sprite, draw flags and
// collision behavior; the remaining record bytes become Actor bytes 0x62-0x68.
typedef struct RoomActorRecordProp {
    u32 dwActorType;
    s16 nPixelX;
    s16 nPixelY;
    u8 pad_8[4];
    u8 bKind;      // 0x0C
    u8 bFacing;    // 0x0D
    u8 b62;        // 0x0E
    u8 b63;        // 0x0F
    u8 b64;        // 0x10
    u8 b65;        // 0x11
    u8 b66;        // 0x12
    u8 pad_13;
    u8 b68;        // 0x14
} RoomActorRecordProp;

// Actor bytes 0x60-0x6A as written by the type 5 constructor.
typedef struct RoomActorTriggerState {
    u8 b60;
    u8 bKind;
    u8 b62;
    u8 b63;
    u8 b64;
    u8 b65;
    u8 b66;
    u8 b67;
    u8 b68;
    u8 b69;
    u8 b6A;
} RoomActorTriggerState;

#define ROOM_ACTOR_TRIGGER_STATE(pActor) ((RoomActorTriggerState *)&(pActor)->scriptState)

extern Actor *SpawnPropActor(u8 bColumn, u8 bRow);
extern void sub_08045ECC(Actor *pActor);
extern void sub_0804651C(Actor *pSelf, Actor *pOther);
extern void sub_080465D4(Actor *pSelf, Actor *pOther);
extern const ActorGfxRecord g_aRoomActorTriggerSprites[80];             // ROM 0x0806C304 (US)
extern const ActorGfxRecord *const g_apRoomActorTriggerAnimFrames[91];  // ROM 0x0806C584 (US)
extern const void *const g_apRoomActorTriggerEffectData[91];             // ROM 0x0806C6F0 (US)
extern const s32 g_aRoomActorTriggerPushVelocity[8][2];                  // ROM 0x0806C85C (US)
extern const u32 g_adwRoomActorTriggerPushFacing[8];                     // ROM 0x0806C89C (US)
extern const ActorGfxRecord g_aRoomActorTriggerEffectSprites[7];        // ROM 0x0806C8BC (US)
extern const u8 g_abRoomActorTriggerAnimData[91][90];                    // ROM 0x0806C8F4 (US)
extern const u8 g_abRoomActorTriggerFacingFrames[8];                     // ROM 0x0806E8F2 (US)
extern const u8 g_abRoomActorTriggerFacingAnimStart[8];                  // ROM 0x0806E8FA (US)

extern void SnapActorXToTileGrid(Actor *actor);
// Puts a type 5 actor into its consumed state; used to restore a used switch.
extern void MarkRoomActorConsumed(Actor *pActor);
