#include "types.h"
#include "actor.h"
#include "particles.h"
#include "save.h"
#include "game_state.h"
#include "hedwig_minigame.h"

// The Clean action: sends a sparkle sweeping across the cage, or returns 0
// when the Clean counter is already low.
u32 StartOwlCleaning(void)
{
    Actor *pCleaner = NULL;

    if (g_saveStateBlock.owlCareKit.abCareCounters[1] <= 9)
    {
        g_saveStateBlock.owlCareKit.abCareCounters[1] = 0;
        return 0;
    }

    pCleaner = SpawnActor(15, 250, 30, NULL);
    if (pCleaner != NULL)
    {
        pCleaner->dwStateTimer = 60;
        pCleaner->pfnTick = TickOwlCleaner;
        pCleaner->pfnDestructor = DestroyOwlCleaner;
        pCleaner->dwFlags &= ~ActorFlagVisible;
        pCleaner->wActionVariant = 0;
        pCleaner->vel.x = -4 << 16;
        LoadParticleGfx(1, 1, &g_OwlCareCleanerSparkles);
        AttachOwlCleanerEmitter(pCleaner, 1, 34, 16, 1, 1, 1);
    }

    g_OwlCareKitScreen.pCleaner = pCleaner;
    return 1;
}
