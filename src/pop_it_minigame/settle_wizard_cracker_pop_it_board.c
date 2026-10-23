#include "types.h"
#include "actor.h"
#include "pop_it_minigame.h"

// Raises the crackers into the gaps a pop left, one row every 4 ticks, then
// closes empty columns. Returns 1 once everything has stopped.
u32 SettleWizardCrackerPopItBoard(void)
{
    s32 noneMoved;
    s32 column;
    u32 row;
    u32 cell;
    Actor *pActor;
    Actor *pNext;

    if (g_pWizardCrackerPopIt->bSettleRow == 7)
    {
        if (AreWizardCrackerPopItCrackersIdle())
        {
            RebuildWizardCrackerPopItGrid();
            ResetWizardCrackerPopItSettle();
            return 1;
        }
    }
    else if (g_pWizardCrackerPopIt->bSettleRow == 6)
    {
        if (AreWizardCrackerPopItCrackersIdle())
        {
            RebuildWizardCrackerPopItGrid();
            CloseWizardCrackerPopItEmptyColumns();
            g_pWizardCrackerPopIt->bSettleRow++;
        }
    }
    else if (g_pWizardCrackerPopIt->bSettleTimer-- <= 0)
    {
        // Rows with nothing to move are skipped within the same tick.
        noneMoved = 1;
        do
        {
            g_pWizardCrackerPopIt->bSettleTimer = 4;
            for (column = 0; column < WIZARD_CRACKER_POP_IT_COLUMNS; column++)
            {
                row = g_pWizardCrackerPopIt->bSettleRow;
                if (g_pWizardCrackerPopIt->aabCells[column][row] == 0)
                {
                    g_pWizardCrackerPopIt->abColumnGaps[column]++;
                }
                else if (g_pWizardCrackerPopIt->abColumnGaps[column] != 0)
                {
                    cell = column + row * WIZARD_CRACKER_POP_IT_COLUMNS;
                    noneMoved = 0;
                    for (pActor = (Actor *)g_ActiveActorListState.pTail; pActor != NULL; pActor = pNext)
                    {
                        pNext = (Actor *)pActor->node.pPrev;
                        if (pActor->wActorType == WizardCrackerPopItActorType_Cracker
                            && pActor->wActionVariant == cell)
                        {
                            SetActorActionState(pActor, 15);
                            pActor->accel.y = -0x10000;
                            pActor->moveTarget.y = pActor->pos.y
                                - ((g_pWizardCrackerPopIt->abColumnGaps[column] * 24) << 16);
                        }
                    }
                }
            }
            g_pWizardCrackerPopIt->bSettleRow++;
        } while (noneMoved && g_pWizardCrackerPopIt->bSettleRow != 6);
    }

    return 0;
}
