#pragma once

#include "types.h"
#include "actor.h"

// RoomActorType_WorldActor. bKind (0-82) selects the sprite, draw flags and
// collision behavior; the remaining record bytes become Actor bytes 0x62-0x68.
typedef struct RoomActorRecordWorldActor {
    u32 dwActorType;
    s16 nPixelX;
    s16 nPixelY;
    u8 pad_8[4];
    u8 bKind;      // 0x0C
    u8 bFacing;    // 0x0D
    u8 bBlocksPlayer;  // 0x0E
    u8 bPushable;  // 0x0F
    u8 bBreakable; // 0x10
    u8 b65;        // 0x11
    u8 b66;        // 0x12
    u8 pad_13;
    u8 bChainRow;  // 0x14
} RoomActorRecordWorldActor;

// Actor bytes 0x60-0x6A as written by SpawnWorldActor.
typedef struct WorldActorState {
    u8 b60;         // bit 1: the chain has run once
    u8 bKind;
    u8 bBlocksPlayer;  // HandlePlayerWorldActorCollision stops the player while intact
    u8 bPushable;   // Flipendo pushes it; slows to a stop
    u8 bBreakable;  // Flipendo breaks it, Reparo restores it; see BreakWorldActor
    u8 b65;
    u8 b66;
    u8 bBrokenFrame;  // animation frame before breaking, 0xFF while intact; +80 while
                      // Reparo restores it
    u8 bChainRow;   // RespawnGroupAndRunChain(0, bChainRow) when used; 0 = none
    u8 bActivated;  // kinds 44, 62, 68, 80: set once triggered
    u8 bNoPlatePress;  // Actor.modeState.actor.bNoPlatePress; always 0
} WorldActorState;

#define WORLD_ACTOR_STATE(pActor) ((WorldActorState *)&(pActor)->scriptState)

extern Actor *SpawnWorldActor(u8 bColumn, u8 bRow);
extern void TickWorldActor(Actor *pActor);
extern void TickWorldActorPlayerControl(Actor *pActor);
extern void HandleWorldActorSecondaryTouch(Actor *pSelf, Actor *pOther);
extern void HandleWorldActorTouch(Actor *pSelf, Actor *pOther);
extern void BreakWorldActor(Actor *pActor);
extern void InitWorldActorBreakEmitter(ParticleEmitter *pEmitter, Actor *pWorldActor);
extern const ActorGfxRecord g_aWorldActorSprites[80];             // ROM 0x0806C304 (US)
extern const ActorGfxRecord *const g_apWorldActorAnimFrames[91];  // ROM 0x0806C584 (US)
extern const void *const g_apWorldActorEffectData[91];            // ROM 0x0806C6F0 (US)
extern const s32 g_aWorldActorPushVelocity[8][2];                 // ROM 0x0806C85C (US)
extern const u32 g_adwWorldActorPushFacing[8];                    // ROM 0x0806C89C (US)
extern const ActorGfxRecord g_WorldActorParticleGfx0;             // ROM 0x0806C8BC (US)
extern const ActorGfxRecord g_WorldActorParticleGfx1;             // ROM 0x0806C8C4 (US)
extern const ActorGfxRecord g_WorldActorParticleGfx2;             // ROM 0x0806C8CC (US)
extern const ActorGfxRecord g_WorldActorParticleGfx3;             // ROM 0x0806C8D4 (US)
extern const ActorGfxRecord g_WorldActorParticleGfx4;             // ROM 0x0806C8DC (US)
extern const ActorGfxRecord g_WorldActorParticleGfx5;             // ROM 0x0806C8E4 (US)
extern const ActorGfxRecord g_WorldActorParticleGfx6;             // ROM 0x0806C8EC (US)
extern const u8 g_abWorldActorAnimData[91][90];                   // ROM 0x0806C8F4 (US)
extern const u8 g_abWorldActorFacingFrames[8];                    // ROM 0x0806E8F2 (US)
extern const u8 g_abWorldActorFacingAnimStart[8];                 // ROM 0x0806E8FA (US)

extern void SnapActorXToTileGrid(Actor *actor);
// Puts a world actor into its consumed state; used to restore a used switch.
extern void MarkRoomActorConsumed(Actor *pActor);
