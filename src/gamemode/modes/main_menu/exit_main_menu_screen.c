#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "menu/main_menu.h"
#include "hw/mem.h"
#include "graphics/object.h"

void ExitMainMenuScreen(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    sub_0801DC6C(g_MainMenuState.pCursorObject);
    sub_080316D4();
    sub_0803171C();
    sub_08030960(0);
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    sub_08007A90();
    sub_0800D2DC();
    g_dwPendingGameMode.dwCurrentGameModeArg1 = 0;
}
