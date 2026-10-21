#include "types.h"
#include "actor.h"
#include "math.h"
#include "mem.h"
#include "pop_it_minigame.h"

// Recomputes the cells and column heights from the crackers' positions.
void RebuildWizardCrackerPopItGrid(void)
{
    s32 i;
    Actor *pCracker;
    s32 column;
    s32 row;

    memset(g_pWizardCrackerPopIt->abColumnHeights, 0, sizeof(g_pWizardCrackerPopIt->abColumnHeights));
    memset(g_pWizardCrackerPopIt->aabCells, 0, sizeof(g_pWizardCrackerPopIt->aabCells));

    for (i = 0; i < ARRAY_COUNT(g_pWizardCrackerPopIt->apCrackers); i++)
    {
        pCracker = g_pWizardCrackerPopIt->apCrackers[i];
        if (pCracker != NULL)
        {
            column = iwramDivideSignedQuotient(pCracker->pos.x >> 16, 24);
            row = iwramDivideSignedQuotient(pCracker->pos.y >> 16, 24);
            pCracker->wActionVariant = row * WIZARD_CRACKER_POP_IT_COLUMNS + column;
            g_pWizardCrackerPopIt->aabCells[column][row] = WIZARD_CRACKER_POP_IT_CELL(pCracker->wCharacterId_candidate + 1);
            g_pWizardCrackerPopIt->abColumnHeights[column]++;
        }
    }
}
