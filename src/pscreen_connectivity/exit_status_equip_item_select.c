#include "types.h"
#include "menu/items_menu.h"
#include "hw/io_regs.h"
#include "mem.h"
#include "actor.h"
#include "default_menu.h"
#include "pscreen_connectivity.h"

void ExitStatusEquipItemSelect(void)
{
    BG_PLTT[4] = g_StatusEquipItemSelect.awSavedPalette[0];
    BG_PLTT[5] = g_StatusEquipItemSelect.awSavedPalette[1];
    BG_PLTT[6] = g_StatusEquipItemSelect.awSavedPalette[2];

    if (g_StatusEquipItemSelect.pItemList != NULL)
        CloseItemList();

    ExitMenuScreen();
    FreeAllActors(&g_ActiveActorListState.pHead);
}
