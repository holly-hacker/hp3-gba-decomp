#include "types.h"
#include "hw/io_regs.h"
#include "menu/main_menu.h"
#include "hw/mem.h"
#include "graphics/object.h"
#include "menu/status_equip.h"

void ExitStatusEquipItemSelect(void)
{
    BG_PLTT[4] = g_StatusEquipItemSelect.awSavedPalette[0];
    BG_PLTT[5] = g_StatusEquipItemSelect.awSavedPalette[1];
    BG_PLTT[6] = g_StatusEquipItemSelect.awSavedPalette[2];

    if (g_StatusEquipItemSelect.pItemList != NULL)
        sub_08027BA4();

    sub_0801E0DC();
    FreeAllObjects(&g_ActiveObjectListState.pHead);
}
