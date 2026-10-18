#include "actor.h"
#include "background.h"
#include "palette.h"
#include "default_menu.h"
#include "pscreen_status_equip.h"

void CloseStatusEquipSlotSelectScreen(void)
{
    ClearBgTilemap(2);
    ExitMenuScreen();
    FreeAllActors(&g_ActiveActorListState.pHead);
    UnreserveObjPaletteSlot(14);
    UnreserveObjPaletteSlot(15);
    ClearObjPaletteSlots();
}
