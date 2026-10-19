#include "types.h"
#include "modes.h"

// The pending mode without PushGameMode's 0x80 "newly pushed" bit.
u32 GetPendingGameMode(void)
{
    return g_dwPendingGameMode.dwCurrentGameMode & ~0x80;
}
