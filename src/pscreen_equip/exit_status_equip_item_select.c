#include "hw/io_regs.h"
#include "default_menu.h"
#include "pscreen_equip.h"
#include "items.h"

void ExitStatusEquipItemSelect(void)
{
    BG_PLTT[4] = g_StatusEquipItemSelect.awSavedPalette[0];
    BG_PLTT[5] = g_StatusEquipItemSelect.awSavedPalette[1];
    BG_PLTT[6] = g_StatusEquipItemSelect.awSavedPalette[2];

    if (g_StatusEquipItemSelect.dwItemListOpen != 0)
        CloseItemList();

    ExitMenuScreen();
    FreeAllActors(&g_ActiveActorListState.pHead);
}
