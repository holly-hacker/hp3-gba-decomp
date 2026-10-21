#include "types.h"
#include "actor.h"
#include "pop_it_minigame.h"

// Moves the crackers left over the columns that emptied.
void CloseWizardCrackerPopItEmptyColumns(void)
{
    s32 columnCount;
    s32 i;
    Actor *pCracker;
    s32 x;
    s32 emptyColumns;
    u32 column;

    columnCount = 0;
    for (i = 0; i < WIZARD_CRACKER_POP_IT_COLUMNS; i++)
        if (g_pWizardCrackerPopIt->abColumnHeights[i] != 0)
            columnCount++;

    if (g_pWizardCrackerPopIt->nColumnCount != columnCount)
    {
        for (i = 0; i < ARRAY_COUNT(g_pWizardCrackerPopIt->apCrackers); i++)
        {
            pCracker = g_pWizardCrackerPopIt->apCrackers[i];
            if (pCracker != NULL)
            {
                x = pCracker->pos.x >> 16;
                emptyColumns = 0;
                for (column = 0; column < g_pWizardCrackerPopIt->nColumnCount; column++)
                    if (g_pWizardCrackerPopIt->abColumnHeights[column] == 0 && column * 24 < x)
                        emptyColumns++;

                SetActorActionState(pCracker, 15);
                StartActorMove(pCracker, pCracker->pos.x - ((emptyColumns * 24) << 16), pCracker->pos.y, 8);
            }
        }

        g_pWizardCrackerPopIt->nColumnCount = columnCount;
    }
}
