#include "types.h"
#include "pop_it_minigame.h"

// Selects the cell and, recursively, its neighbors holding the same kind
// (cell high nibble), each one order step later.
void FloodSelectWizardCrackerPopItGroup(s32 column, s32 row, u8 kind, u8 order)
{
    u32 cellKind;

    cellKind = g_pWizardCrackerPopIt->aabCells[column][row] >> 4;
    if (cellKind == kind)
    {
        SelectWizardCrackerPopItCracker(column, row, order);
        g_pWizardCrackerPopIt->dwSelectedCount++;
        order++;
        g_pWizardCrackerPopIt->aabCells[column][row] >>= 4;

        if (column != 0)
            FloodSelectWizardCrackerPopItGroup(column - 1, row, kind, order);
        if (column < g_pWizardCrackerPopIt->nColumnCount - 1)
            FloodSelectWizardCrackerPopItGroup(column + 1, row, kind, order);
        if (row != 0)
            FloodSelectWizardCrackerPopItGroup(column, row - 1, kind, order);
        if (row < g_pWizardCrackerPopIt->abColumnHeights[column] - 1)
            FloodSelectWizardCrackerPopItGroup(column, row + 1, kind, order);
    }
}
