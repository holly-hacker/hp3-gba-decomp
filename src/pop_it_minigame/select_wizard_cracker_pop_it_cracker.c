#include "types.h"
#include "actor.h"
#include "pop_it_minigame.h"

// Highlights the cracker in a cell; order delays its pop by 8 ticks a step.
void SelectWizardCrackerPopItCracker(s32 column, s32 row, u8 order)
{
    s32 i;
    u32 cell;

    cell = column + row * WIZARD_CRACKER_POP_IT_COLUMNS;
    for (i = 0; i < ARRAY_COUNT(g_pWizardCrackerPopIt->apCrackers); i++)
    {
        if (g_pWizardCrackerPopIt->apCrackers[i] != NULL && g_pWizardCrackerPopIt->apCrackers[i]->wActionVariant == cell)
        {
            g_pWizardCrackerPopIt->apCrackers[i]->oam.paletteNum =
                g_aWizardCrackerPopItPalettes[g_pWizardCrackerPopIt->apCrackers[i]->wCharacterId_candidate].bSelectedSlot;
            g_pWizardCrackerPopIt->apCrackers[i]->oam.objMode = 1;
            g_pWizardCrackerPopIt->apCrackers[i]->dwStateTimer = order * 8 + 1;
            return;
        }
    }
}
