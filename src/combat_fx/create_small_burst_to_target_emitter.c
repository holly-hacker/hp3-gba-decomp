#include "types.h"
#include "combat_fx.h"
#include "gen/graphics/battle.h"

// As CreateBurstToTargetEmitter, with 2 particles and another palette.
ParticleEmitter *CreateSmallBurstToTargetEmitter(Actor *actor, u8 poolIndex, u8 entryIndex)
{
    IntPoint anchor;

    actor->pWindupParticleEmitter = AllocParticleEmitter((const ObjPalette *)gBattleEffect004Palette,
                                                         poolIndex, entryIndex);
    actor->pWindupParticleEmitter->pTarget = actor;
    actor->pWindupParticleEmitter->wSpawnPeriod = 0;
    actor->pWindupParticleEmitter->wDuration = 1;
    actor->pWindupParticleEmitter->wLifetimeBase = 20;
    actor->pWindupParticleEmitter->wLifetimeRange = 5;
    actor->pWindupParticleEmitter->wFlags = ParticleEmitterFlagRelease | ParticleEmitterFlagNoCollision
                                          | ParticleEmitterFlagPriorityFromTarget;
    actor->pWindupParticleEmitter->wSpread = 2;
    actor->pWindupParticleEmitter->wSpawnTimer = 1;
    actor->pWindupParticleEmitter->bMode = ParticleModeRandomSpeedVector;
    actor->pWindupParticleEmitter->bSpawnsPerPeriod = 2;
    actor->pWindupParticleEmitter->bParam43 = 0;
    actor->pWindupParticleEmitter->bAnimTicks = 3;
    actor->pWindupParticleEmitter->dwSpeed = 0x300;
    GetActorAnchor(g_pFightState->pFighters[g_effectStaging.bTargetIndex].pActor, 1, &anchor);
    actor->pWindupParticleEmitter->nVelX = FixedDivide(((g_awBattleSlotPosX_candidate[g_effectStaging.bScriptParam] + anchor.x) << 16) - actor->pos.x, 30 << 16);
    actor->pWindupParticleEmitter->nVelY = FixedDivide(((g_abBattleSlotPosY_candidate[g_effectStaging.bScriptParam] + anchor.y) << 16) - actor->pos.y, 30 << 16);
    return actor->pWindupParticleEmitter;
}
