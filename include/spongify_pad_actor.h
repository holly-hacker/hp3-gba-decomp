#pragma once

#include "types.h"
#include "actor.h"
#include "math.h"
#include "particles.h"

// Room actor of tile actorType 10, a Spongify pad that launches the party to a
// target point; see docs/formats/rooms.md.

// Static tile record of actorType 10, returned by GetRoomActorStaticRecord.
typedef struct RoomActorRecordSpongifyPad {
    u16 wActorType;
    u16 wUnk2;
    s16 nPixelX;
    s16 nPixelY;
    s16 nArg8;
    s16 nArgA;
    u8 bVariant;  // 0x0C
    u8 abArgD[2];
} RoomActorRecordSpongifyPad;

// Actor bytes 0x60-0x6D as set by the constructor from the record arguments.
typedef struct SpongifyPadState {
    IntPoint target;  // 0x60, pixels: where the party lands
    u32 dwArmed;      // 0x68, 1 from a Spongify effect hit until the player steps on it
    u8 bRespawnRow;   // 0x6C, RespawnGroupAndRunChain arguments run on landing
    u8 bChainRow;     // 0x6D
} SpongifyPadState;

#define SPONGIFY_PAD_STATE(pActor) ((SpongifyPadState *)&(pActor)->scriptState)

extern Actor *SpawnSpongifyPadActor(u8 bColumn, u8 bRow);
extern void TickSpongifyPadActor(Actor *pActor);
extern void HandleSpongifyPadTouch(Actor *pSelf, Actor *pOther);
extern void TickSpongifyPadEffect(Actor *pEffect);
extern void InitSpongifyPadParticleEmitter0(ParticleEmitter *pEmitter, Actor *pEffect);
extern void InitSpongifyPadParticleEmitter1(ParticleEmitter *pEmitter, Actor *pEffect);
extern void SpawnSpongifyPadEffect(Actor *pPad, Actor *pPlayer);
// [3] is the effect sprite of SpawnSpongifyPadEffect.
extern const ActorGfxRecord g_aRoomSpongifyPadSprites[4];             // ROM 0x0806B8DC (US)
extern const ActorGfxRecord *const g_apRoomSpongifyPadAnimFrames[3];  // ROM 0x0806B8FC (US)
extern const void *const g_apRoomSpongifyPadEffectData[3];             // ROM 0x0806B908 (US)
extern const u8 g_abRoomSpongifyPadAnimData[30];                       // ROM 0x0806B914 (US)
extern const ActorGfxRecord g_RoomSpongifyPadParticleGfx0;             // ROM 0x0806B934 (US)
extern const ActorGfxRecord g_RoomSpongifyPadParticleGfx1;             // ROM 0x0806B93C (US)
