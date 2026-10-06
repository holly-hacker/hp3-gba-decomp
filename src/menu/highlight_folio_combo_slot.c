#include "types.h"
#include "divide.h"
#include "game/game_modes.h"
#include "menu/folio_universitas.h"

// Dims the combo slots, then lights the one the cursor is on.
void HighlightFolioComboSlot(void)
{
    s32 selected;
    u32 i;

    if (g_GameModeStackContext.dwCurrentGameModeArg1 != FolioUniversitasPickCombo)
    {
        iwramDivideSignedRemainder(g_FolioUniversitasState.dwSlot, 3, &selected);

        for (i = 0; i < 3; i++)
        {
            if (g_FolioUniversitasState.aComboSlots[i].pCard != NULL)
                g_FolioUniversitasState.aComboSlots[i].pCard->oam.objMode = 1;
            if (g_FolioUniversitasState.aComboSlots[i].pCount != NULL)
                g_FolioUniversitasState.aComboSlots[i].pCount->oam.objMode = 1;
        }

        if (g_FolioUniversitasState.aComboSlots[selected].pCard != NULL)
            g_FolioUniversitasState.aComboSlots[selected].pCard->oam.objMode = 0;
        if (g_FolioUniversitasState.aComboSlots[selected].pCount != NULL)
            g_FolioUniversitasState.aComboSlots[selected].pCount->oam.objMode = 0;

        if (g_FolioUniversitasState.dwSlot == 9 || g_FolioUniversitasState.dwCategory == 5)
        {
            if (g_FolioUniversitasState.aComboSlots[1].pCard != NULL)
                g_FolioUniversitasState.aComboSlots[1].pCard->oam.objMode = 0;
            if (g_FolioUniversitasState.aComboSlots[1].pCount != NULL)
                g_FolioUniversitasState.aComboSlots[1].pCount->oam.objMode = 0;
        }
    }
}
