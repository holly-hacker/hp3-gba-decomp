#include "types.h"
#include "combat_fx.h"
#include "gen/graphics/battle.h"

// Attaches a one-shot emitter to actor: 20 particles fly from it in
// random directions.
ParticleEmitter *CreateRandomBurstEmitter(Actor *actor, u8 poolIndex, u8 entryIndex)
{
    actor->pWindupParticleEmitter = AllocParticleEmitter((const ObjPalette *)gBattleEffect003Palette,
                                                         poolIndex, entryIndex);
    if (actor->pWindupParticleEmitter != NULL)
    {
        actor->pWindupParticleEmitter->pTarget = actor;
        actor->pWindupParticleEmitter->wSpawnPeriod = 0;
        actor->pWindupParticleEmitter->wDuration = 1;
        actor->pWindupParticleEmitter->wLifetimeBase = 10;
        actor->pWindupParticleEmitter->wSpread = 5;
        actor->pWindupParticleEmitter->bMode = ParticleModeRandomDirection;
        actor->pWindupParticleEmitter->bSpawnsPerPeriod = 20;
        actor->pWindupParticleEmitter->wFlags = ParticleEmitterFlagRelease | ParticleEmitterFlagNoCollision
                                              | ParticleEmitterFlagPriorityFromTarget;
        return actor->pWindupParticleEmitter;
    }

    return NULL;
}
