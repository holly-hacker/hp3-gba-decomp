#include "types.h"
#include "actor.h"
#include "pop_it_minigame.h"

void ClearWizardCrackerPopItSelection(void)
{
    s32 column;
    s32 row;
    Actor *pCracker;
    u32 cell;

    for (column = 0; column < WIZARD_CRACKER_POP_IT_COLUMNS; column++)
    {
        for (row = 0; row < WIZARD_CRACKER_POP_IT_ROWS; row++)
        {
            pCracker = g_pWizardCrackerPopIt->apCrackers[column * WIZARD_CRACKER_POP_IT_ROWS + row];
            cell = g_pWizardCrackerPopIt->aabCells[column][row] & 0xF;
            g_pWizardCrackerPopIt->aabCells[column][row] = cell | (cell << 4);
            if (pCracker != NULL)
            {
                pCracker->oam.objMode = 0;
                pCracker->dwFlags &= ~ActorFlagHasPaletteSlot;
                pCracker->oam.paletteNum = g_aWizardCrackerPopItPalettes[pCracker->wCharacterId_candidate].bIdleSlot;
                if (pCracker->bActionState == 0)
                    pCracker->dwStateTimer = 0;
            }
        }
    }

    g_pWizardCrackerPopIt->dwSelectedCount = 0;
}
