#include "types.h"
#include "modes.h"
#include "input.h"

void DispatchGameModeInit(void)
{
    void (*pInitFn)(void);

    ResetKeyInput();
    pInitFn = g_pGameModeDispatchTable[g_GameModeStackContext.dwCurrentGameMode].pInitFn;
    if (pInitFn != NULL)
        pInitFn();
}
