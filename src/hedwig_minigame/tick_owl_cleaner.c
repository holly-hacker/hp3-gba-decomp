#include "types.h"
#include "actor.h"
#include "save.h"
#include "game_state.h"
#include "hedwig_minigame.h"

// Sweeps across the cage, turning every 60 ticks. After the first turn it
// lowers the Clean counter by 1 per tick and leaves once it is down to 9.
void TickOwlCleaner(Actor *pCleaner)
{
    if (pCleaner->dwStateTimer-- == 0)
    {
        pCleaner->dwStateTimer = 60;
        pCleaner->vel.x = -pCleaner->vel.x;
        pCleaner->wActionVariant = 1;
        if (g_saveStateBlock.owlCareKit.abCareCounters[1] <= 9)
            pCleaner->dwFlags |= ActorFlagPendingDestroy;
    }

    if (pCleaner->wActionVariant == 1)
    {
        if (g_saveStateBlock.owlCareKit.abCareCounters[1] <= 9)
        {
            g_saveStateBlock.owlCareKit.abCareCounters[1] = 0;
            pCleaner->dwFlags |= ActorFlagPendingDestroy;
        }
        else
            g_saveStateBlock.owlCareKit.abCareCounters[1]--;
    }
}
