#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "menu/in_game_menu.h"
#include "menu/main_menu.h"
#include "hw/mem.h"

void ExitInGameMenu(void)
{
    g_ListMenuState.bInGameMenuCursor = g_GameModeStackContext.dwModeScratchB;

    if (GetPendingGameMode_candidate() == Overworld)
    {
        sub_0803D420(0, 8);
        PlayScreenTransitionOutByIndex(0x3F, 2);
        sub_0803D420(0, 8);
    }

    sub_0801E0DC();
    sub_08007464(1, 0x6F);
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    sub_0800D2DC();
}
