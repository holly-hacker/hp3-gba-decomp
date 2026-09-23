#include "types.h"
#include "battle.h"
#include "display.h"
#include "game_modes.h"
#include "items_menu.h"
#include "main_menu.h"
#include "mem.h"

void ExitItemsSectionSelect(void)
{
    g_bItemsSectionCursor = g_GameModeStackContext.dwModeScratchB;
    ClearBgTilemap(2);
    sub_080015D4(&g_ActiveObjectListState.pHead);
    sub_0801DC6C(g_pMenuCursorObject);
    g_pMenuCursorObject = NULL;
    sub_080316D4();
    sub_0803171C();
    sub_0800D2DC();
}
