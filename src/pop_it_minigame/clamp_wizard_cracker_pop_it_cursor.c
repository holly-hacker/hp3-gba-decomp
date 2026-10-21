#include "types.h"
#include "pop_it_minigame.h"

void ClampWizardCrackerPopItCursor(void)
{
    if (g_pWizardCrackerPopIt->nCursorColumn >= g_pWizardCrackerPopIt->nColumnCount)
        g_pWizardCrackerPopIt->nCursorColumn = g_pWizardCrackerPopIt->nColumnCount - 1;
    if (g_pWizardCrackerPopIt->nCursorColumn < 0)
        g_pWizardCrackerPopIt->nCursorColumn = 0;

    if (g_pWizardCrackerPopIt->nCursorRow >= g_pWizardCrackerPopIt->abColumnHeights[g_pWizardCrackerPopIt->nCursorColumn])
        g_pWizardCrackerPopIt->nCursorRow = g_pWizardCrackerPopIt->abColumnHeights[g_pWizardCrackerPopIt->nCursorColumn] - 1;
    if (g_pWizardCrackerPopIt->nCursorRow < 0)
        g_pWizardCrackerPopIt->nCursorRow = 0;
}
