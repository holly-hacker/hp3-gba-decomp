#include "types.h"
#include "battle.h"
#include "display.h"
#include "game_modes.h"
#include "main_menu.h"
#include "mem.h"
#include "minigame_menu.h"
#include "riddikulus.h"

void ExitRiddikulusMinigame(void)
{
    if (g_Riddikulus.dwExitToMenu == 1)
    {
        g_dwPendingGameMode.dwCurrentGameModeArg1 = 3;
        g_dwPendingGameMode.dwCurrentGameModeArg3 = 0xFF;
    }

    PlayScreenTransitionOutByIndex(0x3F, 2);

    if (g_Riddikulus.pCursorObject != NULL)
    {
        sub_0801DC6C(g_Riddikulus.pCursorObject);
        g_Riddikulus.pCursorObject = NULL;
        sub_0803171C();
    }

    sub_0802CEE4(g_Riddikulus.pObjectGroup1C);
    sub_0802CEE4(g_Riddikulus.pObjectGroup20);
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    sub_0803FF04();
    sub_0802CDB8();
}
