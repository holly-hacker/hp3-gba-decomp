#include "types.h"
#include "combat_fx.h"
#include "combat_fx_script.h"
#include "particles.h"

// Attaches a particle emitter to actor (as its pWindupParticleEmitter) for
// BSOP_CreateEmitter12, using palette g_aEffectActorAssets[assetIndex] and
// particle graphics entry entryIndex of pool poolIndex. The emitter is
// released after duration ticks. A nonzero flag18 also sets the unread
// ParticleEmitterFlagUnused8 and ParticleEmitterFlagUnused10.
ParticleEmitter *CreateScriptEmitter12(Actor *actor, u8 mode, u8 lifetimeBase, u8 spread,
                                       u8 direction, u8 spawnsPerPeriod, u8 flag18,
                                       s32 assetIndex, u8 poolIndex, u8 entryIndex, u8 speed,
                                       u8 duration, u8 spawnPeriod)
{
    actor->pWindupParticleEmitter = AllocParticleEmitter(g_aEffectActorAssets[assetIndex].pPalette,
                                                         poolIndex, entryIndex);
    if (actor->pWindupParticleEmitter != NULL)
    {
        actor->pWindupParticleEmitter->pTarget = actor;
        actor->pWindupParticleEmitter->wSpawnPeriod = spawnPeriod;
        actor->pWindupParticleEmitter->wLifetimeBase = lifetimeBase;
        actor->pWindupParticleEmitter->wSpread = spread;
        actor->pWindupParticleEmitter->bMode = mode;
        actor->pWindupParticleEmitter->bDirection = direction;
        actor->pWindupParticleEmitter->bSpawnsPerPeriod = spawnsPerPeriod;
        actor->pWindupParticleEmitter->wDuration = duration;
        actor->pWindupParticleEmitter->wFlags = ParticleEmitterFlagPriorityFromTarget | ParticleEmitterFlagRelease;
        actor->pWindupParticleEmitter->dwSpeed = speed << 12;
        actor->pWindupParticleEmitter->wFlags |= ParticleEmitterFlagNoCollision;
        if (flag18)
            actor->pWindupParticleEmitter->wFlags
                |= ParticleEmitterFlagUnused8 | ParticleEmitterFlagUnused10;
        return actor->pWindupParticleEmitter;
    }

    return NULL;
}
