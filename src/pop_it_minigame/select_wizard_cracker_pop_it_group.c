#include "types.h"
#include "pop_it_minigame.h"

// Selects the cracker group at a cell; a lone cracker is not selected.
void SelectWizardCrackerPopItGroup(s32 column, s32 row)
{
    u32 kind;

    kind = g_pWizardCrackerPopIt->aabCells[column][row] >> 4;
    if (kind != 0)
    {
        FloodSelectWizardCrackerPopItGroup(column, row, kind, 0);
        if (g_pWizardCrackerPopIt->dwSelectedCount <= 1)
            ClearWizardCrackerPopItSelection();
    }
}
