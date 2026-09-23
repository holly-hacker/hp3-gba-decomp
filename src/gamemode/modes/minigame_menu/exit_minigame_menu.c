#include "types.h"
#include "battle.h"
#include "display.h"
#include "main_menu.h"
#include "mem.h"
#include "room.h"

void ExitMinigameMenu(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    sub_0801E0DC();
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    sub_0803171C();
    ClearScanlineEffects();
}
