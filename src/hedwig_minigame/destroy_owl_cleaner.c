#include "types.h"
#include "actor.h"
#include "particles.h"
#include "hedwig_minigame.h"

void DestroyOwlCleaner(Actor *pCleaner)
{
    g_OwlCareKitScreen.pCleaner = NULL;
    if (pCleaner != NULL)
    {
        pCleaner->pWindupParticleEmitter = NULL;
        FreeAllParticles();
        ReleaseParticleGfx(1, 1);
    }
}
