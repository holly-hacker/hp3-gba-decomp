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
    u8 bPushable;  // 0x0F
    u8 bBreakable; // 0x10
    u8 b65;        // 0x11
    u8 b66;        // 0x12
    u8 pad_13;
    u8 bChainRow;  // 0x14
} RoomActorRecordProp;

// Actor bytes 0x60-0x6A as written by the type 5 constructor.
typedef struct RoomActorTriggerState {
    u8 b60;         // bit 1: the chain has run once
    u8 bKind;
    u8 b62;
    u8 bPushable;   // Flipendo pushes it; slows to a stop
    u8 bBreakable;  // Flipendo breaks it, Reparo restores it; see BreakPropActor
    u8 b65;
    u8 b66;
    u8 bBrokenFrame;  // animation frame before breaking, 0xFF while intact; +80 while
                      // Reparo restores it
    u8 bChainRow;   // RespawnGroupAndRunChain(0, bChainRow) when used; 0 = none
    u8 bActivated;  // kinds 44, 62, 68, 80: set once triggered
    u8 b6A;
} RoomActorTriggerState;

#define ROOM_ACTOR_TRIGGER_STATE(pActor) ((RoomActorTriggerState *)&(pActor)->scriptState)

extern Actor *SpawnPropActor(u8 bColumn, u8 bRow);
extern void TickPropActor(Actor *pActor);
extern void TickPropActorPlayerControl(Actor *pActor);
extern void HandlePropActorSecondaryTouch(Actor *pSelf, Actor *pOther);
extern void HandlePropActorTouch(Actor *pSelf, Actor *pOther);
extern void BreakPropActor(Actor *pActor);
extern void InitPropBreakEmitter(ParticleEmitter *pEmitter, Actor *pProp);
extern const ActorGfxRecord g_aRoomActorTriggerSprites[80];             // ROM 0x0806C304 (US)
extern const ActorGfxRecord *const g_apRoomActorTriggerAnimFrames[91];  // ROM 0x0806C584 (US)
extern const void *const g_apRoomActorTriggerEffectData[91];             // ROM 0x0806C6F0 (US)
extern const s32 g_aRoomActorTriggerPushVelocity[8][2];                  // ROM 0x0806C85C (US)
extern const u32 g_adwRoomActorTriggerPushFacing[8];                     // ROM 0x0806C89C (US)
extern const ActorGfxRecord g_RoomPropParticleGfx0;                 // ROM 0x0806C8BC (US)
extern const ActorGfxRecord g_RoomPropParticleGfx1;                 // ROM 0x0806C8C4 (US)
extern const ActorGfxRecord g_RoomPropParticleGfx2;                 // ROM 0x0806C8CC (US)
extern const ActorGfxRecord g_RoomPropParticleGfx3;                 // ROM 0x0806C8D4 (US)
extern const ActorGfxRecord g_RoomPropParticleGfx4;                 // ROM 0x0806C8DC (US)
extern const ActorGfxRecord g_RoomPropParticleGfx5;                 // ROM 0x0806C8E4 (US)
extern const ActorGfxRecord g_RoomPropParticleGfx6;                 // ROM 0x0806C8EC (US)
extern const u8 g_abRoomActorTriggerAnimData[91][90];                    // ROM 0x0806C8F4 (US)
extern const u8 g_abRoomActorTriggerFacingFrames[8];                     // ROM 0x0806E8F2 (US)
extern const u8 g_abRoomActorTriggerFacingAnimStart[8];                  // ROM 0x0806E8FA (US)

extern void SnapActorXToTileGrid(Actor *actor);
// Puts a type 5 actor into its consumed state; used to restore a used switch.
extern void MarkRoomActorConsumed(Actor *pActor);
