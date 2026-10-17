#include "types.h"
#include "modes.h"

void DispatchGameModeUpdate(void)
{
    void (*pUpdateFn)(void);

    pUpdateFn = g_pGameModeDispatchTable[g_GameModeStackContext.dwCurrentGameMode].pUpdateFn;
    if (pUpdateFn != NULL)
        pUpdateFn();
}
