#include "types.h"
#include "combat_fx.h"
#include "gen/graphics/battle.h"

// Attaches a one-shot emitter to actor: 12 particles fly from it toward
// anchor point 1 of the target fighter's sprite, placed at battle slot
// bScriptParam, arriving in 30 ticks.
ParticleEmitter *CreateBurstToTargetEmitter(Actor *actor, u8 poolIndex, u8 entryIndex)
{
    IntPoint anchor;

    actor->pWindupParticleEmitter = AllocParticleEmitter((const ObjPalette *)gBattleEffect003Palette,
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
    actor->pWindupParticleEmitter->bSpawnsPerPeriod = 12;
    actor->pWindupParticleEmitter->bParam43 = 0;
    actor->pWindupParticleEmitter->bAnimTicks = 3;
    actor->pWindupParticleEmitter->dwSpeed = 0x300;
    GetActorAnchor(g_pFightState->pFighters[g_effectStaging.bTargetIndex].pActor, 1, &anchor);
    actor->pWindupParticleEmitter->nVelX = FixedDivide(((g_awBattleSlotPosX_candidate[g_effectStaging.bScriptParam] + anchor.x) << 16) - actor->pos.x, 30 << 16);
    actor->pWindupParticleEmitter->nVelY = FixedDivide(((g_abBattleSlotPosY_candidate[g_effectStaging.bScriptParam] + anchor.y) << 16) - actor->pos.y, 30 << 16);
    return actor->pWindupParticleEmitter;
}
