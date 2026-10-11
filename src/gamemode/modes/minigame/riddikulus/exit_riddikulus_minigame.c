#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "menu/main_menu.h"
#include "hw/mem.h"
#include "menu/minigame_menu.h"
#include "minigame/riddikulus.h"

void ExitRiddikulusMinigame(void)
{
    if (g_Riddikulus.dwExitToMenu == 1)
    {
        g_dwPendingGameMode.dwCurrentGameModeArg1 = 3;
        g_dwPendingGameMode.dwCurrentGameModeArg3 = 0xFF;
    }

    PlayScreenTransitionOutByIndex(0x3F, 2);

    if (g_Riddikulus.pCursorActor != NULL)
    {
        ReleaseMenuCursor(g_Riddikulus.pCursorActor);
        g_Riddikulus.pCursorActor = NULL;
        FreeAllParticles();
    }

    sub_0802CEE4(g_Riddikulus.pActorGroup1C);
    sub_0802CEE4(g_Riddikulus.pActorGroup20);
    FreeAllActors(&g_ActiveActorListState.pHead);
    sub_0803FF04();
    sub_0802CDB8();
}
