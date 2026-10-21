#include "types.h"
#include "actor.h"
#include "particles.h"
#include "hedwig_minigame.h"

void AttachOwlCleanerEmitter(Actor *pCleaner, u8 spawnPeriod, u8 lifetimeBase, u8 spread,
                             u8 spawnsPerPeriod, u8 pool, u8 entry)
{
    pCleaner->pWindupParticleEmitter = AllocParticleEmitter(g_OwlCareCleanerSparkles.pPalette, pool, entry);
    if (pCleaner->pWindupParticleEmitter != NULL)
    {
        pCleaner->pWindupParticleEmitter->pTarget = pCleaner;
        pCleaner->pWindupParticleEmitter->wSpawnPeriod = spawnPeriod;
        pCleaner->pWindupParticleEmitter->wLifetimeBase = lifetimeBase;
        pCleaner->pWindupParticleEmitter->wSpread = spread;
        pCleaner->pWindupParticleEmitter->bMode = ParticleModeRandomVelocity;
        pCleaner->pWindupParticleEmitter->bSpawnsPerPeriod = spawnsPerPeriod;
        pCleaner->pWindupParticleEmitter->wFlags |= ParticleEmitterFlagAnimTicksFixed | ParticleEmitterFlagNoCollision
                                                  | ParticleEmitterFlagPriorityFromTarget;
        pCleaner->pWindupParticleEmitter->abVelRange[0] = -2;
        pCleaner->pWindupParticleEmitter->abVelRange[1] = 2;
        pCleaner->pWindupParticleEmitter->abVelRange[2] = 0;
        pCleaner->pWindupParticleEmitter->abVelRange[3] = 0;
        pCleaner->pWindupParticleEmitter->wParam38 = 0x200;
    }
}
