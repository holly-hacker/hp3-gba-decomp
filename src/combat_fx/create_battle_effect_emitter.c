#include "types.h"
#include "combat_fx.h"

// Attaches a random-velocity particle emitter to actor (as its
// pWindupParticleEmitter), using palette g_aEffectActorAssets[assetIndex]
// and particle graphics entry entryIndex of pool poolIndex. Particles take
// their X velocity from velMinX..velMaxX and Y from velMinY..velMaxY. A
// nonzero duration releases the emitter after that many ticks, and a
// nonzero anchor spawns at anchor point anchor - 1 of the actor's frame.
ParticleEmitter *CreateBattleEffectEmitter(Actor *actor, u8 unused, u8 spawnPeriod,
                                           u8 lifetimeBase, u8 spread, u8 spawnsPerPeriod,
                                           u8 velMinX, u8 velMaxX, u8 velMinY, u8 velMaxY,
                                           u8 param38, u8 poolIndex, u8 entryIndex,
                                           s32 assetIndex, u8 duration, s32 fixedAnimTicks,
                                           u8 anchor)
{
    actor->pWindupParticleEmitter = AllocParticleEmitter(g_aEffectActorAssets[assetIndex].pPalette,
                                                         poolIndex, entryIndex);
    if (actor->pWindupParticleEmitter != NULL)
    {
        actor->pWindupParticleEmitter->pTarget = actor;
        actor->pWindupParticleEmitter->wSpawnPeriod = spawnPeriod;
        actor->pWindupParticleEmitter->wLifetimeBase = lifetimeBase;
        actor->pWindupParticleEmitter->wSpread = spread;
        actor->pWindupParticleEmitter->bMode = ParticleModeRandomVelocity;
        actor->pWindupParticleEmitter->bSpawnsPerPeriod = spawnsPerPeriod;
        actor->pWindupParticleEmitter->wFlags |= ParticleEmitterFlagPriorityFromTarget | ParticleEmitterFlagNoCollision;
        if (fixedAnimTicks)
            actor->pWindupParticleEmitter->wFlags |= ParticleEmitterFlagAnimTicksFixed;
        if (anchor)
        {
            actor->pWindupParticleEmitter->wFlags |= ParticleEmitterFlagAnchorPosition;
            actor->pWindupParticleEmitter->bParam43 = anchor - 1;
        }
        actor->pWindupParticleEmitter->abVelRange[0] = velMinX;
        actor->pWindupParticleEmitter->abVelRange[1] = velMaxX;
        actor->pWindupParticleEmitter->abVelRange[2] = velMinY;
        actor->pWindupParticleEmitter->abVelRange[3] = velMaxY;
        actor->pWindupParticleEmitter->wParam38 = param38 << 8;
        if (duration)
        {
            actor->pWindupParticleEmitter->wDuration = duration;
            actor->pWindupParticleEmitter->wFlags |= ParticleEmitterFlagRelease;
        }
        return actor->pWindupParticleEmitter;
    }

    return NULL;
}
