#include "types.h"
#include "graphics/graphics.h"
#include "graphics/object.h"
#include "mt19937.h"

// Advances one emitter by a frame: spawns particles every wSpawnPeriod + 1 ticks (up to
// bSpawnsPerPeriod attempts), and releases the emitter when its target is being destroyed
// or, with ParticleEmitterFlagRelease, once wDuration has run out.
void TickParticleEmitter(ParticleEmitter *emitter)
{
    u32 attempt;

    if (!(emitter->wFlags & ParticleEmitterFlagSkipTick))
    {
        if (emitter->wSpawnTimer++ >= emitter->wSpawnPeriod)
        {
            emitter->wSpawnTimer = 0;
            for (attempt = 0; attempt < emitter->bSpawnsPerPeriod; attempt++)
            {
                if (g_wActiveParticleCount > 0x3E)
                    continue;
                if (g_bParticleSpawnBlocked)
                    continue;
                if (emitter->wFlags & ParticleEmitterFlagSpawnDisabled)
                    continue;
                if (!(emitter->pTarget->dwFlags & ObjectFlagOnscreenForTileAlloc)
                    && !(emitter->wFlags & ParticleEmitterFlagScreenPosition))
                    continue;

                if (!(emitter->wFlags & ParticleEmitterFlagSpawnRoll))
                    SpawnParticle(emitter);
                else if (Mt19937RandMax2(emitter->wSpawnRollMax) < emitter->wSpawnRollThreshold)
                    SpawnParticle(emitter);
            }
        }
    }

    if ((emitter->pTarget->dwFlags & ObjectFlagPendingDestroy)
        || ((emitter->wFlags & ParticleEmitterFlagRelease) && --emitter->wDuration == 0xFFFF))
        FreeParticleEmitter(emitter);
}
