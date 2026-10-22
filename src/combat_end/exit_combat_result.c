#include "modes.h"
#include "actor.h"
#include "screen_transitions.h"
#include "map.h"

void ExitCombatResult(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    FreeAllActors(&g_ActiveActorListState.pHead);

    if (g_PrevGameModeStackContext.dwCurrentGameModeArg3 == 0xFF)
        g_dwPendingGameMode.dwCurrentGameModeArg3 = 0xFF;
    else
        g_dwPendingGameMode.dwCurrentGameModeArg3 = 0;

    g_GameModeStackContext.dwCurrentGameMode = Battle;
    g_dwPendingGameMode.dwCurrentGameModeArg1 = OverworldEntryReturn;
}
