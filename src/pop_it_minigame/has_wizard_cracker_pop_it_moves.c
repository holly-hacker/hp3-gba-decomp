#include "types.h"
#include "pop_it_minigame.h"

// Returns 1 while some cracker has a neighbor of its kind.
u32 HasWizardCrackerPopItMoves(void)
{
    s32 column;
    s32 row;
    u8 cell;

    for (column = 0; column < g_pWizardCrackerPopIt->nColumnCount; column++)
    {
        for (row = 0; row < g_pWizardCrackerPopIt->abColumnHeights[column]; row++)
        {
            cell = g_pWizardCrackerPopIt->aabCells[column][row];
            if (column > 0 && g_pWizardCrackerPopIt->aabCells[column - 1][row] == cell)
                return 1;
            if (column < g_pWizardCrackerPopIt->nColumnCount - 1
                && g_pWizardCrackerPopIt->aabCells[column + 1][row] == cell)
                return 1;
            if (row > 0 && g_pWizardCrackerPopIt->aabCells[column][row - 1] == cell)
                return 1;
            if (row < g_pWizardCrackerPopIt->abColumnHeights[column] - 1
                && g_pWizardCrackerPopIt->aabCells[column][row + 1] == cell)
                return 1;
        }
    }

    return 0;
}
