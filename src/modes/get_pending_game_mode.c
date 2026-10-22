#include "types.h"
#include "modes.h"

// The pending mode without GameModeSwitchPending.
u32 GetPendingGameMode(void)
{
    return g_dwPendingGameMode.dwCurrentGameMode & ~GameModeSwitchPending;
}
