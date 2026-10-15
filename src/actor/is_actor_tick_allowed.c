#include "types.h"
#include "game/game_modes.h"

// TickActor's gate: no mode transition in flight, and not in Dialog mode.
s32 IsActorTickAllowed(void)
{
    s32 result = 0;

    if (g_GameModeStackContext.dwCurrentGameMode != Dialog && !IsGameModeTransitionPending()) {
        result = 1;
    }
    return result;
}
