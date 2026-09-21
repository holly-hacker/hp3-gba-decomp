#include "types.h"
#include "battle.h"
#include "display.h"
#include "game_modes.h"
#include "in_game_menu.h"
#include "main_menu.h"
#include "mem.h"

void ExitInGameMenu(void)
{
    g_bInGameMenuCursor = g_GameModeStackContext.dwModeScratchB_candidate;

    if (GetPendingGameMode_candidate() == Overworld)
    {
        sub_0803D420(0, 8);
        PlayScreenTransitionOutByIndex_candidate(0x3F, 2);
        sub_0803D420(0, 8);
    }

    sub_0801E0DC();
    sub_08007464(1, 0x6F);
    sub_080015D4(&g_ActiveObjectListState.pHead);
    sub_0800D2DC();
}
