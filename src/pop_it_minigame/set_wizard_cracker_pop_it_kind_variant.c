#include "types.h"
#include "actor.h"
#include "pop_it_minigame.h"

// Sets the kind's timer and, unless 0xFF, its variant, and restarts the
// idle animation of its crackers.
void SetWizardCrackerPopItKindVariant(u32 kind, u32 variant, s32 timer)
{
    s32 i;
    Actor *pCracker;

    g_pWizardCrackerPopIt->aKinds[kind].nTimer = timer;
    if (variant != 0xFF)
        g_pWizardCrackerPopIt->aKinds[kind].dwVariant = variant;

    for (i = 0; i < ARRAY_COUNT(g_pWizardCrackerPopIt->apCrackers); i++)
    {
        pCracker = g_pWizardCrackerPopIt->apCrackers[i];
        if (pCracker != NULL && pCracker->wSubtype == kind)
        {
            SetWizardCrackerPopItCrackerAnim(pCracker, kind);
            pCracker->anim.bAnimFrameCounter = 3;
        }
    }
}
