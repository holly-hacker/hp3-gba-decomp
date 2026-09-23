#include "types.h"
#include "io_regs.h"
#include "main_menu.h"
#include "mem.h"
#include "object.h"
#include "status_equip.h"

void ExitStatusEquipItemSelect(void)
{
    BG_PLTT[4] = g_StatusEquipItemSelect.awSavedPalette[0];
    BG_PLTT[5] = g_StatusEquipItemSelect.awSavedPalette[1];
    BG_PLTT[6] = g_StatusEquipItemSelect.awSavedPalette[2];

    if (g_StatusEquipItemSelect.pItemList != NULL)
        sub_08027BA4();

    sub_0801E0DC();
    sub_080015D4(&g_ActiveObjectListState.pHead);
}
