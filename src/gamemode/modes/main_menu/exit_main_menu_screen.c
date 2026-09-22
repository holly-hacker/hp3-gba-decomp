#include "types.h"
#include "battle.h"
#include "display.h"
#include "game_modes.h"
#include "main_menu.h"
#include "mem.h"
#include "object.h"

void ExitMainMenuScreen(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    sub_0801DC6C(g_MainMenuState.pCursorObject);
    sub_080316D4();
    sub_0803171C();
    sub_08030960(0);
    sub_080015D4(&g_ActiveObjectListState.pHead);
    sub_08007A90();
    sub_0800D2DC();
    g_dwPendingGameMode.dwCurrentGameModeArg1 = 0;
}
