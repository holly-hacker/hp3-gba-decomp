#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "menu/main_menu.h"
#include "hw/mem.h"
#include "overworld/room.h"

void ExitMinigameMenu(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    sub_0801E0DC();
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    sub_0803171C();
    ClearScanlineEffects();
}
