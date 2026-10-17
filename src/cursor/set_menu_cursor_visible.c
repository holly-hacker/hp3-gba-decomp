#include "types.h"
#include "actor.h"
#include "cursor.h"
#include "particles.h"

// Shows or hides a cursor; for the list cursor (kind 4) also stops or resumes
// its sparkles, clearing the ones already spawned when hiding.
void SetMenuCursorVisible(Actor *pActor, u32 visible)
{
    if (visible == 1)
        pActor->dwFlags |= ActorFlagVisible;
    else
        pActor->dwFlags &= ~ActorFlagVisible;

    if (pActor->wActorType == 4)
    {
        if (visible == 1)
        {
            g_pMenuCursorEmitter->wFlags &= ~ParticleEmitterFlagSpawnDisabled;
        }
        else
        {
            FreeAllParticles();
            g_pMenuCursorEmitter->wFlags |= ParticleEmitterFlagSpawnDisabled;
        }
    }
}
