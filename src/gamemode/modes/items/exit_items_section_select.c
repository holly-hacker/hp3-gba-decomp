#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "menu/items_menu.h"
#include "menu/main_menu.h"
#include "hw/mem.h"

void ExitItemsSectionSelect(void)
{
    g_bItemsSectionCursor = g_GameModeStackContext.dwModeScratchB;
    ClearBgTilemap(2);
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    sub_0801DC6C(g_pMenuCursorObject);
    g_pMenuCursorObject = NULL;
    sub_080316D4();
    sub_0803171C();
    sub_0800D2DC();
}
