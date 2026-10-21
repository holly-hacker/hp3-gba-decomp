#include "types.h"
#include "actor.h"
#include "random.h"
#include "pop_it_minigame.h"

// Restarts the kind's timer and sets its crackers' animation frame counters.
void AnimateWizardCrackerPopItKind(u32 kind, u32 animCounter)
{
    s32 i;

    g_pWizardCrackerPopIt->aKinds[kind].nTimer = Mt19937RandRange(40, 70);
    for (i = 0; i < ARRAY_COUNT(g_pWizardCrackerPopIt->apCrackers); i++)
        if (g_pWizardCrackerPopIt->apCrackers[i] != NULL && g_pWizardCrackerPopIt->apCrackers[i]->wCharacterId_candidate == kind)
            g_pWizardCrackerPopIt->apCrackers[i]->anim.bAnimFrameCounter = animCounter;
}
