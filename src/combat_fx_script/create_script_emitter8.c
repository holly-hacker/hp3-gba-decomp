#include "types.h"
#include "combat_fx.h"
#include "combat_fx_script.h"
#include "particles.h"

// Attaches a still particle emitter to actor (as its pWindupParticleEmitter)
// for BSOP_CreateEmitter8, using palette g_aEffectActorAssets[assetIndex] and
// particle graphics entry entryIndex of pool poolIndex.
ParticleEmitter *CreateScriptEmitter8(Actor *actor, u8 unused, u8 spawnPeriod, u8 lifetimeBase,
                                      u8 spread, u8 spawnsPerPeriod, s32 assetIndex, u8 poolIndex,
                                      u8 entryIndex)
{
    actor->pWindupParticleEmitter = AllocParticleEmitter(g_aEffectActorAssets[assetIndex].pPalette,
                                                         poolIndex, entryIndex);
    if (actor->pWindupParticleEmitter != NULL)
    {
        actor->pWindupParticleEmitter->pTarget = actor;
        actor->pWindupParticleEmitter->wSpawnPeriod = spawnPeriod;
        actor->pWindupParticleEmitter->wLifetimeBase = lifetimeBase;
        actor->pWindupParticleEmitter->wSpread = spread;
        actor->pWindupParticleEmitter->bMode = ParticleModeStill;
        actor->pWindupParticleEmitter->bSpawnsPerPeriod = spawnsPerPeriod;
        actor->pWindupParticleEmitter->wFlags |= ParticleEmitterFlagPriorityFromTarget
                                               | ParticleEmitterFlagNoCollision
                                               | ParticleEmitterFlagAnimTicksFixed;
        return actor->pWindupParticleEmitter;
    }

    return NULL;
}
