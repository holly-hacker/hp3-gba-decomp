#include "types.h"
#include "actor.h"
#include "math.h"
#include "pop_it_minigame.h"

// Replaces each selected cracker with one in action state 4, which pops it
// after its selection delay.
void PopWizardCrackerPopItSelection(void)
{
    s32 i;
    Actor *pCracker;
    Actor *pPopping;
    s32 row;
    s32 column;

    g_pWizardCrackerPopIt->dwSelectedCount = 0;
    for (i = 0; i < ARRAY_COUNT(g_pWizardCrackerPopIt->apCrackers); i++)
    {
        pCracker = g_pWizardCrackerPopIt->apCrackers[i];
        if (pCracker != NULL && pCracker->dwStateTimer != 0)
        {
            pPopping = SpawnWizardCrackerPopItCracker(pCracker->wSubtype, pCracker->pos.x >> 16,
                                                      pCracker->pos.y >> 16);
            SetActorActionState(pPopping, 4);
            pPopping->dwStateTimer = pCracker->dwStateTimer;
            pPopping->wActionVariant = pCracker->wActionVariant;
            pCracker->dwFlags = (pCracker->dwFlags & ~ActorFlagVisible) | ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
            g_pWizardCrackerPopIt->apCrackers[i] = NULL;
            pCracker = pPopping;

            if (pCracker->wSubtype == WizardCrackerPopItKindWrapped)
            {
                if (g_pWizardCrackerPopIt->aKinds[pCracker->wSubtype].dwVariant == 0)
                    SetActorAnimFrame(pCracker, 0);
                else
                    SetActorAnimFrame(pCracker, 11);
            }
            else if (pCracker->wSubtype == WizardCrackerPopItKindTriangle)
            {
                SetActorAnimFrame(pCracker, 9);
            }
            else
            {
                SetActorAnimFrame(pCracker, 0);
            }

            row = iwramDivideSignedRemainder(pCracker->wActionVariant, WIZARD_CRACKER_POP_IT_COLUMNS, &column);
            g_pWizardCrackerPopIt->aabCells[column][row] = 0;
        }
    }
}
