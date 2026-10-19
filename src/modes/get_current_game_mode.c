#include "types.h"
#include "modes.h"

u32 GetCurrentGameMode(void)
{
    return g_GameModeStackContext.dwCurrentGameMode;
}
