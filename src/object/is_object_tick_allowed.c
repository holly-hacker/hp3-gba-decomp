#include "types.h"
#include "game_modes.h"

// TickObject's gate: no mode transition in flight, and not in Dialogue mode.
s32 IsObjectTickAllowed(void)
{
    s32 result = 0;

    if (g_GameModeStackContext.dwCurrentGameMode != Dialogue && !IsGameModeTransitionPending()) {
        result = 1;
    }
    return result;
}
