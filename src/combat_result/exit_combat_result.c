#include "types.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "hw/mem.h"

void ExitCombatResult(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    FreeAllActors(&g_ActiveActorListState.pHead);

    if (g_PrevGameModeStackContext.dwCurrentGameModeArg3 == 0xFF)
        g_dwPendingGameMode.dwCurrentGameModeArg3 = 0xFF;
    else
        g_dwPendingGameMode.dwCurrentGameModeArg3 = 0;

    g_GameModeStackContext.dwCurrentGameMode = Battle;
    g_dwPendingGameMode.dwCurrentGameModeArg1 = 3;
}
