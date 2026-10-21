#include "types.h"
#include "input.h"
#include "modes.h"
#include "sound.h"
#include "pop_it_minigame.h"

void HandleWizardCrackerPopItCursorInput(void)
{
    u32 max;

    max = g_pWizardCrackerPopIt->abColumnHeights[g_pWizardCrackerPopIt->nCursorColumn];
    if (max != 0)
        max--;
    if (StepCursorUpDown((u32 *)&g_pWizardCrackerPopIt->nCursorRow, 0, max, 1, 0))
    {
        PlaySoundById(0);
        if (g_GameModeStackContext.dwModeState == WizardCrackerPopItStateSelect)
        {
            ClearWizardCrackerPopItSelection();
            SelectWizardCrackerPopItGroup(g_pWizardCrackerPopIt->nCursorColumn, g_pWizardCrackerPopIt->nCursorRow);
        }
    }

    max = g_pWizardCrackerPopIt->nColumnCount;
    if (max != 0)
        max--;
    if (StepCursorLeftRight((u32 *)&g_pWizardCrackerPopIt->nCursorColumn, 0, max, 1, 0))
    {
        PlaySoundById(0);
        if (g_pWizardCrackerPopIt->nCursorRow
            > g_pWizardCrackerPopIt->abColumnHeights[g_pWizardCrackerPopIt->nCursorColumn] - 1)
            g_pWizardCrackerPopIt->nCursorRow =
                g_pWizardCrackerPopIt->abColumnHeights[g_pWizardCrackerPopIt->nCursorColumn] - 1;
        if (g_GameModeStackContext.dwModeState == WizardCrackerPopItStateSelect)
        {
            ClearWizardCrackerPopItSelection();
            SelectWizardCrackerPopItGroup(g_pWizardCrackerPopIt->nCursorColumn, g_pWizardCrackerPopIt->nCursorRow);
        }
    }

    ClampWizardCrackerPopItCursor();
}
